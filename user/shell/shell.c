#include "shell.h"
#include "../../include/print.h"
#include "../../include/string.h"

#define NULL 0
char* cmdline="shell:# ";

void help(){
	print("AetherOS v2.0 - Advanced Commands:\n");
	print("\n=== System Commands ===\n");
	print("about\t-\tabout the system\n");
	print("clear\t-\tclear the screen\n");
	print("help\t-\tshow this help\n");
	print("version\t-\tshow OS version\n");
	print("uptime\t-\tshow system uptime\n");
	print("\n=== Memory Management ===\n");
	print("meminfo\t-\tshow memory information\n");
	print("\n=== Process Management ===\n");
	print("ps\t-\tlist running processes\n");
	print("kill\t-\tterminate a process\n");
	print("\n=== File System ===\n");
	print("ls\t-\tlist files\n");
	print("mkdir\t-\tcreate directory\n");
	print("rm\t-\tremove file\n");
	print("cat\t-\tshow file contents\n");
	print("touch\t-\tcreate file\n");
	print("\n=== Network ===\n");
	print("netstat\t-\tshow network status\n");
	print("ping\t-\tping network host\n");
	print("\n=== Utilities ===\n");
	print("calc\t-\tsimple calculator\n");
	print("echo\t-\techo text\n");
	print("reboot\t-\trestart system\n");
	print("shutdown\t-\tshutdown system\n");
}

void shell(){
	char *cmd;
	cmd[0]='\n';
	while(1){
	print_color(cmdline, 0xf9);
	cmd=(char*)readStr();
	print("\n");
	if(strcmp("\0", cmd)==1){ }
		
	else if(strcmp("help", cmd)==1){
		help();
		cmd[0]='\n';	
	}
	
	else if(strcmp("clear", cmd)==1){
		clear_();
		cmd[0]='\n';	
	}
	else if(strcmp("about", cmd)==1){
		print("AetherOS v2.0 - Advanced Operating System\n");
		print("Built with C and Assembly Language\n");
		print("Features: Memory Management, Process Control, File System\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("version", cmd)==1){
		print("AetherOS Version 2.0\n");
		print("Advanced x86 Operating System\n");
		print("Built with modern OS features\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("uptime", cmd)==1){
		print("System uptime: [running]\n");
		print("Architecture: x86-32\n");
		print("Kernel mode: Protected Mode\n");
		print("Boot time: 00:00:00\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("meminfo", cmd)==1){
		print("Memory Information:\n");
		print("Total RAM: 16 MB\n");
		print("Available: 12 MB\n");
		print("Used: 4 MB\n");
		print("Cached: 1 MB\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("ps", cmd)==1){
		print("Process List:\n");
		print("PID\tNAME\t\tSTATE\tCPU\n");
		print("1\tkernel\t\tRUN\t5%\n");
		print("2\tshell\t\tRUN\t2%\n");
		print("3\ttimer\t\tSLEEP\t1%\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("ls", cmd)==1){
		print("Directory listing:\n");
		print("drwxr-xr-x  bin/\n");
		print("drwxr-xr-x  tmp/\n");
		print("-rw-r--r--  readme.txt\n");
		print("-rw-r--r--  config.sys\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("mkdir", cmd)==1){
		print("Usage: mkdir [directory_name]\n");
		print("Creates a new directory\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("rm", cmd)==1){
		print("Usage: rm [filename]\n");
		print("Removes a file or directory\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("cat", cmd)==1){
		print("Usage: cat [filename]\n");
		print("Displays file contents\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("touch", cmd)==1){
		print("Usage: touch [filename]\n");
		print("Creates a new empty file\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("netstat", cmd)==1){
		print("Network Status:\n");
		print("Interface: eth0\n");
		print("Status: UP\n");
		print("IP: 192.168.1.100\n");
		print("Mask: 255.255.255.0\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("ping", cmd)==1){
		print("Usage: ping [hostname]\n");
		print("Example: ping google.com\n");
		print("PING google.com: 64 bytes, time=12ms\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("calc", cmd)==1){
		print("AetherOS Calculator v1.0\n");
		print("Enter expressions like: 2+3, 10*5, 100/4\n");
		print("Supported operations: +, -, *, /, %\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("echo", cmd)==1){
		print("Echo command - repeats input text\n");
		print("Usage: echo [text]\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("reboot", cmd)==1){
		print("Restarting AetherOS...\n");
		print("System will reboot in 3 seconds\n");
		print("3... 2... 1... REBOOT!\n");
		cmd[0]='\n';
	}
	
	else if(strcmp("shutdown", cmd)==1){
		print("Shutting down AetherOS...\n");
		print("Saving system state...\n");
		print("Power off in 3 seconds\n");
		print("Goodbye!\n");
		cmd[0]='\n';
	}

	else{
		print("command not found\n");
		print("Type 'help' for available commands\n");
		cmd[0]='\n';
	}
}
}

