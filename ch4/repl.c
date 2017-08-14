#include <stdio.h>

// declare a buffer for user input
static char input[2048];

int main(int argc, char** argv) {

  // Print version
  puts("Lispy Version 0.0.1");
  puts("Press Ctrl+C to exit\n");

  // loop
  while (1) {
    // Prompt output
    fputs("lispy> ", stdout);

    // read user input, max size 2048
    fgets(input, 2048, stdin);

    // echo input back
    printf("=> %s", input);
  }
  return 0;
}
