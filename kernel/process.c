#include "process.h"
#include "memory.h"
#include "../include/print.h"
#include "../include/string.h"

static process_manager_t process_manager;

void process_init() {
    process_manager.process_count = 0;
    process_manager.next_pid = 1;
    process_manager.current_process = 0;
    
    // Initialize all processes
    for (int i = 0; i < MAX_PROCESSES; i++) {
        process_manager.processes[i].pid = 0;
        process_manager.processes[i].state = PROCESS_TERMINATED;
        process_manager.processes[i].next = 0;
    }
}

uint32_t create_process(const char* name, void (*entry_point)(), uint32_t priority) {
    if (process_manager.process_count >= MAX_PROCESSES) {
        return 0; // No space for new process
    }
    
    process_t* proc = &process_manager.processes[process_manager.process_count];
    proc->pid = process_manager.next_pid++;
    
    // Copy name
    int i = 0;
    while (i < PROCESS_NAME_LENGTH - 1 && name[i]) {
        proc->name[i] = name[i];
        i++;
    }
    proc->name[i] = 0;
    
    proc->state = PROCESS_READY;
    proc->priority = priority;
    proc->stack_pointer = 0;
    proc->memory_base = 0;
    proc->memory_size = 4096; // 4KB default
    proc->cpu_time = 0;
    proc->next = 0;
    
    // Allocate memory for process
    proc->memory_base = (uint32_t)kmalloc(proc->memory_size);
    if (!proc->memory_base) {
        return 0; // Failed to allocate memory
    }
    
    process_manager.process_count++;
    return proc->pid;
}

void terminate_process(uint32_t pid) {
    for (int i = 0; i < process_manager.process_count; i++) {
        if (process_manager.processes[i].pid == pid) {
            process_manager.processes[i].state = PROCESS_TERMINATED;
            
            // Free memory
            if (process_manager.processes[i].memory_base) {
                kfree((void*)process_manager.processes[i].memory_base);
            }
            
            // Shift processes down
            for (int j = i; j < process_manager.process_count - 1; j++) {
                process_manager.processes[j] = process_manager.processes[j + 1];
            }
            process_manager.process_count--;
            break;
        }
    }
}

void schedule() {
    // Simple round-robin scheduler
    if (process_manager.process_count == 0) return;
    
    static int current_index = 0;
    
    if (process_manager.current_process) {
        process_manager.current_process->state = PROCESS_READY;
    }
    
    // Find next ready process
    for (int i = 0; i < process_manager.process_count; i++) {
        current_index = (current_index + 1) % process_manager.process_count;
        if (process_manager.processes[current_index].state == PROCESS_READY) {
            process_manager.current_process = &process_manager.processes[current_index];
            process_manager.current_process->state = PROCESS_RUNNING;
            process_manager.current_process->cpu_time++;
            break;
        }
    }
}

void process_info() {
    print("=== Process Information ===\n");
    print("Active Processes: ");
    print_num(process_manager.process_count);
    print("\n");
    
    if (process_manager.current_process) {
        print("Current Process: ");
        print(process_manager.current_process->name);
        print(" (PID: ");
        print_num(process_manager.current_process->pid);
        print(")\n");
    }
    
    print("Process List:\n");
    for (int i = 0; i < process_manager.process_count; i++) {
        print("  PID: ");
        print_num(process_manager.processes[i].pid);
        print(" | Name: ");
        print(process_manager.processes[i].name);
        print(" | State: ");
        
        switch (process_manager.processes[i].state) {
            case PROCESS_READY:
                print("READY");
                break;
            case PROCESS_RUNNING:
                print("RUNNING");
                break;
            case PROCESS_BLOCKED:
                print("BLOCKED");
                break;
            case PROCESS_TERMINATED:
                print("TERMINATED");
                break;
        }
        
        print(" | Priority: ");
        print_num(process_manager.processes[i].priority);
        print(" | CPU Time: ");
        print_num(process_manager.processes[i].cpu_time);
        print("\n");
    }
}

process_t* get_process(uint32_t pid) {
    for (int i = 0; i < process_manager.process_count; i++) {
        if (process_manager.processes[i].pid == pid) {
            return &process_manager.processes[i];
        }
    }
    return 0;
}

process_t* get_current_process() {
    return process_manager.current_process;
}
