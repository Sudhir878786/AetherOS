#include "../cpu/gdt.h"
#include "../cpu/idt.h"
#include "../cpu/irq.h"
#include "../cpu/timer.h"
#include "../cpu/kb.h"
#include "../include/print.h"
#include "../include/input.h"
#include "../include/about.h"
#include "../user/shell/shell.h"
#include "../user/taskbar/taskbar.h"
#include "memory.h"
#include "process.h"
#include "filesystem.h"
#include "network.h"

void main(){
clear(0xf0);
print_color("\n========== AETHER OS BOOTLOADER ==========\n", 0xfc);

// Initialize all subsystems
memory_init();
print_color("Initializing Memory Manager............[OK]\n", 0xf9);

process_init();
print_color("Loading GDT............................[OK]\n", 0xf9);
print_color("Loading ISR............................[OK]\n", 0xf9);

irq_install();
print_color("Loading IRQ............................[OK]\n", 0xf9);

timer_install();
print_color("Loading Timer..........................[OK]\n", 0xf9);

keyboard_install();
print_color("Loading Keyboard.......................[OK]\n", 0xf9);

print_color("Loading Process Manager................[OK]\n", 0xf9);

filesystem_init();
print_color("Loading File System....................[OK]\n", 0xf9);

network_init();
print_color("Loading Network Stack..................[OK]\n", 0xf9);

print_color("Loading Shell..........................[OK]\n", 0xf9);

print_color("\n========== BOOT COMPLETE ==========\n", 0xfc);
print_color("Welcome to AetherOS v2.0!\n", 0xfa);
print_color("Advanced Operating System - Type 'help' for commands\n\n", 0xf7);

int i=0;
for(i=0;i<COLS;i++){
print("_");
}

os_about();
taskbar();
shell();
	
}
