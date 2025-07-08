#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <stdint.h>

#define MAX_FILES 64
#define MAX_FILENAME_LENGTH 32
#define MAX_FILE_SIZE 4096

typedef enum {
    FILE_TYPE_REGULAR,
    FILE_TYPE_DIRECTORY,
    FILE_TYPE_EXECUTABLE
} file_type_t;

typedef struct file {
    char name[MAX_FILENAME_LENGTH];
    file_type_t type;
    uint32_t size;
    uint32_t created_time;
    uint32_t modified_time;
    uint32_t permissions;
    uint8_t* data;
    struct file* parent;
    struct file* next;
} file_t;

typedef struct {
    file_t files[MAX_FILES];
    int file_count;
    file_t* root_directory;
    file_t* current_directory;
} filesystem_t;

// File system functions
void filesystem_init();
file_t* create_file(const char* name, file_type_t type);
int delete_file(const char* name);
file_t* find_file(const char* name);
int read_file(const char* name, uint8_t* buffer, uint32_t size);
int write_file(const char* name, const uint8_t* buffer, uint32_t size);
void list_files();
int change_directory(const char* name);
file_t* get_current_directory();

#endif
