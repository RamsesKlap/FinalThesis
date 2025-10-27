cmake_minimum_required(VERSION 3.22)

add_library(ssd1306 STATIC
    ssd1306.c
    ssd1306_tests.c
    ssd1306_fonts.c
)

# Link dependencies for this library
target_link_libraries(ssd1306 PRIVATE stm32cubemx)