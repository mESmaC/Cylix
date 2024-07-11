# Cylix OS

Cylix OS is a lightweight operating system/firmware designed for single board computers. It provides a minimal environment for running bare-metal applications with basic timing and scheduling capabilities.

## Features

- Bare-metal 32-bit x86 environment
- Simple cooperative multitasking scheduler  
- Millisecond timer implementation
- VGA text mode display output
- Modular architecture for easy customization

## Building

To build Cylix OS, you need:

- GCC cross-compiler for i386 target
- NASM assembler
- GNU Make

Build steps:

1. Clone this repository
2. Run `make` in the root directory
3. The firmware binary will be output to `build/bin/firmware`

## Running

Cylix OS can be run on:

- Real x86 hardware
- QEMU x86 emulator 

To run in QEMU:

```
qemu-system-i386 -kernel build/bin/firmware
```

## Project Structure

- `src/` - Source code
  - `boot/` - Boot code and assembly routines  
  - `kernel/` - Core kernel functionality
  - `lib/` - Common library functions
  - `main.cpp` - Kernel entry point
- `include/` - Header files
- `build/` - Build output
- `firmware.ld` - Linker script

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
