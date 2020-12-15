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
#ifndef __EPD_2IN7_H_
#define __EPD_2IN7_H_

// Display resolution
#define EPD_WIDTH   176
#define EPD_HEIGHT  264

#define HIGH 1
#define LOW 0

#ifdef __cplusplus
extern "C" {
#endif

#include "epdif.h"

class Epd : EpdIf {
public:
    unsigned long width;
    unsigned long height;

    Epd();
    ~Epd();
    int Init(void);
	int Init_4Gray(void);
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void ReadBusy(void);
    void SetLut(void);
    void SetgrayLut(void);
    
    void Reset(void);
    void Clear(void);
    void Display(const unsigned char* frame_buffer);
	void GrayDisplay(const unsigned char* frame_buffer);
    
    void Sleep(void);
private:
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;
};
#ifdef __cplusplus
}
#endif

#endif