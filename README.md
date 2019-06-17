# M202MD12D
This program is Main of Futaba M202MD12D(2x20) VFD Demo

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
## Tada
![alt text](https://github.com/boricha/M202MD12D/blob/master/src/tada.jpg)
## Pinout
![alt text](https://github.com/boricha/M202MD12D/blob/master/src/pinout.jpg)        
## Schematic
![alt text](https://github.com/boricha/M202MD12D/blob/master/schematic/schematic.jpg)
