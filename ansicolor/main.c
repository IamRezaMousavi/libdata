#include <stdio.h>

#include "ansicolors.h"

int main(int argc, const char *argv[]) {
  setupConsole();

  printf("Reset\n");
  printf(RED_TEXT "HI" RESET_TEXT "\n");
  printf("Reset\n");
  printf(GREEN_TEXT "HI" RESET_TEXT "\n");
  printf("Reset\n");
  printf(MAGENTA_TEXT "HI" RESET_TEXT "\n");
  printf("Reset\n");
  printf(BOLD_RED_TEXT "HI" RESET_TEXT "\n");
  printf("Reset\n");
  printf(UNDERLINE_GREEN_TEXT "HI" RESET_TEXT "\n");
  printf("Reset\n");

  restoreConsole();
  return 0;
}
