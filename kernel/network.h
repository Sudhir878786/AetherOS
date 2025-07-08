#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdint.h>

#define MAX_NETWORK_INTERFACES 4
#define MAX_HOSTNAME_LENGTH 64
#define MAX_IP_LENGTH 16

typedef struct network_interface {
    char name[16];
    char ip_address[MAX_IP_LENGTH];
    char subnet_mask[MAX_IP_LENGTH];
    char gateway[MAX_IP_LENGTH];
    uint8_t mac_address[6];
    int is_active;
    uint32_t bytes_sent;
    uint32_t bytes_received;
} network_interface_t;

typedef struct network_stack {
    network_interface_t interfaces[MAX_NETWORK_INTERFACES];
    int interface_count;
    char hostname[MAX_HOSTNAME_LENGTH];
    int network_enabled;
} network_stack_t;

// Network functions
void network_init();
void network_info();
int ping_host(const char* hostname);
void set_hostname(const char* hostname);
char* get_hostname();
int add_interface(const char* name, const char* ip);
void show_interfaces();

#endif
