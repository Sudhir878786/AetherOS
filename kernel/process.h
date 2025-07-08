#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdint.h>

#define MAX_PROCESSES 32
#define PROCESS_NAME_LENGTH 32

typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_BLOCKED,
    PROCESS_TERMINATED
} process_state_t;

typedef struct process {
    uint32_t pid;
    char name[PROCESS_NAME_LENGTH];
    process_state_t state;
    uint32_t priority;
    uint32_t stack_pointer;
    uint32_t memory_base;
    uint32_t memory_size;
    uint32_t cpu_time;
    struct process* next;
} process_t;

typedef struct {
    process_t processes[MAX_PROCESSES];
    int process_count;
    uint32_t next_pid;
    process_t* current_process;
} process_manager_t;

// Process management functions
void process_init();
uint32_t create_process(const char* name, void (*entry_point)(), uint32_t priority);
void terminate_process(uint32_t pid);
void schedule();
void process_info();
process_t* get_process(uint32_t pid);
process_t* get_current_process();

#endif
