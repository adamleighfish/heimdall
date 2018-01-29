cmake_minimum_required(VERSION 2.8.3)
project (heimdall)

include_directories(
    # Heimdall includes
    include
)

add_executable(heimdall
    # Header files
    include/geometry.h
    
    # Source files
    src/main.cpp
)
