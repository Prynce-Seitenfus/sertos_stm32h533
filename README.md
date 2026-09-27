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
git submodule update --init --recursive
cmake -S . -B build
cmake --build build
```

The firmware builds the profiler module and records instrumented application
function entry/exit events in a statically allocated 1,024-event buffer. The
buffer wraps to retain recent events. The STM32H533 port uses the Cortex-M33
DWT cycle counter for timestamps.

To retrieve the captured events, open USART2 at 115200 baud, 8 data bits, no
parity, and 1 stop bit, then send `prof-dump` (optionally followed by a newline).
The firmware pauses capture while it streams the saved events over TX DMA as
CSV. The first line reports the event count, timestamp frequency, and whether
the event buffer overflowed; rows contain the index, timestamp, event type,
function address, and call-site address. If overflow is reported, older events
were overwritten and the dump contains only the retained events.

This project is meant to be used with the core kernel repository:

- https://github.com/Prynce-Seitenfus/sertos

## License

MIT License. Copyright (c) 2026 Prynce Seitenfus.
