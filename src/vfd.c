/**
 * $Id: vfd.c 05:57 PM 2019-05-29 $
 *
 * This program is Futaba M202MD12D(2x20) VFD Interface driver
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
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "vfd.h"
#include "uart.h"

void vfd_init(void)
{
 //vfd_country(VFD_COUNTRY_JAPAN);
 //vfd_country(VFD_COUNTRY_JAPAN2);
  vfd_dimming(VFD_DIMMING_80);
  vfd_clear();
}

/**
 * To light up or light off Triangle mark
 *
 * Parameter: P4P3P2P1P0 Data obtained by displaying triangle mark
 * light-up/light-off data in 20-bit mask pattern and converting it to
 * 5 digit hexadecimal ASC
 * 
 * @note That only applies to line 2
 
 * TMARK  Triangle Mark
 *   |        1 2 3 4 5 6 7 8 91011121314151617181920 
 *   | Line1 □□□□□□□□□□□□□□□□□□□□
 *   | Line2 □□□□□□□□□□□□□□□□□□□□
 *   |       ▼_ _ ▼▼▼▼▼_ _ _ _ _ ▼▼_ _ _ _ ▼ 
 *   +->     1 0 0 1 1 1 1 1 0 0 0 0 0 1 1 0 0 0 0 1  vfd_tmark(0x9f061);
 *   |
 *   |       ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼  
 *   +->     1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  vfd_tmark(0xfffff);  
 *   |
 *   |       _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ▼
 *   +->     0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1  vfd_tmark(0x1); 
 *
*/
void vfd_tmark(uint32_t bitmask)
{
  char commandBuffer[12] = {0};
  
  sprintf(commandBuffer,"\x1b\\?LT%05lX", bitmask);
  uart_puts((const unsigned char *)commandBuffer);
}

/**
 * Moves to the writing position of Py(Row) and Px(Column).
 *
 * Px: If it is 0, 1 is assumed. If it is greater
 * Py: If it is 0, 1 is assumed. If it is greater than the maximum line, 
 * it is assumed to be the VFD_LINES
 *
*/
void vfd_gotoxy(const uint8_t Px, const uint8_t Py)
{
  char commandBuffer[14] = {'\0'};
  
  sprintf(commandBuffer,"\x1b[%d;%dH", Py, Px);
  uart_puts((const unsigned char *)commandBuffer);
}

// clear screen
void vfd_clear(void)
{
  uart_putc(VFD_ESC);  
  uart_puts_P(VFD_CLEAR_DISPLAY);  
  vfd_gotoxy(1,1);
}
// clear line
void vfd_clear_line(const uint8_t y)
{
  vfd_gotoxy(1,y);
  uart_putc(VFD_ESC);  
  uart_puts_P(VFD_CLEAR_LINE);
  vfd_gotoxy(1,y);
}
/**
 * Changes Cursor Mode
 *
 * *VFD_CURSOR_OFF       // Cursor off  
 *  VFD_CURSOR_BLINK     // Cursor blink
 *  VFD_CURSOR_ON        // Cursor on
 * 
 * @note The default value after power on willbe cursor off
*/
void vfd_cursor(const uint8_t cparam)
{
  uart_putc(VFD_ESC);  
  uart_puts_P(VFD_CURSOR);  
  uart_putc(cparam);  
}
/**
 * Changes the brightness of the display device.
 *
 * *VFD_DIMMING_100      // Brightness adjustment 100%
 *  VFD_DIMMING_80       // Brightness adjustment  80%
 *  VFD_DIMMING_60       // Brightness adjustment  60%
 *  VFD_DIMMING_40       // Brightness adjustment  40%
 *  VFD_DIMMING_20       // Brightness adjustment  20%
 *  VFD_DIMMING_0        // Brightness adjustment   0%
 *
 * @note The default value after power on willbe ‘5’(100%).
*/
void vfd_dimming(const uint8_t cparam)
{
  uart_putc(VFD_ESC);  
  uart_puts_P(VFD_DIMMING);  
  uart_putc(cparam);  
}
/**
 * Set country code
 *
 *  VFD_COUNTRY_USA             
 *  VFD_COUNTRY_FRANCE      
 * *VFD_COUNTRY_GERMANY       
 *  VFD_COUNTRY_UK         
 *  VFD_COUNTRY_DENMARK1   
 *  VFD_COUNTRY_SWEDEN     
 *  VFD_COUNTRY_ITALY      
 *  VFD_COUNTRY_SPAIN1     
 *  VFD_COUNTRY_JAPAN      
 *  VFD_COUNTRY_DENMARK2   
 *  VFD_COUNTRY_SPAIN2     
 *  VFD_COUNTRY_LATIN      
 *  VFD_COUNTRY_JAPAN2       
 *
 * @note The default value after power on is Germany.
*/
void vfd_country(const uint8_t cparam)
{
  uart_putc(VFD_ESC);    
  uart_putc(VFD_COUNTRY);  
  uart_putc(0x63);  
}
/*
*EOF
*/
