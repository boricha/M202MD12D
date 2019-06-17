/**
 * $Id: uart.c 06:00 PM 2012-10-24 $
 *
 * This program is UART library
 *
 * MIT License
 * 
 * Copyright (c) 2019 ssk.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
*/
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>            // printf
#include "uart.h"

#ifdef _PRINTF_STREAM_  
   static int uart_putchar(char c, FILE *stream);
   FILE PRINTF_STREAM = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
#endif

void uart_init(void)
{
  uint16_t ubrr = UART_UBRR;
  
  UBRR0H = (uint8_t)(ubrr>>8);
  UBRR0L = (uint8_t)ubrr;

  //UCSR0B = _BV(TXEN0) | _BV(RXEN0);  
  UCSR0B = _BV(TXEN0);  
 
  // ANSI Escape sequences - VT100 / VT52
  // http://ascii-table.com/ansi-escape-sequences-vt-100.php
  
  //^[ = Esc
  // reset RIS             Reset terminal to initial state        ^[c
  // clearscreen ED2       Clear entire screen                    ^[[2J
  
  uart_puts_P("\33c\33[2J");            // Reset & Clear Terminal
  _delay_ms(100);
  
#ifdef _PRINTF_STREAM_  
  stdout = &PRINTF_STREAM;  // Route stdout stream to PRINTF_STREAM
  PRINTF(">>> Welcome Debug Mode  %dbps, UBRR:%d, Free memory:%dBytes\r\n",BAUDRATE, ubrr, freeRam());
#else
  uart_puts_P(">>> Welcome Debug Mode ");
#endif
}

#ifdef _PRINTF_STREAM_  
static int uart_putchar(char c, FILE *stream)
{
  //if (c == '\n') uart_putchar('\r', stream);
  
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}
#endif

void uart_putc(uint8_t data)
{
//  loop_until_bit_is_set(UCSRA, UDRE);
//  UDR = data;
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}

void uart_puts(const unsigned char *str)
{
  register char c;
  while((c=*str++)) uart_putc(c);

}

uint8_t uart_getc(void)
{
//  loop_until_bit_is_set(UCSRA, RXC);
//  return UDR;
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

void uart_puts_p(const char *progmem_s)
{
  register char c;
  while((c= pgm_read_byte(progmem_s++))) uart_putc(c);
}
/*
 * EOF
 */