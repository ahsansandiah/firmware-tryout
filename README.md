# Firmware Example (Skeleton)

Lokasi: `firmware_example/`

Contoh ini hanya rangka dasar untuk mikrokontroler kontrol car wash:
- State machine sederhana (IDLE → READY → RUNNING → FAULT).
- Placeholder HAL: init, watchdog, E-stop, kesehatan komunikasi/sensor, supply voltage, output off, langkah wash.
- Health check: E-stop, komunikasi, sensor, tegangan suplai.
- Logging stub.

Cara pakai:
1) Pilih toolchain (mis. ARM GCC + CMake/Make atau STM32CubeIDE).
2) Map fungsi `hal_*` ke hardware nyata (GPIO/ADC/PWM/CAN/RS485/UART, driver motor, proteksi).
3) Tambah scheduler (RTOS atau tick interrupt) dan protokol (CAN/RS485) untuk perintah/telemetri.
4) Implementasi OTA/secure boot jika butuh update jarak jauh.

CMake + VS Code (contoh):
- Pastikan `arm-none-eabi-gcc` dan `cmake` ada di PATH.
- `CMakeLists.txt` + `toolchain-arm-gcc.cmake` sudah disiapkan (target Cortex-M4).
- Di VS Code jalankan task:
  - Configure: Command Palette → “Tasks: Run Task” → “CMake: Configure”
  - Build: “Tasks: Run Task” → “CMake: Build”

Build cepat tanpa CMake:
- Task “Build (arm-none-eabi-gcc direct)” menjalankan satu perintah gcc di folder ini.

Catatan:
- Semua `TODO` harus disesuaikan dengan pinout, tegangan, dan urutan logika mesin Anda.
- Tidak ada dependensi eksternal; file ini dimaksudkan sebagai titik awal.
