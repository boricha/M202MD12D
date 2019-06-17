/**
 * $Id: main.c 05:57 PM 2019-05-26 $
 *
 * This program is Main of Futaba M202MD12D(2x20) VFD Demo
 *
 * Application : LIUST-5X Display Module
 * Features    : 20x2 Digits, 5x7 Dots + Triangle Mark
 * Interface   : RS-232C Asynchronous Full duplex
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
 * Connector wiring
 * Pin No. Signal name            in/out
 *      1  RTS: Request To Send   Out
 *      2  CTS: Clear To Send     In
 *     *3  GND                    -
 *     *4  RXD: Receive Data      In
 *      5  TXD: Transmit Data     Out
 *     *6  +12V                   -
 *
 *  Please note that this program does not use hardware flow control(No.1 RTS / No2. CTS) 
 *  only use No.4 RXD
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "uart.h"
#include "vfd.h"

static void setup(void);
static void demo_welcome(void);
static void demo_dimming(void);
static void demo_tmark(void);
static void demo_end(void);

int main(void)
{
  _delay_ms(100);

  setup();

  while(1)
  {
   _delay_ms(1000);
    demo_welcome();
    demo_dimming();
    demo_tmark();
    demo_end();
  }
}
static void setup(void)
{
  uart_init();
  vfd_init();
}
static void demo_welcome(void)
{
  vfd_clear();
  // \xae,\xb0 : special character
  vfd_puts_P("\xae\xae TOSHIBA  LIUST \xaf\xaf");
  vfd_gotoxy(1,2);
  vfd_puts_P("\xb0 RS-232C INTERFACE");
  _delay_ms(2000);
}
static void demo_end(void)
{
  vfd_clear();
  vfd_gotoxy(4,1);
  vfd_puts_P("Thank you for");
  vfd_gotoxy(6,2);
  vfd_puts_P("Watching!.");
  _delay_ms(4000);

  vfd_clear();
  _delay_ms(4000);
}
static void demo_dimming(void)
{
  vfd_clear();
  for(uint8_t i=0;i<VFD_DISP_LENGTH;i++) vfd_putc(0xdb);
  vfd_gotoxy(1,2);
  for(uint8_t i=0;i<VFD_DISP_LENGTH;i++) vfd_putc(0xdb);

  vfd_gotoxy(5,1);
  vfd_puts_P(" Brightness ");

  vfd_gotoxy(8,2);
  vfd_puts_P(" 100% ");
  vfd_dimming(VFD_DIMMING_100);
  _delay_ms(1500);

  vfd_gotoxy(8,2);
  vfd_putc(0xdb);
  vfd_puts_P(" 80% ");
  vfd_dimming(VFD_DIMMING_80);
  _delay_ms(1000);

  vfd_gotoxy(9,2);
  vfd_puts_P(" 60% ");
  vfd_dimming(VFD_DIMMING_60);
  _delay_ms(1000);

  vfd_gotoxy(9,2);
  vfd_puts_P(" 40% ");
  vfd_dimming(VFD_DIMMING_40);
  _delay_ms(1000);

  vfd_gotoxy(9,2);
  vfd_puts_P(" 20% ");
  vfd_dimming(VFD_DIMMING_20);
  _delay_ms(3000);

  vfd_gotoxy(8,2);
  vfd_puts_P(" 100% ");
  vfd_dimming(VFD_DIMMING_100);
  _delay_ms(3000);
}

static void demo_tmark(void)
{
  uint32_t tmark=0;

  demo_welcome();

  vfd_tmark(0xfffff);                   // TMark all On
  _delay_ms(1000);

  vfd_tmark(0x0);                       // TMark all Off
  _delay_ms(1000);

  //         20....+...10....+...1
  //          09876543210987654321
  vfd_tmark(0b11111000001111100000);    // TMark may be configured in bit unit.
 _delay_ms(1000);

  vfd_tmark(0b00000111110000011111);    // TMark may be configured in bit unit.
 _delay_ms(1000);

  for(uint8_t i=0; i<20;i++)
  {
    vfd_tmark(tmark << i);
   _delay_ms(100);
  }
  _delay_ms(1000);

  tmark = 0x80000;
  for(uint8_t i=0; i<20;i++)
  {
    vfd_tmark(tmark >> i);
   _delay_ms(100);
  }
  _delay_ms(2000);
}

/*
*EOF
*/

