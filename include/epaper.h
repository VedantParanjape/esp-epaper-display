#ifndef EPAPER_H
#define EPAPER_H

#include "sdkconfig.h"

#ifdef CONFIG_EPD_1_54_V2
#include "epd1in54_V2.h"
#endif

#ifdef CONFIG_EPD_2_13_D
#include "epd2in13d.h"
#endif

#ifdef CONFIG_EPD_2_7
#include "epd2in7.h"
#endif

#include "epdpaint.h"

#endif