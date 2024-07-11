#include <cstdint>

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
    write_string("Hello World!", 0, 0);
    while(1) {}
}