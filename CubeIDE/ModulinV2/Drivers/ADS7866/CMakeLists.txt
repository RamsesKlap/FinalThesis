cmake_minimum_required(VERSION 3.22)

add_library(ADS7866 STATIC
    ADS7866.c
)

# Link dependencies for this library
target_link_libraries(ADS7866 PRIVATE stm32cubemx)