#include <cstdint>
#include "lib/timer.h"
#include "lib/window_manager.h"

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;
const uint64_t FRAME_TIME = 0; 

uint16_t* const VGA_BUFFER = (uint16_t*)0xB8000;

const char* CYLIX_LOGO[] = {
    "  /$$$$$$            /$$ /$$          ",
    " /$$__  $$          | $$|__/          ",
    "| $$  \\__/ /$$   /$$| $$ /$$ /$$   /$$",
    "| $$      | $$  | $$| $$| $$|  $$ /$$/",
    "| $$      | $$  | $$| $$| $$ \\  $$$$/ ",
    "| $$    $$| $$  | $$| $$| $$  >$$  $$ ",
    "|  $$$$$$/|  $$$$$$$| $$| $$ /$$/\\  $$",
    " \\______/  \\____  $$|__/|__/|__/  \\__/",
    "           /$$  | $$                  ",
    "          |  $$$$$$/                  ",
    "           \\______/                   "
};

const int LOGO_HEIGHT = 11;
const int LOGO_WIDTH = 41;

class Display {
public:
    static void clear_screen() {
        for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
            VGA_BUFFER[i] = (uint16_t)' ' | (uint16_t)(0x0F << 8);
        }
    }

    static void write_char(char c, int x, int y) {
        int offset = y * SCREEN_WIDTH + x;
        VGA_BUFFER[offset] = (uint16_t)c | (uint16_t)(0x0F << 8);
    }

    static void write_string(const char* str, int x, int y) {
        for (int i = 0; str[i] != '\0'; ++i) {
            write_char(str[i], x + i, y);
        }
    }

    static void display_logo() {
        int start_x = (SCREEN_WIDTH - LOGO_WIDTH) / 2;
        int start_y = (SCREEN_HEIGHT - LOGO_HEIGHT) / 2;
        for (int y = 0; y < LOGO_HEIGHT; y++) {
            for (int x = 0; x < LOGO_WIDTH; x++) {
                write_char(CYLIX_LOGO[y][x], start_x + x, start_y + y);
            }
        }
    }
};

class Shell {
public:
    static void run() {
        Display::write_string("Shell not implemented yet", 0, SCREEN_HEIGHT - 1);
    }
};

class GUI {
public:
    static void run() {
        WindowManager windowManager;
        windowManager.init();

        windowManager.run();

    }
};

enum class Mode {
    LOGO,
    SHELL,
    GUI
};

class System {
private:
    Mode current_mode;
    Timer timer;

public:
    System() : current_mode(Mode::GUI) {}

    void update() {
        Display::clear_screen();
        switch (current_mode) {
            case Mode::LOGO:
                Display::display_logo();
                Display::write_string("Cylix OS", (SCREEN_WIDTH - 8) / 2, SCREEN_HEIGHT - 2);
                break;
            case Mode::SHELL:
                Shell::run();
                break;
            case Mode::GUI:
                GUI::run();
                break;
        }
    }

    void run() {
        while (1) {
            uint64_t elapsed_time = timer.getElapsedMs();
            
            if (elapsed_time >= FRAME_TIME) {
                update();
                timer.reset();

                if (elapsed_time > 5000) {
                    current_mode = Mode::SHELL;
                }
            }
        }
    }
};

extern "C" void main() {
    System system;
    system.run();
}