cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Transmitter C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(Transmitter
        src/main.cpp
        lib/Transmitter_Class/Transmitter_Class.cpp
        lib/ADF4351_Synth/ADF4351_Synth.cpp
        lib/F1953_Att/F1953_Att.cpp
        lib/Latched_Serial_Write/Latched_Serial_Write.cpp
        lib/PA_Chain/PA_Chain.cpp
        lib/PRBS/PRBS.cpp
        lib/SKY13286_Switch/SKY13286_Switch.cpp
        )

# pull in common dependencies
target_link_libraries(Transmitter pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(Transmitter 1)
pico_enable_stdio_uart(Transmitter 0)

#debug option
add_definitions(-DDEBUG)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(Transmitter)