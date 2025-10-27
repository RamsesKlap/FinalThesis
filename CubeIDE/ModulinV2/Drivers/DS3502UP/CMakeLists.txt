cmake_minimum_required(VERSION 3.22)

add_library(DS3502UP STATIC
    DS3502UP.c
)

# Link dependencies for this library
target_link_libraries(DS3502UP PRIVATE stm32cubemx)