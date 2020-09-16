/**
 *  @filename   :   epd1in54-demo.ino
 *  @brief      :   1.54inch e-paper display demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     September 5 2017
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

#include "epd1in54_V2.h"
#include "epdpaint.h"
#include "imagedata.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"

static const char * kEPDTAG = "EPD";

Epd epd;

unsigned long time_start_ms;
unsigned long time_now_s;

#define COLORED     0
#define UNCOLORED   1

extern "C" void app_main() 
{
  unsigned char* frame = (unsigned char*)malloc(epd.width * epd.height / 8);
  unsigned char* frame_ = (unsigned char*)malloc(epd.width * epd.height / 8);

  Paint paint(frame, epd.width, epd.height);
  Paint paint_(frame_, epd.width, epd.height);
  paint.Clear(UNCOLORED);
  paint_.Clear(UNCOLORED);

  ESP_LOGI(kEPDTAG, "e-Paper init and clear");
  epd.LDirInit();
  epd.Clear();

  // paint.DrawStringAt(10, 10, "hello world", &Font20, COLORED);
  // epd.Display(frame);

  int d = 3;
  for (char i = '0'; i <= '9'; i++)
  {
    // paint_.Clear(UNCOLORED);
    paint_.DrawCharAt(d, d, i, &Font20, COLORED);
    epd.DisplayPart(frame_);
    // epd.DisplayPart(frame);
    vTaskDelay(100);
    d = d + 20; 
  }
  epd.Sleep();
}

