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
 * 
 *  there are 2 memory areas embedded in the e-paper display
 *  and once the display is refreshed, the memory area will be auto-toggled,
 *  i.e. the next action of SetFrameMemory will set the other memory area
 *  therefore you have to set the frame memory and refresh the display twice.
 *
 * see also: 
 *    D:\Work_Epaper\_projects\e-Paper-WaveShare_Demo\e-Paper\Arduino\epd2in9_V2   -for partial update code sample
 *    https://github.com/waveshare/e-Paper/tree/master
 *    https://github.com/waveshare/e-Paper/tree/master/Arduino/epd2in9_V2
 * 
 *    Sample-code using "WEMOS D1 Mini" / ESP8266!
 * 
 */
#include "Debug.h"
#include "ArduinoTrace.h"
#include <SPI.h>
#include "epd2in9_GDEH029Z92.h"    // needed for epd? GDEH029Z94 is ok, too. Using SSD1680-Controller 
#include "GUI_Paint.h"
#include "imagedata.h"
#include "fonts.h"
#include <stdint.h>

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

    //printf("Test_printf %d", 100);
    
    
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
    Debug("Now, execute testcases ...\r\n");    
    Debug("Draw-Canvas init.\r\n"); 
    //Paint_NewImage(MyImage, EPD_WIDTH, EPD_HEIGHT, ROTATE_90, WHITE);   // white background, rotation works  (270 not? 180 + 0, OK)
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Paint_NewImage(MyImage, EPD_HEIGHT, EPD_WIDTH, ROTATE_90, WHITE);   // white background, rotation works  (270 not? 180 + 0, OK)
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //TODO check rotation and mirroring. Check their defaults  
    Debug("Draw-Canvas created.\r\n"); 
    
    Paint_SelectImage(MyImage);                                        // grep the image-buffer      
    Paint_Clear(WHITE);
       
    //Debug ("call Paint_DrawCharAt");  
    //Paint.Rotate = ROTATE_270; 
    // auf *Paint_DrawCharAt* geändert! Paint_DrawChar Pointer-Exception?!
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Debug ("call Paint_DrawText");  
    //Paint_DrawText(20,10, "Hallo. Dies ist ein Test, der ueber zwei Zeilen geht.", &Font16, BLACK, WHITE); 
    //TODO: real text positioning, regarding also text.length and CRs
    // OK, tested
    //Paint_DrawText(Font16.Width +20, Font16.Height +10, "01234567890123456789012345678901234567890123456789.", &Font16, BLACK, WHITE); 
    //Paint_DrawText (0, 0, "01234567890123456789012345678901234567890123456789.", &Font16, BLACK, WHITE);            // Font 16  are 25 chars per line
    //Paint_DrawText (0, 0, "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", &Font8, BLACK, WHITE);     // Font 8   are 58 chars per line
    //Paint_DrawText (0, 0, "012345678901234567890123456789012345678901234567890123456789", &Font12, BLACK, WHITE);   // Font 12  are 41 chars per line
    //Paint_DrawText (0, 0, "012345678901234567890123456789012345678901234567890123456789", &Font20, BLACK, WHITE);   // Font 20  are 20 chars per line
    //Paint_DrawText (0, 0, "012345678901234567890123456789012345678901234567890123456789", &Font24, BLACK, WHITE);     // Font 24  are 16 chars per line
    //Paint_DrawText (0, 0, "012345678901234567890123456789012345678901234567890123456789", &Font24, BLACK, WHITE);     // Font 24  are 16 chars per line

    //Paint_DrawStringAt(0,50,"abcdefghijkl", &Font16, COLORED);

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // ok, funktioniert
    //Paint_DrawCharAt(20,1, '*',&Font16, UNCOLORED);

    Debug ("Paint_DrawCharAt.Ready");  

  //TODO: @epd2in9_V2-demo.ino

  //epd.SetFrameMemory_Partial(paint.GetImage(), 80, 72, paint.GetWidth(), paint.GetHeight());
  //epd.DisplayFrame_Partial();

/* OK*/
   /* 
    Paint_DrawPoint(1,1,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND); 
    Paint_DrawPoint(1,10,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND);
    Paint_DrawPoint(1,20,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND);
    Paint_DrawPoint(1,30,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND);
    Paint_DrawPoint(1,40,BLACK,DOT_PIXEL_1X1, DOT_FILL_AROUND);
   */

    //---      ( Xstart | Ystart | Xend | Yend | Color | DOT_PIXEL Line_width | LINE_STYLE Line_Style
    //Paint_DrawLine(20, 10, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID); 
    /* Paint_DrawLine(20, 10, 20, 120, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);  */

    /* 
    for (int dy=1; dy < 128; dy += 10) 
    {
        DUMP(dy); 
        //---      ( Xstart | Ystart | Xend | Yend | Color | DOT_PIXEL Line_width | LINE_STYLE Line_Style
        //Paint_DrawLine(20, dy, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID); 
        Paint_DrawLine(20, dy, 20, 120, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID); 
    } 
    */
 
    epd.DisplayBuffer(MyImage);    // black on white
    
    //epd.Display_Base(MyImage);   //black on red background
    
    //epd.Display_Partial(MyImage);

    //*******************************************************************************************************
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

    Debug ("Begin testing TEST_PARTIAL.in \r\n");
    
    Debug ("call Display_Base\r\n");
    //epd.Display_Base(&IMAGE_BLACK);   //black on red background

    Debug ("call DisplayFrame IMAGE_BLACK + IMAGE_RED\r\n");
    epd.ClearFrame();
    epd.DisplayFrame(IMAGE_BLACK,IMAGE_RED); 
    delay(5000);

    Debug ("call DisplayFrame IMAGE_BLACK\r\n");
    epd.ClearFrame();
    epd.DisplayFrame(IMAGE_BLACK,NULL); 
    delay(5000);

    Debug ("call DisplayFrame IMAGE_RED\r\n");
    epd.ClearFrame();
    epd.DisplayFrame(NULL,IMAGE_RED); 

    //Debug ("call Display_Partial");
    //epd.Display_Partial(IMAGE_BLACK);

    Debug ("call TEST_PARTIAL.out \r\n");

    Debug ("enter DEEP_SLEEP\r\n");
    epd.DeepSleep(); 
    
  
  
  //--- Done, stop here  
  TRACE();
  Debug("Stopped by Enless_loop\r\n");
  epd.EndlessLoop(); 

  //PAINT paint;


   /*  unsigned char image[1024];
    Paint paint(image, 128, 8);    //width should be the multiple of 8 

    paint.Clear(UNCOLORED);
   
    Debug( "DrawAbsolutePixel");
    
  
    for (int x = 0; x < 120; x++)
    {      
      paint.DrawAbsolutePixel(x, 5, COLORED);   //--- writes to buffer only
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
        //---ESP8266 needs this  
        ESP.wdtFeed(); //Feed dog to prevent system reset
        // put your main code here, to run repeatedly:
        digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
        delay(2);
        digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on (Note that LOW is the voltage level
        delay(250);  
    }
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

