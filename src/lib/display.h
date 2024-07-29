#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;
const int BUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

// Define two buffers for double buffering
extern uint16_t framebuffer1[BUFFER_SIZE] __attribute__((aligned(16)));
extern uint16_t framebuffer2[BUFFER_SIZE] __attribute__((aligned(16)));

// Pointer to the VGA buffer (display output)
extern uint16_t* VGA_BUFFER; // VGA text mode memory

class Display {
private:
    static uint16_t* front_buffer;
    static uint16_t* back_buffer;

public:
    static void initialize();
    static void clear_screen();
    static void write_char(char c, int x, int y);
    static void write_string(const char* str, int x, int y);
    static void display_logo(const char* logo[], int logo_height, int logo_width);
    static void swap_buffers();
};

#endif // DISPLAY_H
