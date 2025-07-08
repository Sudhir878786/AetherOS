#ifndef __GUI_H__
#define __GUI_H__

#include <stdint.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAX_WINDOWS 8

typedef struct {
    int x, y;
    int width, height;
    char title[32];
    int is_active;
    char background_color;
    char border_color;
} window_t;

typedef struct {
    window_t windows[MAX_WINDOWS];
    int window_count;
    int active_window;
} gui_manager_t;

// GUI functions
void gui_init();
int create_window(const char* title, int x, int y, int width, int height);
void draw_window(int window_id);
void draw_all_windows();
void set_active_window(int window_id);
void close_window(int window_id);
void gui_info();

#endif
