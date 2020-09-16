set(srcs "epd1in54_V2.cpp" "epdif.cpp" "epdpaint.cpp" "font8.c" "font12.c" "font16.c" "font20.c" "font24.c")

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "include"
                       REQUIRES )