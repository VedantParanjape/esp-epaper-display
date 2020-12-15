/*****************************************************************************
* | File      	:   EPD_2in13d
* | Author      :   Waveshare team
* | Function    :   2.13inch e-paper d
* | Info        :
*----------------
* |	This version:   V4.0
* | Date        :   2019-12-31
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include <stdlib.h>
#include "epd2in7.h"

/**
 * full screen update LUT
**/

static const unsigned char EPD_2in7_lut_vcom_dc[] = {
    0x00	,0x00,
    0x00	,0x08	,0x00	,0x00	,0x00	,0x02,
    0x60	,0x28	,0x28	,0x00	,0x00	,0x01,
    0x00	,0x14	,0x00	,0x00	,0x00	,0x01,
    0x00	,0x12	,0x12	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00
};
static const unsigned char EPD_2in7_lut_ww[] = {
    0x40	,0x08	,0x00	,0x00	,0x00	,0x02,
    0x90	,0x28	,0x28	,0x00	,0x00	,0x01,
    0x40	,0x14	,0x00	,0x00	,0x00	,0x01,
    0xA0	,0x12	,0x12	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
static const unsigned char EPD_2in7_lut_bw[] = {
    0x40	,0x08	,0x00	,0x00	,0x00	,0x02,
    0x90	,0x28	,0x28	,0x00	,0x00	,0x01,
    0x40	,0x14	,0x00	,0x00	,0x00	,0x01,
    0xA0	,0x12	,0x12	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
static const unsigned char EPD_2in7_lut_bb[] = {
    0x80	,0x08	,0x00	,0x00	,0x00	,0x02,
    0x90	,0x28	,0x28	,0x00	,0x00	,0x01,
    0x80	,0x14	,0x00	,0x00	,0x00	,0x01,
    0x50	,0x12	,0x12	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
static const unsigned char EPD_2in7_lut_wb[] = {
    0x80	,0x08	,0x00	,0x00	,0x00	,0x02,
    0x90	,0x28	,0x28	,0x00	,0x00	,0x01,
    0x80	,0x14	,0x00	,0x00	,0x00	,0x01,
    0x50	,0x12	,0x12	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};

//////////////////////////////////////full screen update LUT////////////////////////////////////////////
//0~3 gray
static const unsigned char EPD_2in7_gray_lut_vcom[] = {
    0x00	,0x00,
    0x00	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x60	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x00	,0x14	,0x00	,0x00	,0x00	,0x01,
    0x00	,0x13	,0x0A	,0x01	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R21
static const unsigned char EPD_2in7_gray_lut_ww[] = {
    0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x10	,0x14	,0x0A	,0x00	,0x00	,0x01,
    0xA0	,0x13	,0x01	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R22H	r
static const unsigned char EPD_2in7_gray_lut_bw[] = {
    0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
    0x99	,0x0C	,0x01	,0x03	,0x04	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R23H	w
static const unsigned char EPD_2in7_gray_lut_wb[] = {
    0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
    0x99	,0x0B	,0x04	,0x04	,0x01	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R24H	b
static const unsigned char EPD_2in7_gray_lut_bb[] = {
    0x80	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x20	,0x14	,0x0A	,0x00	,0x00	,0x01,
    0x50	,0x13	,0x01	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};

Epd::~Epd()
{
};

Epd::Epd()
{
    reset_pin = RST_PIN;
    dc_pin = DC_PIN;
    cs_pin = CS_PIN;
    busy_pin = BUSY_PIN;
    width = EPD_WIDTH;
    height = EPD_HEIGHT;
};

/**
 *  @brief: basic function for sending commands
 */
void Epd::SendCommand(unsigned char command)
{
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void Epd::SendData(unsigned char data)
{
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void Epd::Reset(void)
{
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);
    DigitalWrite(reset_pin, LOW);                //module reset
    DelayMs(10);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void Epd::ReadBusy(void)
{
    ESP_LOGI("EPD", "ReadBusy");
    char busy;
    do {
        SendCommand(0x71);
        busy = DigitalRead(busy_pin);
        busy =!(busy & 0x01);
    } while(busy);
    ESP_LOGI("EPD", "ReadBusy over");
    DelayMs(200);
}

/******************************************************************************
function :	LUT download
parameter:
******************************************************************************/
void Epd::SetLut(void)
{
    unsigned int count;
    SendCommand(0x20); //vcom
    for(count = 0; count < 44; count++) {
        SendData(EPD_2in7_lut_vcom_dc[count]);
    }

    SendCommand(0x21); //ww --
    for(count = 0; count < 42; count++) {
        SendData(EPD_2in7_lut_ww[count]);
    }

    SendCommand(0x22); //bw r
    for(count = 0; count < 42; count++) {
        SendData(EPD_2in7_lut_bw[count]);
    }

    SendCommand(0x23); //wb w
    for(count = 0; count < 42; count++) {
        SendData(EPD_2in7_lut_bb[count]);
    }

    SendCommand(0x24); //bb b
    for(count = 0; count < 42; count++) {
        SendData(EPD_2in7_lut_wb[count]);
    }
}

/******************************************************************************
function :	LUT download
parameter:
******************************************************************************/
void Epd::SetgrayLut(void)
{
    unsigned int count;
    SendCommand(0x20);							//vcom
    for(count=0; count<44; count++) {
        SendData(EPD_2in7_gray_lut_vcom[count]);
    }

    SendCommand(0x21);							//red not use
    for(count=0; count<42; count++) {
        SendData(EPD_2in7_gray_lut_ww[count]);
    }

    SendCommand(0x22);							//bw r
    for(count=0; count<42; count++) {
        SendData(EPD_2in7_gray_lut_bw[count]);
    }

    SendCommand(0x23);							//wb w
    for(count=0; count<42; count++) {
        SendData(EPD_2in7_gray_lut_wb[count]);
    }

    SendCommand(0x24);							//bb b
    for(count=0; count<42; count++) {
        SendData(EPD_2in7_gray_lut_bb[count]);
    }

    SendCommand(0x25);							//vcom
    for(count=0; count<42; count++) {
        SendData(EPD_2in7_gray_lut_ww[count]);
    }
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
int Epd::Init()
{
    /* this calls the peripheral hardware interface, see epdif */
    if (IfInit() != 0) {
        return -1;
    }

    Reset();
    SendCommand(0x01);	//POWER SETTING
    SendData(0x03);
    SendData(0x00);
    SendData(0x2b);
    SendData(0x2b);
    SendData(0x09);

    SendCommand(0x06);	//boost soft start
    SendData(0x07);     //A
    SendData(0x07);     //B
    SendData(0x17);     //C

    // Power optimization
    SendCommand(0xF8);
    SendData(0x60);
    SendData(0xA5);

    // Power optimization
    SendCommand(0xF8);
    SendData(0x89);
    SendData(0xA5);

    // Power optimization
    SendCommand(0xF8);
    SendData(0x90);
    SendData(0x00);

    // Power optimization
    SendCommand(0xF8);
    SendData(0x93);
    SendData(0x2A);

    // Power optimization
    SendCommand(0xF8);
    SendData(0xA0);
    SendData(0xA5);

    // Power optimization
    SendCommand(0xF8);
    SendData(0xA1);
    SendData(0x00);

    // Power optimization
    SendCommand(0xF8);
    SendData(0x73);
    SendData(0x41);

    SendCommand(0x16); // PARTIAL_DISPLAY_REFRESH
    SendData(0x00);
	
	SendCommand(0x04); //Power_on
    ReadBusy();

    SendCommand(0x00);	//panel setting
    SendData(0xAF);     // KW-BF   KWR-AF    BWROTP 0f
    SendCommand(0x30); // PLL_CONTROL
    SendData(0x3A); // 3A 100HZ   29 150Hz 39 200HZ    31 171HZ
    SendCommand(0x82);  // VCM_DC_SETTING_REGISTER
    SendData(0x12);

    SetLut();

    return 0;
}
int Epd::Init_4Gray()
{
	/* this calls the peripheral hardware interface, see epdif */
    if (IfInit() != 0) {
        return -1;
    }
	
    Reset();
    SendCommand(0x01);			//POWER SETTING
    SendData (0x03);
    SendData (0x00);
    SendData (0x2b);
    SendData (0x2b);


    SendCommand(0x06);         //booster soft start
    SendData (0x07);		//A
    SendData (0x07);		//B
    SendData (0x17);		//C

    SendCommand(0xF8);         //boost??
    SendData (0x60);
    SendData (0xA5);

    SendCommand(0xF8);         //boost??
    SendData (0x89);
    SendData (0xA5);

    SendCommand(0xF8);         //boost??
    SendData (0x90);
    SendData (0x00);

    SendCommand(0xF8);         //boost??
    SendData (0x93);
    SendData (0x2A);

    SendCommand(0xF8);         //boost??
    SendData (0xa0);
    SendData (0xa5);

    SendCommand(0xF8);         //boost??
    SendData (0xa1);
    SendData (0x00);

    SendCommand(0xF8);         //boost??
    SendData (0x73);
    SendData (0x41);

    SendCommand(0x16);
    SendData(0x00);

    SendCommand(0x04);
    ReadBusy();

    SendCommand(0x00);			//panel setting
    SendData(0xbf);		//KW-BF   KWR-AF	BWROTP 0f

    SendCommand(0x30);			//PLL setting
    SendData (0x90);      	//100hz

    SendCommand(0x61);			//resolution setting
    SendData (0x00);		//176
    SendData (0xb0);
    SendData (0x01);		//264
    SendData (0x08);

    SendCommand(0x82);			//vcom_DC setting
    SendData (0x12);

    SendCommand(0X50);			//VCOM AND DATA INTERVAL SETTING
    SendData(0x97);
	
	return 0;
}


void Epd::Clear(void)
{
    int w, h;
    w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    h = EPD_HEIGHT;

    SendCommand(0x10);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            SendData(0xFF);
        }
    }

    SendCommand(0x13);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            SendData(0xFF);
        }
    }

    SendCommand(0x12);
    ReadBusy();
}


/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void Epd::Display(const unsigned char *Image)
{
    int Width, Height;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;

    SendCommand(0x10);
    for (int j = 0; j < Height; j++) {
        for (int i = 0; i < Width; i++) {
            SendData(0xFF);
        }
    }

    SendCommand(0x13);
    for (int j = 0; j < Height; j++) {
        for (int i = 0; i < Width; i++) {
            SendData(Image[i + j * Width]);
        }
    }

   SendCommand(0x12);
   ReadBusy();
}

void Epd::GrayDisplay(const unsigned char *Image)
{
    unsigned int i,j,k;
    unsigned char temp1,temp2,temp3;

    // old  data
    SendCommand(0x10);
    for(i=0; i<5808; i++) {             //5808*4  46464
        temp3=0;
        for(j=0; j<2; j++) {
            temp1 = Image[i*2+j];
            for(k=0; k<2; k++) {
                temp2 = temp1&0xC0;
                if(temp2 == 0xC0)
                    temp3 |= 0x01;//white
                else if(temp2 == 0x00)
                    temp3 |= 0x00;  //black
                else if(temp2 == 0x80)
                    temp3 |= 0x01;  //gray1
                else //0x40
                    temp3 |= 0x00; //gray2
                temp3 <<= 1;

                temp1 <<= 2;
                temp2 = temp1&0xC0 ;
                if(temp2 == 0xC0)  //white
                    temp3 |= 0x01;
                else if(temp2 == 0x00) //black
                    temp3 |= 0x00;
                else if(temp2 == 0x80)
                    temp3 |= 0x01; //gray1
                else    //0x40
                    temp3 |= 0x00;	//gray2
                if(j!=1 || k!=1)
                    temp3 <<= 1;

                temp1 <<= 2;
            }

        }
        SendData(temp3);
    }
    // new  data
    SendCommand(0x13);
    for(i=0; i<5808; i++) {             //5808*4  46464
        temp3=0;
        for(j=0; j<2; j++) {
            temp1 = Image[i*2+j];
            for(k=0; k<2; k++) {
                temp2 = temp1&0xC0 ;
                if(temp2 == 0xC0)
                    temp3 |= 0x01;//white
                else if(temp2 == 0x00)
                    temp3 |= 0x00;  //black
                else if(temp2 == 0x80)
                    temp3 |= 0x00;  //gray1
                else //0x40
                    temp3 |= 0x01; //gray2
                temp3 <<= 1;

                temp1 <<= 2;
                temp2 = temp1&0xC0 ;
                if(temp2 == 0xC0)  //white
                    temp3 |= 0x01;
                else if(temp2 == 0x00) //black
                    temp3 |= 0x00;
                else if(temp2 == 0x80)
                    temp3 |= 0x00; //gray1
                else    //0x40
                    temp3 |= 0x01;	//gray2
                if(j!=1 || k!=1)
                    temp3 <<= 1;

                temp1 <<= 2;
            }
        }
        SendData(temp3);
    }

    SetgrayLut();
    SendCommand(0x12);
    DelayMs(200);
    ReadBusy();
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void Epd::Sleep(void)
{
    SendCommand(0X50);
    SendData(0xf7);
    SendCommand(0X02);  	//power off
    SendCommand(0X07);  	//deep sleep
    SendData(0xA5);

    DigitalWrite(reset_pin, LOW);
}
