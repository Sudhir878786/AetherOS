#ifndef __PRINT_H__
#define __PRINT_H__

#define ROWS 25
#define COLS 80

void clearLine(int from, int to, char color);
void clear(char color);
void clear_();
void printch(char c, char color);
void print (char* ch);
void print_color (char* ch, char color);
void print_num(int i);
void back_cursor(int l);
void printLine(int from, int to, char msg[], char color);
#endif
