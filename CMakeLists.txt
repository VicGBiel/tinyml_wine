# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(wine_ml C CXX ASM)
pico_sdk_init()

add_subdirectory(lib/pico-tflmicro EXCLUDE_FROM_ALL)

add_executable(wine_ml
    wine_ml.c
    tflm_wrapper.cpp
    tflm_wrapper.h
    wine_mlp_float.h
    wine_dataset.h
    wine_normalization.h
)

pico_set_program_name(wine_ml "wine_ml")
pico_set_program_version(wine_ml "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(wine_ml 0)
pico_enable_stdio_usb(wine_ml 1)

# Add the standard library to the build
target_link_libraries(wine_ml
        pico_stdlib
        hardware_sync
        pico-tflmicro
        )

# Add the standard include files to the build
target_include_directories(wine_ml PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(wine_ml 
        
        )

pico_add_extra_outputs(wine_ml)

