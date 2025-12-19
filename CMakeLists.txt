cmake_minimum_required(VERSION 3.16)
project(firmware_example C CXX ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Toolchain flags (adjust to your MCU)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CLANG_COMMON_FLAGS "-ffunction-sections -fdata-sections -fno-builtin")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${MCU_FLAGS} ${CLANG_COMMON_FLAGS} -Wall -Wextra")

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -nostdlib -Wl,--gc-sections -Wl,-Map=firmware_example.map -T${LINKER_SCRIPT}")

add_executable(firmware_example.elf
    startup_minimal.c
    main.c
)

target_link_libraries(firmware_example.elf
    c
    m
    nosys
)

add_custom_command(TARGET firmware_example.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex firmware_example.elf firmware_example.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary firmware_example.elf firmware_example.bin
    COMMENT "Generating HEX and BIN"
)
