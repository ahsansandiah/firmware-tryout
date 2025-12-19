# Firmware TryOUT (Skeleton)

Basic firmware scaffold for a car wash controller.

What’s inside:
- Simple state machine: IDLE → READY → RUNNING → FAULT.
- HAL placeholders: init, watchdog, E-stop, comms/sensor status, supply voltage, outputs off, wash step, logging.
- Health checks: E-stop, comms, sensors, supply voltage.

How to use:
1) Choose a toolchain (e.g., ARM GCC + CMake/Make or STM32CubeIDE).
2) Map `hal_*` functions to real hardware (GPIO/ADC/PWM/CAN/RS485/UART, motor drivers, protections).
3) Add a scheduler (RTOS or tick interrupt) and protocol (CAN/RS485) for commands/telemetry.
4) Implement OTA/secure boot if you need remote updates.

CMake + VS Code (example):
- Ensure `arm-none-eabi-gcc` and `cmake` are in PATH.
- Use `CMakeLists.txt` + `toolchain-arm-gcc.cmake` (Cortex-M4 target).
- Run tasks in VS Code:
  - Configure: Command Palette → “Tasks: Run Task” → “CMake: Configure”
  - Build: “Tasks: Run Task” → “CMake: Build”

Quick build without CMake:
- Task “Build (arm-none-eabi-gcc direct)” runs a single gcc command in this folder.

Notes:
- All `TODO`s must match your pinout, voltages, and machine logic.
- No external dependencies; this file is a starting point.
