#include <stdio.h>
#include <string.h>

// declare buffer for user input
static char input[2048];

int main(int argc, char **argv) {
  // print version and exit info
  printf("Lispy Version 0.0.1\n");
  printf("Type 'exit', or press ctrl+c to exit\n");

  while (1) {
    fputs("lispy> ", stdout);

    // read a line
    fgets(input, 2048, stdin);

    printf("<- %s", input);

    // if you type exit, exit
    if (strncmp(input, "exit", 4) == 0) {
      break;
    }
  }
  return 0;
}
