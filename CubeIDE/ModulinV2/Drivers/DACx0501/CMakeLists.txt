cmake_minimum_required(VERSION 3.22)

add_library(DACx0501 STATIC
    DACx0501.c
)

# Link dependencies for this library
target_link_libraries(DACx0501 PRIVATE stm32cubemx)