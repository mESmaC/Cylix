#ifndef SHELL_H
#define SHELL_H

#include "display.h"
#include <cstdint>

struct Command {
  const char *name;
  void (*function)();
};

std::size_t strlen(const char *str);
char *strncpy(char *dest, const char *src, std::size_t n);
int strcmp(const char *str1, const char *str2);

class Shell {
private:
  static const int MAX_COMMANDS = 10;
  static const int MAX_HISTORY = 25;
  static Command commands[MAX_COMMANDS];
  static int command_count;
  static char history[MAX_HISTORY][SCREEN_WIDTH];
  static int history_count;
  static int history_index;

  static void add_to_history(const char *command);

public:
  static void register_command(const char *name, void (*function)());
  static void run();
  static void clear();
  static void move_history_up();
  static void execute_command(const char *input);
};

#endif // SHELL_H
