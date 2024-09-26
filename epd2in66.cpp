/**
 *  @filename   :   epd2in66.cpp
 *  @brief      :   Implements for e-paper library
 *  @author     :   Waveshare
 *
 *  Copyright (C) Waveshare     July 29 2020
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

#include <stdlib.h>
#include "epd2in66.h"

static const UBYTE WF_PARTIAL[159] =
{
0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0A,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x22,0x22,0x22,0x22,0x22,0x22,
0x00,0x00,0x00,0x22,0x17,0x41,0xB0,0x32,0x36,
};

Epd::~Epd() {
};

Epd::Epd() {
    reset_pin = RST_PIN;
    dc_pin = DC_PIN;
    cs_pin = CS_PIN;
    busy_pin = BUSY_PIN;
    width = EPD_WIDTH;
    height = EPD_HEIGHT;
};

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void Epd::Reset(void) {
    DigitalWrite(reset_pin, LOW);                //module reset
    DelayMs(1);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);
}

/**
 *  @brief: Initialize the e-Paper register
 */
int Epd::Init(void) {
	if (IfInit() != 0) {
	  return -1;
	}
	Reset();

	WaitUntilIdle();
	SendCommand(0x12);//soft  reset
	WaitUntilIdle();
	/*	Y increment, X increment	*/
	SendCommand(0x11);
	SendData(0x03);
	/*	Set RamX-address Start/End position	*/
	SendCommand(0x44);
	SendData(0x01);
	SendData((width % 8 == 0)? (width / 8 ): (width / 8 + 1) );
	/*	Set RamY-address Start/End position	*/
	SendCommand(0x45);
	SendData(0);
	SendData(0);
	SendData((height&0xff));
	SendData((height&0x100)>>8);

	WaitUntilIdle();
	return 0;
}

/**
 *  @brief: Initialize the e-Paper register(Partial display)
 */
int Epd::Init_Partial(void) {
	  Reset();

    WaitUntilIdle();
    SendCommand(0x12);//soft  reset
    WaitUntilIdle();

    Load_LUT();
    SendCommand(0x37);
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

	/* Y increment, X increment */
    SendCommand(0x11);
    SendData(0x03);
    /*	Set RamX-address Start/End position	*/
    SendCommand(0x44);
    SendData(0x01);
    SendData((width % 8 == 0)? (width / 8 ): (width / 8 + 1) );
    /*	Set RamY-address Start/End position	*/
    SendCommand(0x45);
    SendData(0);
    SendData(0);
    SendData((height&0xff));
    SendData((height&0x100)>>8);

    SendCommand(0x3C);
    SendData(0x80);

    SendCommand(0x22);
    SendData(0xcf);
    SendCommand(0x20);
    WaitUntilIdle();
	  return 0;
}

/**
 *  @brief: basic function for sending commands
 */
void Epd::SendCommand(unsigned char command) {
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void Epd::SendData(unsigned char data) {
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes HIGH
 */
void Epd::WaitUntilIdle(void) {
	UBYTE busy;
	do
	{
	busy = DigitalRead(busy_pin);
	}
	while(busy);
	DelayMs(200);
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
void Epd::TurnOnDisplay(void)
{
    SendCommand(0x20);
    WaitUntilIdle();
}

/******************************************************************************
function :  Display Array data
******************************************************************************/
void Epd::DisplayFrame(const UBYTE *Image) {
    UWORD Width, Height;
    Width = (width % 8 == 0)? (width / 8 ): (width / 8 + 1);
    Height = height;

    SendCommand(0x24);
    for (UWORD j = 0; j <Height; j++) {
        for (UWORD i = 0; i <Width; i++) {
            SendData(pgm_read_byte(&Image[i + j * Width]));
        }
    }
    TurnOnDisplay();
}

/******************************************************************************
function :  Partial Display
******************************************************************************/
void Epd::DisplayFrame_part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD iwidth, UWORD iheight) {
    UWORD Width, Height;
    Width = (width % 8 == 0)? (width / 8 ): (width / 8 + 1);
    Height = height;

    SendCommand(0x24);
    for (UWORD j = 0; j<Height; j++) {
        for (UWORD i = 0; i <Width; i++) {
            if(j>=Ystart && j<Ystart+iheight && i>=Xstart/8 && i<(Xstart+iwidth)/8)
                SendData(Image[(i-Xstart/8) + (j-Ystart)*iwidth/8]);
            else
                SendData(0xff);
        }
    }
    TurnOnDisplay();
}


/******************************************************************************
function :  set the look-up tables
parameter:
******************************************************************************/
void Epd::Load_LUT(void) {
	UWORD i;
	SendCommand(0x32);
	for (i = 0; i < 153; i++) {
		SendData(WF_PARTIAL[i]);
	}
	WaitUntilIdle();
}

/******************************************************************************
function :  Clear Screen
parameter:
  mode: 0:just partial mode
        1:clear all
******************************************************************************/
void Epd::Clear(void) {
    UWORD Width, Height;
    Width = (width % 8 == 0)? (width / 8 ): (width / 8 + 1);
    Height = height;
    SendCommand(0x24);
    for (UWORD j = 0; j <=Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            SendData(0xff);
        }
    }
    TurnOnDisplay();
}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          You can use EPD_Reset() to awaken
 */
void Epd::Sleep(void) {
    SendCommand(0X10);
    SendData(0x01);
}

/* END OF FILE */