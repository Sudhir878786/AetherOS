#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

#define MEMORY_BLOCK_SIZE 4096
#define MAX_MEMORY_BLOCKS 1024
#define MEMORY_START_ADDR 0x100000

typedef struct memory_block {
    uint32_t address;
    uint32_t size;
    int is_free;
    struct memory_block* next;
} memory_block_t;

typedef struct {
    memory_block_t blocks[MAX_MEMORY_BLOCKS];
    int block_count;
    uint32_t total_memory;
    uint32_t free_memory;
} memory_manager_t;

// Memory management functions
void memory_init();
void* kmalloc(uint32_t size);
void kfree(void* ptr);
void memory_info();
uint32_t get_free_memory();
uint32_t get_total_memory();

#endif
