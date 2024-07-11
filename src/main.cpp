#include <cstdint>
#include "lib/timer.h"

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;
const uint64_t FRAME_TIME = 1000 / 60; // ~16.67 ms for 60 FPS

uint16_t* const VGA_BUFFER = (uint16_t*)0xB8000;

void clear_screen() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VGA_BUFFER[i] = (uint16_t)' ' | (uint16_t)(0x0F << 8);
    }
}

void write_char(char c, int x, int y) {
    int offset = y * SCREEN_WIDTH + x;
    VGA_BUFFER[offset] = (uint16_t)c | (uint16_t)(0x0F << 8);
}

void write_string(const char* str, int x, int y) {
    for (int i = 0; str[i] != '\0'; ++i) {
        write_char(str[i], x + i, y);
    }
}

void update() {
    clear_screen();
    write_string("Hello World!", 0, 0);
}

extern "C" void main() {
    Timer timer;
    
    while(1) {
        uint64_t elapsed_time = timer.getElapsedMs();
        
        if (elapsed_time >= FRAME_TIME) {
            update();
            timer.reset();
        }
    }
}