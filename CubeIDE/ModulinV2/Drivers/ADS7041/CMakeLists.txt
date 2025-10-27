cmake_minimum_required(VERSION 3.22)

add_library(ADS7041 STATIC
    ADS7041.c
)

# Link dependencies for this library
target_link_libraries(ADS7041 PRIVATE stm32cubemx)