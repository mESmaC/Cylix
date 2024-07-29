#include "display.h"

uint16_t framebuffer1[BUFFER_SIZE] __attribute__((aligned(16)));
uint16_t framebuffer2[BUFFER_SIZE] __attribute__((aligned(16)));

// Pointer to the VGA buffer (display output)
uint16_t* VGA_BUFFER = (uint16_t*)0xB8000; // VGA text mode memory

uint16_t* Display::front_buffer = framebuffer1;
uint16_t* Display::back_buffer = framebuffer2;

void Display::initialize() {
    front_buffer = framebuffer1;
    back_buffer = framebuffer2;
    clear_screen();  // Clear the back buffer
    swap_buffers();  // Initialize the display with the front buffer
}

void Display::clear_screen() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        back_buffer[i] = (uint16_t)' ' | (uint16_t)(0x0F << 8); // Clear with space character
    }
}

void Display::write_char(char c, int x, int y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        int offset = y * SCREEN_WIDTH + x;
        back_buffer[offset] = (uint16_t)c | (uint16_t)(0x0F << 8); // Write to the back buffer
    }
}

void Display::write_string(const char* str, int x, int y) {
    for (int i = 0; str[i] != '\0'; ++i) {
        write_char(str[i], x + i, y); // Write each character
    }
}

void Display::display_logo(const char* logo[], int logo_height, int logo_width) {
    int start_x = (SCREEN_WIDTH - logo_width) / 2;
    int start_y = (SCREEN_HEIGHT - logo_height) / 2;
    for (int y = 0; y < logo_height; y++) {
        for (int x = 0; x < logo_width; x++) {
            write_char(logo[y][x], start_x + x, start_y + y); // Draw the logo
        }
    }
}

void Display::swap_buffers() {
    // Swap the buffers
    if (front_buffer == framebuffer1) {
        front_buffer = framebuffer2;
        back_buffer = framebuffer1;
    } else {
        front_buffer = framebuffer1;
        back_buffer = framebuffer2;
    }
    // Copy the back buffer to the VGA buffer
    for (int i = 0; i < BUFFER_SIZE; i++) {
        VGA_BUFFER[i] = back_buffer[i];
    }
}
