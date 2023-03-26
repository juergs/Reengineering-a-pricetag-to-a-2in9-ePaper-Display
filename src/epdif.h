/**
 *  @filename   :   epdif.h
 *  @brief      :   Header file of epdif.cpp providing EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef EPDIF_H
#define EPDIF_H

#include <Arduino.h>
#include "ArduinoTrace.h"
/*
 * juergs ePaper Connections
#define EPD_DC      4   // D2 can be any pin, but required! default is GPIUO0 = D3
#define EPD_CS      15  // D8 can be any pin, but required!
#define EPD_BUSY    5   // D1 can set to -1 to not use a pin (will wait a fixed delay) default is GPIO4 = D2
#define EPD_RESET   2   // D4 can set to -1 and share with chip Reset (can't deep sleep)
#define SRAM_CS     -1  // NC can set to -1 to not use a pin (uses a lot of RAM!)   see comment above, having no external SRAM
*/

// Pin definition for ESP8266 (e.g. NodeMCU)
// Connect display CLK signal to GPIO 14 (Node MCU pin D5)
// Connect display DIN signal to GPIO 13 (Node MCU pin D7)
// Connect display 3.3V to NodeMCU 3V3
// Connect display GND to NodeMCU GND
// Connect other pins as follows:
//      Display       GPIO   WemosD1 pin
#define BUSY_PIN        5 // 
#define RST_PIN         2 // 
#define DC_PIN          4 // 
#define CS_PIN          15 // 


class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);
};

#endif
