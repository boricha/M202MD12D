#ifndef _VFD_H_
#define _VFD_H_
/**
 * $Id: vfd.h 05:57 PM 2019-05-29 $
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

// Control Character
#define VFD_ESC               0x1b      // CTRL-[ Escape Sequence
#define VFD_BS                0x08      // CTRL-H Back Space
#define VFD_LF                0x0a      // CTRL-J Line Feed
#define VFD_CR                0x0d      // CTRL-M Carriage Return

#define VFD_CLEAR_DISPLAY    "[2J"
#define VFD_CLEAR_LINE       "[0K"

#define VFD_COUNTRY           0x52      // Set country code
#define VFD_COUNTRY_USA       0x30
#define VFD_COUNTRY_FRANCE    0x01
#define VFD_COUNTRY_GERMANY   0x02      // *Power On default
#define VFD_COUNTRY_UK        0x03
#define VFD_COUNTRY_DENMARK1  0x04
#define VFD_COUNTRY_SWEDEN    0x05
#define VFD_COUNTRY_ITALY     0x06
#define VFD_COUNTRY_SPAIN1    0x07
#define VFD_COUNTRY_JAPAN     0x08
#define VFD_COUNTRY_NORWAY    0x09
#define VFD_COUNTRY_DENMARK2  0x0A
#define VFD_COUNTRY_SPAIN2    0x0B
#define VFD_COUNTRY_LATIN     0x0C
#define VFD_COUNTRY_JAPAN2    0x63

#define VFD_DIMMING          "\\?LD"   // Changes the brightness of the display device.
#define VFD_DIMMING_100       0x35     // Brightness adjustment 100%
#define VFD_DIMMING_80        0x34     // Brightness adjustment  80%
#define VFD_DIMMING_60        0x33     // Brightness adjustment  60%
#define VFD_DIMMING_40        0x32     // Brightness adjustment  40%
#define VFD_DIMMING_20        0x31     // Brightness adjustment  20%
#define VFD_DIMMING_0         0x30     // Brightness adjustment   0%

#define VFD_CURSOR           "\\?LC"   // Cursor mode
#define VFD_CURSOR_OFF        0x30     // Cursor off  (power on default)
#define VFD_CURSOR_BLINK      0x31     // Cursor blink
#define VFD_CURSOR_ON         0x32     // Cursor on

#define VFD_TMARK            "\\?LT"   // Triangle Mark
#define VFD_TMARK_ON          0x01     // Triangle Mark on
#define VFD_TMARK_OFF         0x00     // Triangle Mark off

#define VFD_ID               "[c"      // Identification Code

#define vfd_putc(c)          uart_putc(c)
#define vfd_puts(s)          uart_puts(s)
#define vfd_puts_p(s)        uart_puts_p(s)
#define vfd_puts_P(s)        uart_puts_P(s)

/**
 *  Definitions for VFD software characteristics
 *  Change these definitions to adapt setting to your display
 */
#define VFD_LINES            2    // Number of visible lines of the display
#define VFD_DISP_LENGTH      20   // Visibles characters per line of the display

//extern coordinates  _vfd_coord;
extern void vfd_init(void);
extern void vfd_clear(void);
extern void vfd_clear_line(const uint8_t y);
extern void vfd_cursor(const uint8_t cparam);
extern void vfd_dimming(const uint8_t cparam);
extern void vfd_country(const uint8_t cparam);
extern void vfd_gotoxy(const uint8_t Px, const uint8_t Py);
extern void vfd_tmark(const uint32_t bitmask);
#endif
/*
*EOF
*/
