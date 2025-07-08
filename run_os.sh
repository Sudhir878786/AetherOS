#!/bin/bash

echo "========== MAYA OS RUNNER =========="
echo "Building Maya OS..."

# Clean previous build
make clean 2>/dev/null || true

# Build the OS
echo "Step 1: Building loader..."
make loader || exit 1

echo "Step 2: Building kernel..."
make kern || exit 1

echo "Step 3: Linking..."
make link || exit 1

echo "Step 4: Cleaning object files..."
make clean || exit 1

echo "Build completed successfully!"
echo "Starting Maya OS in QEMU..."
echo "Press Ctrl+Alt+G to release mouse capture"
echo "Press Ctrl+Alt+2 to access QEMU monitor"
echo "Press Ctrl+Alt+1 to return to OS"
echo "To exit QEMU, press Ctrl+A then X"
echo "======================================"

# Run the OS
qemu-system-x86_64 -kernel kernel.bin
