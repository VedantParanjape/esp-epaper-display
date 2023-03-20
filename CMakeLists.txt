set(srcs "epdif.cpp" "epdpaint.cpp" "font8.c" "font12.c" "font16.c" "font20.c" "font24.c")

if(CONFIG_EPD_1_54_V2)
    list(APPEND srcs "epd1in54_V2.cpp")
elseif(CONFIG_EPD_2_13_D)
    list(APPEND srcs "epd2in13d.cpp")
elseif(CONFIG_EPD_2_7)
    list(APPEND srcs "epd2in7.cpp")
endif()

string(REGEX MATCH "([0-9]+).([0-9])" VERSION ${IDF_VER})
string(REPLACE "." ";" VERSION_LIST ${VERSION})
list(GET ${VERSION_LIST} 0 VERSION_MAJOR)
if(${VERSION_MAJOR} LESS 4)
    add_compile_definitions(ESP_IDF_VERSION_MAJOR=${VERSION_MAJOR})
    list(GET ${VERSION_LIST} 0 VERSION_MINOR)
    add_compile_definitions(ESP_IDF_VERSION_MINOR=${VERSION_MINOR})
endif()
idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "include"
                       REQUIRES esp_common driver)