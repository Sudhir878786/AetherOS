#include "memory.h"
#include "../include/print.h"
#include "../include/string.h"

static memory_manager_t memory_manager;

void memory_init() {
    memory_manager.block_count = 0;
    memory_manager.total_memory = 16 * 1024 * 1024; // 16MB
    memory_manager.free_memory = memory_manager.total_memory;
    
    // Initialize first block
    memory_manager.blocks[0].address = MEMORY_START_ADDR;
    memory_manager.blocks[0].size = memory_manager.total_memory;
    memory_manager.blocks[0].is_free = 1;
    memory_manager.blocks[0].next = 0;
    memory_manager.block_count = 1;
}

void* kmalloc(uint32_t size) {
    if (size == 0) return 0;
    
    // Align size to 4 bytes
    size = (size + 3) & ~3;
    
    for (int i = 0; i < memory_manager.block_count; i++) {
        if (memory_manager.blocks[i].is_free && memory_manager.blocks[i].size >= size) {
            memory_manager.blocks[i].is_free = 0;
            
            // If block is larger than needed, split it
            if (memory_manager.blocks[i].size > size && memory_manager.block_count < MAX_MEMORY_BLOCKS - 1) {
                memory_manager.blocks[memory_manager.block_count].address = 
                    memory_manager.blocks[i].address + size;
                memory_manager.blocks[memory_manager.block_count].size = 
                    memory_manager.blocks[i].size - size;
                memory_manager.blocks[memory_manager.block_count].is_free = 1;
                memory_manager.blocks[memory_manager.block_count].next = 0;
                memory_manager.block_count++;
                
                memory_manager.blocks[i].size = size;
            }
            
            memory_manager.free_memory -= size;
            return (void*)memory_manager.blocks[i].address;
        }
    }
    
    return 0; // Out of memory
}

void kfree(void* ptr) {
    if (!ptr) return;
    
    uint32_t addr = (uint32_t)ptr;
    
    for (int i = 0; i < memory_manager.block_count; i++) {
        if (memory_manager.blocks[i].address == addr && !memory_manager.blocks[i].is_free) {
            memory_manager.blocks[i].is_free = 1;
            memory_manager.free_memory += memory_manager.blocks[i].size;
            
            // Simple coalescing - merge with next free block
            for (int j = 0; j < memory_manager.block_count; j++) {
                if (j != i && memory_manager.blocks[j].is_free && 
                    memory_manager.blocks[j].address == memory_manager.blocks[i].address + memory_manager.blocks[i].size) {
                    memory_manager.blocks[i].size += memory_manager.blocks[j].size;
                    // Remove block j by shifting
                    for (int k = j; k < memory_manager.block_count - 1; k++) {
                        memory_manager.blocks[k] = memory_manager.blocks[k + 1];
                    }
                    memory_manager.block_count--;
                    break;
                }
            }
            break;
        }
    }
}

void memory_info() {
    print("=== Memory Information ===\n");
    print("Total Memory: ");
    print_num(memory_manager.total_memory / 1024);
    print(" KB\n");
    print("Free Memory: ");
    print_num(memory_manager.free_memory / 1024);
    print(" KB\n");
    print("Used Memory: ");
    print_num((memory_manager.total_memory - memory_manager.free_memory) / 1024);
    print(" KB\n");
    print("Memory Blocks: ");
    print_num(memory_manager.block_count);
    print("\n");
}

uint32_t get_free_memory() {
    return memory_manager.free_memory;
}

uint32_t get_total_memory() {
    return memory_manager.total_memory;
}
