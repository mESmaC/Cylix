#include "lib/display.h"
#include "lib/shell.h"
#include "lib/timer.h"
#include "lib/window_manager.h"
#include <cstdint>

const uint64_t FRAME_TIME = 1;
const uint64_t LOGO_DISPLAY_TIME = 3000;

class GUI {
public:
  static void run() {
    WindowManager windowManager;
    windowManager.init();
    windowManager.run();
  }
};

enum class Mode { LOGO, SHELL, GUI };

class System {
private:
  Mode current_mode;
  Timer timer;
  uint64_t logo_start_time;
  bool logo_displayed;

public:
  System()
      : current_mode(Mode::LOGO), logo_start_time(0), logo_displayed(false) {}

  void update() {
    Display::clear_screen();
    switch (current_mode) {
    case Mode::LOGO:
      if (!logo_displayed) {
        const char *CYLIX_LOGO[] = {"  /$$$$$$            /$$ /$$          ",
                                    " /$$__  $$          | $$|__/          ",
                                    "| $$  \\__/ /$$   /$$| $$ /$$ /$$   /$$",
                                    "| $$      | $$  | $$| $$| $$|  $$ /$$/",
                                    "| $$      | $$  | $$| $$| $$ \\  $$$$/ ",
                                    "| $$    $$| $$  | $$| $$| $$  >$$  $$ ",
                                    "|  $$$$$$/|  $$$$$$$| $$| $$ /$$/\\  $$",
                                    " \\______/  \\____  $$|__/|__/|__/  \\__/",
                                    "           /$$  | $$                  ",
                                    "          |  $$$$$$/                  ",
                                    "           \\______/                   "};
        const int LOGO_HEIGHT = 11;
        const int LOGO_WIDTH = 41;
        Display::display_logo(CYLIX_LOGO, LOGO_HEIGHT,
                              LOGO_WIDTH); // Display the logo
        Display::write_string("Cylix OS", (SCREEN_WIDTH - 8) / 2,
                              SCREEN_HEIGHT - 2);
        logo_displayed = true;
        logo_start_time = timer.getElapsedMs(); // Record the start time
      }
      break;
    case Mode::SHELL:
      Shell::run();
      break;
    case Mode::GUI:
      GUI::run();
      break;
    }
    Display::swap_buffers();
  }

  void run() {
    Display::initialize(); // Initialize the display
    while (true) {
      uint64_t elapsed_time = timer.getElapsedMs();

      if (elapsed_time >= FRAME_TIME) {
        update();      // Update the display
        timer.reset(); // Reset the timer

        if (current_mode == Mode::LOGO &&
            (elapsed_time - logo_start_time) >= LOGO_DISPLAY_TIME) {
          current_mode = Mode::SHELL; // Change to shell mode after 3 seconds
        }
      }
    }
  }
};

extern "C" void main() {
  System system;
  system.run();
}
