<br />
<p align="center">
  <a href="https://github.com/VedantParanjape/esp-epaper-display">
    <img src="assets/logo.png" alt="Logo" width="400" height="200">
  </a>

  <p align="center">
    ESP-IDF component for Waveshare epaper displays
    <br/>
    <br/>
    <a href="https://github.com/VedantParanjape/esp-epaper-display/issues">Report Bug</a>
    ·
    <a href="https://github.com/VedantParanjape/esp-epaper-display/issues">Request Feature</a>
    ·
    <a href="https://github.com/VedantParanjape/esp-epaper-display/pulls">Send a Pull Request</a>
  </p>
</p>

<p align="center">
<img src="https://img.shields.io/github/stars/VedantParanjape/esp-epaper-display">
<img src="https://img.shields.io/github/forks/VedantParanjape/esp-epaper-display">
<img src="https://img.shields.io/github/issues/VedantParanjape/esp-epaper-display">
<img src="https://img.shields.io/github/repo-size/VedantParanjape/esp-epaper-display">
</p>

# ESP32 Epaper Display component
ESP-IDF Component for driving waveshare's epaper displays. This is a port of Waveshare's official code for driving epaper display.     
* [1.54" V2 module](https://www.waveshare.com/wiki/1.54inch_e-Paper_Module)  

## Installation

```
cd <your_esp_idf_project>
mkdir components
cd components
git clone https://github.com/VedantParanjape/esp-epaper-display.git epaper
```

Change CMakeList.txt to add the line given below:

`set(EXTRA_COMPONENT_DIRS <relative_path_to_component_folder>)`

component folder must contain `epaper` component

## Configuration

Set the pins used in menuconfig

```bash
idf.py menuconfig
```

## Example code

```c
#include "epaper.h"
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
  unsigned char* frame_ = (unsigned char*)malloc(epd.width * epd.height / 8);

  Paint paint_(frame_, epd.width, epd.height);
  paint_.Clear(UNCOLORED);

  ESP_LOGI(kEPDTAG, "e-Paper init and clear");
  epd.LDirInit();
  epd.Clear();

  int d = 3;
  for (char i = '0'; i <= '9'; i++)
  {
    paint_.DrawCharAt(d, d, i, &Font20, COLORED);
    epd.DisplayPart(frame_);
    vTaskDelay(100);
    d = d + 20; 
  }
  epd.Sleep();
}
```

# Credits
* Thanks to ayoy, this code is based on this [repository](https://github.com/ayoy/esp32-waveshare-epd)
* Thanks to waveshare for sharing [arduino codes](https://github.com/waveshare/e-Paper/tree/master/Arduino) for epaper display