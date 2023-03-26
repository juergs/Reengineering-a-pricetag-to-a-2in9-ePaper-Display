/**
 *  @filename   :   epd2in9b-demo.ino
 *  @brief      :   2.9inch e-paper display (B) demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     July 17 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
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
#include "Debug.h"
#include "ArduinoTrace.h"
#include <SPI.h>
#include "epd2in9_GDEH029Z92.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include "epdpaint.h"


#define COLORED     0
#define UNCOLORED   1

/* //--------------------------------------------------------------------------------------------
void Sys_run(void)
{
  ESP.wdtFeed(); //Feed dog to prevent system reset
}
//--------------------------------------------------------------------------------------------
void LED_run(void)
{
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(5);
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on (Note that LOW is the voltage level
  delay(250);
} */
//--------------------------------------------------------------------------------------------
void setup() 
{
    //--- put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("");
    
    
    //--- class with lowlevel functions (epd2in9_GDEH029Z92)
    Epd epd;

    int isInitialized = epd.Init(); 
    DUMP(isInitialized); 

    if (isInitialized != 0) 
    {
      Serial.print("e-Paper init failed!");    
      return;
    }
    else
    {
      Serial.print("e-Paper init done.");
    }
  
    TRACE();
    
    //--- prepareings: clears directly the SRAM-buffer on the e-paper display, without sw-buffer 
    epd.ClearFrame();


    //--- sw-buffer: big enough heap size ? 
    //--- https://arduino-esp8266.readthedocs.io/en/latest/mmu.html

    uint8_t *MyImage;
    uint16_t Imagesize = 4736;  // y=128 * x=296

    if ((MyImage = (uint8_t *)malloc(Imagesize)) == NULL) 
    {
        Debug("FATAL: Failed to request memory...\r\n");
        ESP.wdtFeed();          //--- feed dog to prevent system reset!
        while(1);
    } else
    {
      Debug("Succeeded to apply memory for image-buffer. \r\n");
    }
    
    //*******************************************************************************************************
    // TESTCASE(S)
    //*******************************************************************************************************
    Debug("Now, draw a black line on a white background ...\r\n");
    Paint_NewImage(MyImage, EPD_WIDTH, EPD_HEIGHT, ROTATE_0, WHITE);   // white background, rotation works 
    
    Paint_SelectImage(MyImage);                                        // grep the image-buffer  
    
    Paint_Clear(WHITE);
    
    Paint_DrawPoint(1,1,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND); 
    Paint_DrawPoint(1,10,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND);
    Paint_DrawPoint(1,20,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND);
    Paint_DrawPoint(1,30,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND);
    Paint_DrawPoint(1,40,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND);

   // Paint_DrawString_EN(1,40, "Hallo. Dies ist ein Test", &Font16, BLACK, WHITE); 

    //---      ( Xstart | Ystart | Xend | Yend | Color | DOT_PIXEL Line_width | LINE_STYLE Line_Style
    //Paint_DrawLine(20, 10, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID); 
    Paint_DrawLine(20, 10, 20, 120, WHITE, DOT_PIXEL_4X4, LINE_STYLE_SOLID); 

    /* for (int dy=1; dy < 128; dy += 10) 
    {
        DUMP(dy); 
        //---      ( Xstart | Ystart | Xend | Yend | Color | DOT_PIXEL Line_width | LINE_STYLE Line_Style
        //Paint_DrawLine(20, dy, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID); 
        Paint_DrawLine(20, dy, 20, 120, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID); 
    } */

    //epd.DisplayBuffer(MyImage);    // black on white
    epd.Display_Base(MyImage);        //black on red background
    //epd.Display_Partial(MyImage);

    //*******************************************************************************************************

    Debug("Drawline Black done....\r\n");

    //*******************************************************
/* 
    Debug("Drawline Black done....\r\n");
    delay(4000);

    Debug("Drawline White on Black ...\r\n");
    //--- 
    Paint_NewImage(MyImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE); 
    Paint_SelectImage(MyImage); 
    
    Paint_Clear(WHITE);
    Paint_DrawLine(20,70,20,120,BLACK, DOT_PIXEL_1X1,LINE_STYLE_SOLID); 

    epd.DisplayBuffer(MyImage); 

    Debug("Drawline White done....\r\n");
    delay(4000);

    Debug("Now, Drawline white on red ...\r\n");
    //--- 
    Paint_NewImage(MyImage, EPD_WIDTH, EPD_HEIGHT, 270, RED); 
    Paint_SelectImage(MyImage); 
    
    Paint_Clear(WHITE);
    Paint_DrawLine(20,70,20,120,WHITE, DOT_PIXEL_1X1,LINE_STYLE_SOLID); 

    epd.DisplayBuffer(MyImage); 

    Debug("Drawline red done....\r\n");
    delay(4000);
 */
    
  TRACE();
  Debug("Stopped by Enless_loop");
  epd.EndlessLoop(); 

  //PAINT paint;


   /*  unsigned char image[1024];
    Paint paint(image, 128, 8);    //width should be the multiple of 8 

    paint.Clear(UNCOLORED);
   
    Debug( "DrawAbsolutePixel");
    
  
    for (int x = 0; x < 120; x++)
    {
      //--- schreibt nur in den Puffer
      paint.DrawAbsolutePixel(x, 5, COLORED);
    } */

    //Todo: Puffer updaten + anzeigen

    //paint.DrawStringAt(0, 0, "e-Paper Demo", &Font12, COLORED);    
    //epd.SetPartialWindowBlack(paint.GetImage(), 0, 123, paint.GetWidth(), paint.GetHeight());
    //epd.DisplayFrame();
    /* epd.UpdateDisplay(); 

    epd.DeepSleep(); 

TRACE();
  String s = "Enless_loop";
  DUMP(s);
  epd.EndlessLoop(); 

 */


    /* TRACE();
    paint.Clear(UNCOLORED);
    paint.DrawStringAt(2, 2, "Hello world", &Font16, COLORED);
    epd.SetPartialWindowRed(paint.GetImage(), 0, 64, paint.GetWidth(), paint.GetHeight());

    TRACE();
    paint.SetWidth(64);
    paint.SetHeight(64);

    TRACE();
    paint.Clear(UNCOLORED);
    paint.DrawRectangle(0, 0, 40, 50, COLORED);
    paint.DrawLine(0, 0, 40, 50, COLORED);
    paint.DrawLine(40, 0, 0, 50, COLORED);
    epd.SetPartialWindowBlack(paint.GetImage(), 8, 120, paint.GetWidth(), paint.GetHeight());

    TRACE();
    paint.Clear(UNCOLORED);
    paint.DrawCircle(32, 32, 30, COLORED);
    epd.SetPartialWindowBlack(paint.GetImage(), 64, 120, paint.GetWidth(), paint.GetHeight());

    TRACE();
    paint.Clear(UNCOLORED);
    paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
    epd.SetPartialWindowRed(paint.GetImage(), 8, 200, paint.GetWidth(), paint.GetHeight());

    TRACE();
    paint.Clear(UNCOLORED);
    paint.DrawFilledCircle(32, 32, 30, COLORED);
    epd.SetPartialWindowRed(paint.GetImage(), 64, 200, paint.GetWidth(), paint.GetHeight()); */

    /* This displays the data from the SRAM in e-Paper module */
    //epd.DisplayFrame();

    /* This displays an image */
    //epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);

    TRACE();

    /* Deep sleep */
    //epd.DeepSleep();
}
//--------------------------------------------------------------------------------------------
void loop() 
{
  // put your main code here, to run repeatedly:
  while (1)
    {   
        ESP.wdtFeed(); //Feed dog to prevent system reset
        // put your main code here, to run repeatedly:
        digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
        delay(5);
        digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on (Note that LOW is the voltage level
        delay(250);  
    }
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

