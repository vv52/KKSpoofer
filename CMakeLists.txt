cmake_minimum_required(VERSION 3.13)

set(PICO_PIO_USB_PATH "$ENV{PICO_PIO_USB_PATH}" CACHE PATH "Path to Pico-PIO-USB source code")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(kkspoofer C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    src/main.c
    src/usb-desc.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE PICO_ENTER_USB_BOOT_ON_EXIT=1)
target_compile_definitions(${PROJECT_NAME} PRIVATE PICO_PRINTF_ALWAYS_INCLUDED=1)

# Setup #define __GIT_REVISION__
execute_process(
    COMMAND git rev-parse --short HEAD
    OUTPUT_VARIABLE GITREV
    RESULT_VARIABLE GIT_RESULT
    ERROR_VARIABLE GIT_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(GIT_RESULT EQUAL 0)
    target_compile_definitions(${PROJECT_NAME} PRIVATE __GIT_REVISION__="${GITREV}")
else()
    message(WARNING "Failed to get git revision: ${GIT_ERROR}")
    target_compile_definitions(${PROJECT_NAME} PRIVATE __GIT_REVISION__="unknown")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/pico
    src/
)

add_subdirectory(${PICO_PIO_USB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/pico_pio_usb)

target_link_libraries(${PROJECT_NAME}
    tinyusb_device
    tinyusb_board
    tinyusb_host
    pico_multicore
    pico_stdlib
    pico_pio_usb
    hardware_clocks
)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})
