#include "filesystem.h"
#include "memory.h"
#include "../include/print.h"
#include "../include/string.h"

static filesystem_t filesystem;
static uint32_t system_time = 0;

void filesystem_init() {
    filesystem.file_count = 0;
    filesystem.root_directory = &filesystem.files[0];
    filesystem.current_directory = filesystem.root_directory;
    
    // Initialize root directory
    int i = 0;
    while (i < MAX_FILENAME_LENGTH - 1 && "/root"[i]) {
        filesystem.root_directory->name[i] = "/root"[i];
        i++;
    }
    filesystem.root_directory->name[i] = 0;
    
    filesystem.root_directory->type = FILE_TYPE_DIRECTORY;
    filesystem.root_directory->size = 0;
    filesystem.root_directory->created_time = system_time++;
    filesystem.root_directory->modified_time = system_time;
    filesystem.root_directory->permissions = 0755;
    filesystem.root_directory->data = 0;
    filesystem.root_directory->parent = 0;
    filesystem.root_directory->next = 0;
    
    filesystem.file_count = 1;
    
    // Create some default files
    create_file("readme.txt", FILE_TYPE_REGULAR);
    create_file("bin", FILE_TYPE_DIRECTORY);
    create_file("tmp", FILE_TYPE_DIRECTORY);
}

file_t* create_file(const char* name, file_type_t type) {
    if (filesystem.file_count >= MAX_FILES) {
        return 0;
    }
    
    file_t* file = &filesystem.files[filesystem.file_count];
    
    // Copy name
    int i = 0;
    while (i < MAX_FILENAME_LENGTH - 1 && name[i]) {
        file->name[i] = name[i];
        i++;
    }
    file->name[i] = 0;
    
    file->type = type;
    file->size = 0;
    file->created_time = system_time++;
    file->modified_time = system_time;
    file->permissions = (type == FILE_TYPE_DIRECTORY) ? 0755 : 0644;
    file->data = 0;
    file->parent = filesystem.current_directory;
    file->next = 0;
    
    // Allocate data buffer for regular files
    if (type == FILE_TYPE_REGULAR) {
        file->data = (uint8_t*)kmalloc(MAX_FILE_SIZE);
        if (!file->data) {
            return 0;
        }
    }
    
    filesystem.file_count++;
    return file;
}

int delete_file(const char* name) {
    for (int i = 0; i < filesystem.file_count; i++) {
        if (strcmp(filesystem.files[i].name, name) == 1) {
            // Free data if allocated
            if (filesystem.files[i].data) {
                kfree(filesystem.files[i].data);
            }
            
            // Shift files down
            for (int j = i; j < filesystem.file_count - 1; j++) {
                filesystem.files[j] = filesystem.files[j + 1];
            }
            filesystem.file_count--;
            return 1;
        }
    }
    return 0;
}

file_t* find_file(const char* name) {
    for (int i = 0; i < filesystem.file_count; i++) {
        if (strcmp(filesystem.files[i].name, name) == 1) {
            return &filesystem.files[i];
        }
    }
    return 0;
}

int read_file(const char* name, uint8_t* buffer, uint32_t size) {
    file_t* file = find_file(name);
    if (!file || file->type != FILE_TYPE_REGULAR) {
        return -1;
    }
    
    uint32_t bytes_to_read = (size < file->size) ? size : file->size;
    for (uint32_t i = 0; i < bytes_to_read; i++) {
        buffer[i] = file->data[i];
    }
    
    return bytes_to_read;
}

int write_file(const char* name, const uint8_t* buffer, uint32_t size) {
    file_t* file = find_file(name);
    if (!file) {
        file = create_file(name, FILE_TYPE_REGULAR);
        if (!file) return -1;
    }
    
    if (file->type != FILE_TYPE_REGULAR) {
        return -1;
    }
    
    uint32_t bytes_to_write = (size < MAX_FILE_SIZE) ? size : MAX_FILE_SIZE;
    for (uint32_t i = 0; i < bytes_to_write; i++) {
        file->data[i] = buffer[i];
    }
    
    file->size = bytes_to_write;
    file->modified_time = system_time++;
    return bytes_to_write;
}

void list_files() {
    print("=== File Listing ===\n");
    print("Current Directory: ");
    print(filesystem.current_directory->name);
    print("\n");
    
    for (int i = 0; i < filesystem.file_count; i++) {
        if (filesystem.files[i].parent == filesystem.current_directory) {
            switch (filesystem.files[i].type) {
                case FILE_TYPE_DIRECTORY:
                    print("[DIR]  ");
                    break;
                case FILE_TYPE_EXECUTABLE:
                    print("[EXE]  ");
                    break;
                default:
                    print("[FILE] ");
                    break;
            }
            
            print(filesystem.files[i].name);
            print(" (");
            print_num(filesystem.files[i].size);
            print(" bytes)\n");
        }
    }
}

int change_directory(const char* name) {
    file_t* dir = find_file(name);
    if (dir && dir->type == FILE_TYPE_DIRECTORY) {
        filesystem.current_directory = dir;
        return 1;
    }
    return 0;
}

file_t* get_current_directory() {
    return filesystem.current_directory;
}
