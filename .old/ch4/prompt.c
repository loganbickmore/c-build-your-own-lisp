#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// windows preprocessor
#ifdef _WIN32
static char buffer[2048];
// fake readline func
char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}
void add_history(char *unused) {}

#else // include editline headers
#include <editline/history.h>
#include <editline/readline.h>
#endif

int main(int argc, char **argv) {
  // print version and exit info
  printf("Lispy Version 0.0.1\n");
  printf("Type 'exit', or press ctrl+c to exit\n");

  while (1) {
    char *input = readline("lispy> ");
    add_history(input);

    printf("<- %s\n", input);
    free(input);

    // if you type exit, exit
    if (strncmp(input, "exit", 4) == 0) {
      break;
    }
  }
  return 0;
}
