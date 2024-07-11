# Compiler and linker
CC = gcc
CXX = g++
AS = nasm
LD = ld

# Flags
CFLAGS = -m32 -O2 -Wall -fno-exceptions -fno-rtti -ffreestanding -fno-builtin -nostdlib -nostartfiles -I$(SRC_DIR)/include
CXXFLAGS = $(CFLAGS) -std=c++11 -fno-use-cxa-atexit -fno-threadsafe-statics
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -static -nostdlib -T firmware.ld

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Source files
C_SRCS = $(wildcard $(SRC_DIR)/*.c)
CXX_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
ASM_SRCS = $(wildcard $(SRC_DIR)/boot/*.s)

# Object files
C_OBJS = $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CXX_OBJS = $(CXX_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
ASM_OBJS = $(ASM_SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)
OBJS = $(C_OBJS) $(CXX_OBJS) $(ASM_OBJS)

# Target executable
TARGET = $(BIN_DIR)/firmware

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(LD) $(LDFLAGS) -o $@ $^

# Compile C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Assemble
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Run in QEMU
run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

# Debug with GDB
debug: $(TARGET)
	qemu-system-i386 -kernel $(TARGET) -s -S &
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(TARGET)"

# Phony targets
.PHONY: all clean run debug