#ifndef EPAPER_H
#define EPAPER_H

#ifdef CONFIG_EPD_1_54_V2
#include "epd1in54_V2.h"

#elif CONFIG_EPD_2_13_D
#include "epd2in13d.h"

#else 
#include "epd1in54_V2.h"
#endif

#include "epdpaint.h"

#endif