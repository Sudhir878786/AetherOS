#include "network.h"
#include "../include/print.h"
#include "../include/string.h"

static network_stack_t network_stack;

void network_init() {
    network_stack.interface_count = 0;
    network_stack.network_enabled = 1;
    
    // Set default hostname
    int i = 0;
    const char* default_hostname = "aetheros";
    while (i < MAX_HOSTNAME_LENGTH - 1 && default_hostname[i]) {
        network_stack.hostname[i] = default_hostname[i];
        i++;
    }
    network_stack.hostname[i] = 0;
    
    // Add default interface
    add_interface("eth0", "192.168.1.100");
}

void network_info() {
    print("=== Network Information ===\n");
    print("Hostname: ");
    print(network_stack.hostname);
    print("\n");
    print("Network Status: ");
    if (network_stack.network_enabled) {
        print("ENABLED\n");
    } else {
        print("DISABLED\n");
    }
    
    print("Active Interfaces: ");
    print_num(network_stack.interface_count);
    print("\n");
    
    show_interfaces();
}

int ping_host(const char* hostname) {
    print("PING ");
    print(hostname);
    print(" (");
    print("192.168.1.1");
    print(") 56(84) bytes of data.\n");
    
    // Simulate ping responses
    for (int i = 0; i < 3; i++) {
        print("64 bytes from ");
        print(hostname);
        print(": icmp_seq=");
        print_num(i + 1);
        print(" time=");
        print_num(10 + i);
        print("ms\n");
    }
    
    print("\n--- ");
    print(hostname);
    print(" ping statistics ---\n");
    print("3 packets transmitted, 3 received, 0% packet loss\n");
    print("round-trip min/avg/max = 10/12/15 ms\n");
    
    return 1;
}

void set_hostname(const char* hostname) {
    int i = 0;
    while (i < MAX_HOSTNAME_LENGTH - 1 && hostname[i]) {
        network_stack.hostname[i] = hostname[i];
        i++;
    }
    network_stack.hostname[i] = 0;
}

char* get_hostname() {
    return network_stack.hostname;
}

int add_interface(const char* name, const char* ip) {
    if (network_stack.interface_count >= MAX_NETWORK_INTERFACES) {
        return 0;
    }
    
    network_interface_t* iface = &network_stack.interfaces[network_stack.interface_count];
    
    // Copy interface name
    int i = 0;
    while (i < 15 && name[i]) {
        iface->name[i] = name[i];
        i++;
    }
    iface->name[i] = 0;
    
    // Copy IP address
    i = 0;
    while (i < MAX_IP_LENGTH - 1 && ip[i]) {
        iface->ip_address[i] = ip[i];
        i++;
    }
    iface->ip_address[i] = 0;
    
    // Set default values
    const char* default_mask = "255.255.255.0";
    const char* default_gateway = "192.168.1.1";
    
    i = 0;
    while (i < MAX_IP_LENGTH - 1 && default_mask[i]) {
        iface->subnet_mask[i] = default_mask[i];
        i++;
    }
    iface->subnet_mask[i] = 0;
    
    i = 0;
    while (i < MAX_IP_LENGTH - 1 && default_gateway[i]) {
        iface->gateway[i] = default_gateway[i];
        i++;
    }
    iface->gateway[i] = 0;
    
    // Set MAC address (simulated)
    iface->mac_address[0] = 0x00;
    iface->mac_address[1] = 0x1A;
    iface->mac_address[2] = 0x2B;
    iface->mac_address[3] = 0x3C;
    iface->mac_address[4] = 0x4D;
    iface->mac_address[5] = 0x5E;
    
    iface->is_active = 1;
    iface->bytes_sent = 0;
    iface->bytes_received = 0;
    
    network_stack.interface_count++;
    return 1;
}

void show_interfaces() {
    print("\nNetwork Interfaces:\n");
    for (int i = 0; i < network_stack.interface_count; i++) {
        network_interface_t* iface = &network_stack.interfaces[i];
        
        print("Interface: ");
        print(iface->name);
        print("\n");
        print("  Status: ");
        if (iface->is_active) {
            print("UP\n");
        } else {
            print("DOWN\n");
        }
        print("  IP Address: ");
        print(iface->ip_address);
        print("\n");
        print("  Subnet Mask: ");
        print(iface->subnet_mask);
        print("\n");
        print("  Gateway: ");
        print(iface->gateway);
        print("\n");
        print("  MAC Address: ");
        for (int j = 0; j < 6; j++) {
            print_num(iface->mac_address[j]);
            if (j < 5) print(":");
        }
        print("\n");
        print("  Bytes Sent: ");
        print_num(iface->bytes_sent);
        print("\n");
        print("  Bytes Received: ");
        print_num(iface->bytes_received);
        print("\n\n");
    }
}
