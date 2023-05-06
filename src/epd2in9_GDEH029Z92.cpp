/** ----------------------------------------------------
 *  @filename   :   epd2in9_GDEH029Z92.cpp
 *  @brief      :   Implements for Dual-color e-paper library
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
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
 * ----------------------------------------------------  */

 // Correct the BUSY signal configuration to pull-down input mode, affecting the sleep current. After changing to the pull-up input, the sleep current is reduced to 1uA.

#include <stdlib.h>
#include "epd2in9_GDEH029Z92.h"
#include "ArduinoTrace.h"

Epd::~Epd() 
{
    // destructor
};

Epd::Epd() 
{
    TRACE(); 
    //--- constructor
    reset_pin   = RST_PIN;
    dc_pin      = DC_PIN;
    cs_pin      = CS_PIN;
    busy_pin    = BUSY_PIN;
    width       = EPD_WIDTH;
    height      = EPD_HEIGHT;
    
    /* DUMP(reset_pin);
    DUMP(dc_pin);
    DUMP(cs_pin);
    DUMP(busy_pin);
    DUMP(width);
    DUMP(height); */
};

int Epd::Init(void) 
{
    // TRACE();

    //--- toggle reset. EPD hardware init start
    ResetDisplay();

    //--- this calls the peripheral hardware interface, see epdif 
    if (IfInit() != 0) 
    {
        return -1;
    }

    // TRACE(); 

    //delay(100);
    
    WaitUntilIdle();

    TRACE();

    //--- SWRESET
    SendCommand(0x12);    
	
    WaitUntilIdle();

    //--- Driver output control
    SendCommand(0x01); 
    SendData(0x27);
    SendData(0x01);
    SendData(0x00);    

    //--- data entry mode 
    SendCommand(0x11); 
    SendData(0x01);

    //TODO: get influence on orientation with  rotate + mirror. Default? 
    //--- set Ram-X address start/end position
    SendCommand(0x44); 
    SendData(0x00);
    SendData(0x0F);     //--- 0x0F-->(15+1)*8=128

    //TODO: get influence on orientation with  rotate + mirror. Default?
    //--- Set ram Y start/end postion
    SendCommand(0x45); 
    SendData(0x27);
    SendData(0x01);
    SendData(0x00);
    SendData(0x00);

    //--- BorderWavefrom
    SendCommand(0x3c); 
    SendData(0x05);

    //--- read built-in temperature sensor
    SendCommand(0x18); 
    SendData(0x80);

    //--- Display update control
    SendCommand(0x21); 
    SendData(0x00);
    SendData(0x80);
    
    //--- set RAM x address count to 0;
    SendCommand(0x4E); 
    SendData(0x00);

     //--- set RAM y address count to 0x199;
    SendCommand(0x4F); 
    SendData(0x27);
    SendData(0x01);
	
    WaitUntilIdle();
	    
    /* EPD hardware init done */
    return 0;

}

/** ----------------------------------------------------
 *  @brief: basic function for sending commands
 * ----------------------------------------------------  */
void Epd::SendCommand(unsigned char command) {
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

/** ----------------------------------------------------
 *  @brief: basic function for sending data
 * ----------------------------------------------------  */
void Epd::SendData(unsigned char data) {
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

/** ----------------------------------------------------
 *  @brief: Wait until the busy_pin goes HIGH
 * ----------------------------------------------------  */
void Epd::WaitUntilIdle(void) 
{
    int busy;
    while (1)
    { //=1 BUSY
        busy = DigitalRead(busy_pin);
        if (busy == 0) break;
        #warning *** Use this with ESP8266 only
        ESP.wdtFeed();          //--- feed dog to prevent system reset!
    }
}

/** ----------------------------------------------------
 *  @brief: module reset. 
 *          often used to awaken the module in deep sleep, 
 *          see Epd::Sleep();
 * ----------------------------------------------------  */
void Epd::ResetDisplay(void) {
    DigitalWrite(reset_pin, LOW);
    DelayMs(200);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);   
}

/** ----------------------------------------------------
 *  @brief: transmit partial data to the SRAM
 * ----------------------------------------------------  */
void Epd::SetPartialWindow(const unsigned char* buffer_black, const unsigned char* buffer_red, int x, int y, int w, int l) 
{
    #define PARTIAL_IN                  0x91
    #define PARTIAL_WINDOW              0x10
    #define DATA_START_TRANSMISSION_1   0x13
    #define DATA_START_TRANSMISSION_2   
    #define PARTIAL_OUT                 0x92

    #warning in dev_progress or not established yet
    // SendCommand(PARTIAL_IN);    
    
    // SendCommand(PARTIAL_WINDOW);
    // SendData(x & 0xf8);             //--- x should be the multiple of 8, the last 3 bit will always be ignored
    // SendData(((x & 0xf8) + w  - 1) | 0x07);
    // SendData(y >> 8);        
    // SendData(y & 0xff);
    // SendData((y + l - 1) >> 8);        
    // SendData((y + l - 1) & 0xff);
    // SendData(0x01);                 //--- Gates scan both inside and outside of the partial window. (default) 
    // DelayMs(2);
    
    // SendCommand(DATA_START_TRANSMISSION_1);
    // if (buffer_black != NULL) {
    //     for(int i = 0; i < w  / 8 * l; i++) 
    //     {
    //         SendData(buffer_black[i]);  
    //     }  
    // } else {
    //     for(int i = 0; i < w  / 8 * l; i++) 
    //     {
    //         SendData(0x00);  
    //     }  
    // }
    // DelayMs(2);
    
    // SendCommand(DATA_START_TRANSMISSION_2);
    // if (buffer_red != NULL) 
    // {
    //     for(int i = 0; i < w  / 8 * l; i++) 
    //     {
    //         SendData(buffer_red[i]);  
    //     }  
    // } else 
    // {
    //     for(int i = 0; i < w  / 8 * l; i++) 
    //     {
    //         SendData(0x00);  
    //     }  
    // }
    // DelayMs(2);
    // SendCommand(PARTIAL_OUT);  
}

/** ----------------------------------------------------
 *  @brief: transmit partial data to the black part of SRAM
 * ----------------------------------------------------  */
void Epd::SetPartialWindowBlack(const unsigned char* buffer_black, int x, int y, int w, int l) 
{
    #warning not established yet
    /* SendCommand(PARTIAL_IN);
    SendCommand(PARTIAL_WINDOW);
    SendData(x & 0xf8);     // x should be the multiple of 8, the last 3 bit will always be ignored
    SendData(((x & 0xf8) + w  - 1) | 0x07);
    SendData(y >> 8);        
    SendData(y & 0xff);
    SendData((y + l - 1) >> 8);        
    SendData((y + l - 1) & 0xff);
    SendData(0x01);         // Gates scan both inside and outside of the partial window. (default) 
    DelayMs(2);
    SendCommand(DATA_START_TRANSMISSION_1);
    if (buffer_black != NULL) {
        for(int i = 0; i < w  / 8 * l; i++) {
            SendData(buffer_black[i]);  
        }  
    } else {
        for(int i = 0; i < w  / 8 * l; i++) {
            SendData(0x00);  
        }  
    }
    DelayMs(2);
    SendCommand(PARTIAL_OUT);   */
}

/** ----------------------------------------------------
 *  @brief: transmit partial data to the red part of SRAM
 * ----------------------------------------------------  */
void Epd::SetPartialWindowRed(const unsigned char* buffer_red, int x, int y, int w, int l) 
{
    #warning not established yet
   /*  SendCommand(PARTIAL_IN);
    SendCommand(PARTIAL_WINDOW);
    SendData(x & 0xf8);     // x should be the multiple of 8, the last 3 bit will always be ignored
    SendData(((x & 0xf8) + w  - 1) | 0x07);
    SendData(y >> 8);        
    SendData(y & 0xff);
    SendData((y + l - 1) >> 8);        
    SendData((y + l - 1) & 0xff);
    SendData(0x01);         // Gates scan both inside and outside of the partial window. (default) 
    DelayMs(2);
    SendCommand(DATA_START_TRANSMISSION_2);
    if (buffer_red != NULL) {
        for(int i = 0; i < w  / 8 * l; i++) {
            SendData(buffer_red[i]);  
        }  
    } else {
        for(int i = 0; i < w  / 8 * l; i++) {
            SendData(0x00);  
        }  
    }
    DelayMs(2);
    SendCommand(PARTIAL_OUT);   */
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--- 08.0423 juergs Test Partial
void Epd::Display_Partial(unsigned char *Image)
{
	unsigned int i;
//Reset
    ResetDisplay();
	//--- read lookuptable partial driving
    Transfer_LUT(PARTIAL_LUT);  //_WF_PARTIAL_2IN9	
    SendCommand(0x37);  //--- write register for display option 
	SendData(0x00);  
	SendData(0x00);  
	SendData(0x00);  
	SendData(0x00); 
	SendData(0x00);  	
	SendData(0x40);  
	SendData(0x00);  
	SendData(0x00);   
	SendData(0x00);  
	SendData(0x00);

	SendCommand(0x3C);  	//---   BorderWavefrom
	SendData(0x80);	

	SendCommand(0x22); 
	SendData(0xC0);   
	SendCommand(0x20); 
	
    WaitUntilIdle();
	
	SetWindows(0, 0, EPD_WIDTH-1, EPD_HEIGHT-1);
	SetCursor(0, 0);

	SendCommand(0x24);   //--- Write back full Black and White image to RAM
	for(i=0;i<4736;i++)
	{
		SendData(Image[i]);
	} 
	TurnOnDisplay_Partial();
}

/** ----------------------------------------------------
 * @brief: sends LUT to EPD-registers
 * ----------------------------------------------------  */
void Epd::Transfer_LUT(unsigned char *lut)
{       
	unsigned char count;
	SendCommand(0x32);
	
    for(count=0; count<153; count++) 
		SendData(lut[count]); 

	WaitUntilIdle();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** ----------------------------------------------------
 * @brief: refresh and displays the frame
 * ----------------------------------------------------  */
void Epd::DisplayFrame(const unsigned char* frame_buffer_black, const unsigned char* frame_buffer_red) 
{
    if (frame_buffer_black != NULL) 
    {
        SendCommand(0x24);
        DelayMs(2);
        for (unsigned int i = 0; i < this->width * this->height / 8; i++) 
        {
            SendData(pgm_read_byte(&frame_buffer_black[i]));
        }
        DelayMs(2);
    }
    if (frame_buffer_red != NULL) 
    {
        SendCommand(0x26);
        DelayMs(2);
        for (unsigned int i = 0; i < this->width * this->height / 8; i++) 
        {
            SendData(pgm_read_byte(&frame_buffer_red[i]));
        }
        DelayMs(2);
    }
    //--- update
    SendCommand(0x22);
    SendData(0xF7);
    SendCommand(0x20);  //--- activate Display Update Sequence
    
    WaitUntilIdle();
}

/** ----------------------------------------------------
 * @brief: clear the frame data from the SRAM, this won't refresh the display
 * ----------------------------------------------------  */
void Epd::ClearFrame(void) 
{    
    /* TRACE(); */
/* 
    DUMP(width);
    DUMP(height);
    DUMP(width * height / 8);
 */  
    //--- write RAM for black(0)/white (1)      
    SendCommand(0x24);
    DelayMs(2);
    
    for(unsigned int i = 0; i < width * height / 8; i++) 
    {
        SendData(0xFF);  
    }  
    delay(2);

    //--- write RAM for red(0)/white (0)      
    SendCommand(0x26);           
    delay(2);
    for(unsigned int i = 0; i < width * height / 8; i++) 
    {
        SendData(0x00);  
    }  
    delay(2); 

    UpdateDisplay(); 
}

/** ----------------------------------------------------
 * @brief: This displays the frame data from SRAM
 * ----------------------------------------------------  */
void Epd::DisplayFrame(void) 
{
    SendCommand(0x22); //--- DISPLAY_REFRESH
    WaitUntilIdle();
}

/** ----------------------------------------------------
 * @brief: After this command is transmitted, the chip would enter the deep-sleep mode to save power. 
 *         The deep sleep mode would return to standby by hardware reset. The only one parameter is a 
 *         check code, the command would be executed if check code = 0xA5. 
 *         You can use Epd::ResetDisplay() to awaken and use Epd::Init() to initialize.
 * ----------------------------------------------------  */
void Epd::DeepSleep() 
{
  SendCommand(0x10);    //--- DEEP_SLEEP
  SendData(0x01);
  delay(100); 
}
//--------------------------------------------------------------------------------------------
void Epd::UpdateDisplay(void)
{
    SendCommand(0x22);  //--- Display Update Control
    SendData(0xF7);   
    SendCommand(0x20);  //--- Activate Display Update Sequence  
    WaitUntilIdle();   
}
//--------------------------------------------------------------------------------------------
void Epd::Update_Fast(void)
{
  SendCommand(0x22); //Display Update Control
  SendData(0xC7);
  SendCommand(0x20); //Activate Display Update Sequence
  WaitUntilIdle();
}
//--------------------------------------------------------------------------------------------
void Epd::Part_Update(void)
{
  SendCommand(0x22);//Display Update Control
  SendData(0xFF);
  SendCommand(0x20); //Activate Display Update Sequence
  WaitUntilIdle();
}
/******************************************************************************
function :	EndlessLoop for ESP-watchdog
parameter:
******************************************************************************/
void Epd::EndlessLoop(void)
{
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
/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper 
parameter:
******************************************************************************/
void Epd::fillScreenBuffer(uint16_t color)
{
//   uint8_t data = (color == GxEPD_BLACK) ? 0xFF : 0x00;
//   //for (uint16_t x = 0; x < sizeof(_buffer); x++)
//   for(unsigned int x = 0; x < width * height / 8; x++) 
//   {
//     //Todo Puffer klären
//     //image[x] = data;
//   }
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper 
parameter:
******************************************************************************/
void Epd::Display_Base(uint8_t *Image)
{
	uint16_t i;   

	SendCommand(0x24);   //Write Black and White image to RAM
	for(i=0;i<4736;i++)
	{               
		SendData(Image[i]);
	}
	SendCommand(0x26);   //Write Black and White image to RAM
	for(i=0;i<4736;i++)
	{               
		SendData(Image[i]);
	}
	TurnOnDisplay();	
}
/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void Epd::DisplayBuffer(uint8_t *Image)
{
	uint16_t i;	
	SendCommand(0x24);   //write RAM for black(0)/white (1)
	for(i=0;i<4736;i++)
	{
		SendData(Image[i]);
	}
	TurnOnDisplay();	
}
/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
void Epd::TurnOnDisplay(void)
{
    SendCommand(0x22); // DISPLAY_UPDATE_CONTROL_2
    SendData(0xF7);
    SendCommand(0x20); // MASTER_ACTIVATION
    WaitUntilIdle();
}
/******************************************************************************
function :	TurnOnDisplay_Partial
parameter:
******************************************************************************/
void Epd::TurnOnDisplay_Partial(void)
{
    SendCommand(0x22); // DISPLAY_UPDATE_CONTROL_2
    SendData(0xFF);
    SendCommand(0x20); // MASTER_ACTIVATION
    WaitUntilIdle();
}
/******************************************************************************
function :	fill LUT-registers
parameter:
******************************************************************************/
void Epd::LoadLookUpTable(void)
{       
	uint8_t count;
	SendCommand(0x32);
	for(count=0; count<153; count++) 
		SendData(PARTIAL_LUT[count]);          //SendData(_WF_PARTIAL_2IN9[count]); 
	WaitUntilIdle();
}

/******************************************************************************
function :	Display_Partial 
parameter:
******************************************************************************/
// void Epd::Display_Partial(uint8_t *Image)
// {
// 	uint16_t i;

// //Reset
//     ResetDisplay(); 		
// 	LoadLookUpTable();

// 	SendCommand(0x37); 
// 	SendData(0x00);  
// 	SendData(0x00);  
// 	SendData(0x00);  
// 	SendData(0x00); 
// 	SendData(0x00);  
// 	SendData(0x40);  
// 	SendData(0x00);  
// 	SendData(0x00);   
// 	SendData(0x00);  
// 	SendData(0x00);

// 	SendCommand(0x3C); //BorderWavefrom
// 	SendData(0x80);	

// 	SendCommand(0x22); 
// 	SendData(0xC0);   
// 	SendCommand(0x20); 
// 	WaitUntilIdle(); 
	
// 	SetWindows(0, 0, EPD_WIDTH-1, EPD_HEIGHT-1);
// 	SetCursor(0, 0);

// 	SendCommand(0x24);   //Write Black and White image-buffer to Display-RAM
// 	for(i=0;i<4736;i++)
// 	{
// 		SendData(Image[i]);
// 	} 
// 	TurnOnDisplay_Partial();
// }

/******************************************************************************
function :	Setting the display window
parameter:
******************************************************************************/
void Epd::SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    SendCommand(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
    SendData((Xstart >> 3) & 0xFF);
    SendData((Xend >> 3) & 0xFF);

    SendCommand(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
    SendData(Ystart & 0xFF);
    SendData((Ystart >> 8) & 0xFF);
    SendData(Yend & 0xFF);
    SendData((Yend >> 8) & 0xFF);
}

/******************************************************************************
function :	Set Cursor
parameter:
******************************************************************************/
void Epd::SetCursor(uint16_t Xstart, uint16_t Ystart)
{
    SendCommand(0x4E);          // SET_RAM_X_ADDRESS_COUNTER
    SendData(Xstart & 0xFF);

    SendCommand(0x4F);          // SET_RAM_Y_ADDRESS_COUNTER
    SendData(Ystart & 0xFF);
    SendData((Ystart >> 8) & 0xFF);
}

//**********************************************************************
//--- <EOT>
//**********************************************************************

