#include <cstdint>

void clear_screen() {
    uint16_t* vga_buffer = (uint16_t*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (uint16_t)' ' | (uint16_t)(0x0F << 8);
    }
}

void write_char(char c, int x, int y) {
    uint16_t* vga_buffer = (uint16_t*)0xB8000;
    int offset = y * 80 + x;
    vga_buffer[offset] = (uint16_t)c | (uint16_t)(0x0F << 8);
}

void write_string(const char* str, int x, int y) {
    for (int i = 0; str[i] != '\0'; ++i) {
        write_char(str[i], x + i, y);
    }
}

extern "C" void main() {
    clear_screen();
    write_string("Hello World!", 0, 0);
    while(1) {}
}