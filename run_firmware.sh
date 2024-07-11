#!/bin/bash

# Path to your firmware file
FIRMWARE="build/bin/firmware"

# Run QEMU with the firmware
qemu-system-i386 \
    -machine type=q35 \
    -cpu qemu32 \
    -m 2G \
    -kernel $FIRMWARE \
    -d in_asm,exec,cpu,int \
    -D qemu.log \
    -enable-kvm

# Clean up
rm -f qemu.log#!/bin/bash