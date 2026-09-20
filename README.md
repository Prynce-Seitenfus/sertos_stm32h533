# SertOS STM32H533

This repository contains an STM32H533-based firmware project built around the `SertOS` real-time operating system kernel.

It is intended to complement the main `SertOS` kernel repository and provides a ready-to-build STM32H533 hardware target using CMake and the STM32CubeMX project file.

## Included project files

- `CMakeLists.txt` for the firmware build
- `CMakePresets.json` for common configure presets
- `startup_stm32h533xx.s` for the MCU startup code
- `STM32H533xx_FLASH.ld` and `STM32H533xx_RAM.ld` linker scripts
- `sertos_stm32h533.ioc` for STM32CubeMX project setup
- `Core/`, `Drivers/`, `cmake/` for the generated and custom build support

## Build

From a Windows shell:

```powershell
cmake -S . -B build
cmake --build build
```

This project is meant to be used with the core kernel repository:

- https://github.com/Prynce-Seitenfus/sertos

## License

MIT License. Copyright (c) 2026 Prynce Seitenfus.
