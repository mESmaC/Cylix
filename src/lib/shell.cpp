#include "shell.h"
#include "display.h"
#include "input.h"

Command Shell::commands[MAX_COMMANDS];
int Shell::command_count = 0;
char Shell::history[MAX_HISTORY][SCREEN_WIDTH];
int Shell::history_count = 0;
int Shell::history_index = 0;

void Shell::add_to_history(const char *command) {
  if (history_count < MAX_HISTORY) {
    strncpy(history[history_count], command, SCREEN_WIDTH);
    history_count++;
  } else {
    // Shift history up if at max capacity
    for (int i = 1; i < MAX_HISTORY; i++) {
      strncpy(history[i - 1], history[i], SCREEN_WIDTH);
    }
    strncpy(history[MAX_HISTORY - 1], command, SCREEN_WIDTH);
  }
  history_index = history_count;
}

void Shell::register_command(const char *name, void (*function)()) {
  if (command_count < MAX_COMMANDS) {
    commands[command_count].name = name;
    commands[command_count].function = function;
    command_count++;
  }
}

void Shell::run() {
  Display::clear_screen();
  const char *prompt = "shell> ";
  char input[SCREEN_WIDTH];
  int input_index = 0;

  while (true) {
    Display::write_string(prompt, 0, SCREEN_HEIGHT - 1);
    char c = get_input(); // Implement this function to get user input

    if (c == '\n') {
      input[input_index] = '\0';
      add_to_history(input);
      execute_command(input);
      input_index = 0;
    } else if (c == '\b' && input_index > 0) {
      input[--input_index] = '\0';
    } else if (c >= ' ' && c <= '~' && input_index < SCREEN_WIDTH - 1) {
      input[input_index++] = c;
    }

    Display::clear_screen();
    for (int i = 0; i < history_count; i++) {
      Display::write_string(history[i], 0, i);
    }
    Display::write_string(prompt, 0, SCREEN_HEIGHT - 1);
    Display::write_string(input, strlen(prompt), SCREEN_HEIGHT - 1);
    Display::swap_buffers();
  }
}

void Shell::clear() {
  history_count = 0;
  Display::clear_screen();
}

void Shell::move_history_up() {
  if (history_count < MAX_HISTORY) {
    for (int i = 0; i < history_count - 1; i++) {
      strncpy(history[i], history[i + 1], SCREEN_WIDTH);
    }
    history_count--;
  }
}

void Shell::execute_command(const char *input) {
  for (int i = 0; i < command_count; i++) {
    if (strcmp(input, commands[i].name) == 0) {
      commands[i].function();
      return;
    }
  }
  Display::write_string("Command not found", 0, SCREEN_HEIGHT - 2);
}

std::size_t strlen(const char *str) {
  std::size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

char *strncpy(char *dest, const char *src, std::size_t n) {
  for (std::size_t i = 0; i < n; i++) {
    dest[i] = src[i];
    if (src[i] == '\0') {
      break;
    }
  }
  return dest;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2 && *s1 == *s2) {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}
