#ifndef _UART_H_
#define _UART_H_
/**
 * $Id: uart.h 06:00 PM 2012-10-24 $
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
#include <stdio.h>   // printf

#define BAUDRATE  9600
#define UART_UBRR  ((F_CPU/(16UL*BAUDRATE))-1)

extern void uart_init(void);                     // Initialize the uart in polling mode
extern void uart_putc(uint8_t data);             // Send one byte over the uart
extern void uart_puts(const unsigned char *str); // Send a string over the uart
extern uint8_t uart_getc(void);                  // Receive one byte from the uart
extern void uart_puts_p(const char *progmem_s);  // Send a string from program memory over the uart

// macros for automatically storing string constant in program memory
#define uart_puts_P(__s)    uart_puts_p(PSTR(__s))
#ifdef  _PRINTF_STREAM_
  #define PRINTF(format, ...)   printf_P(PSTR(format), ## __VA_ARGS__)
#endif  
#endif
