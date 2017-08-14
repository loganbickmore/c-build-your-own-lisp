#include <stdio.h>
#include <stdlib.h>

/* if on windows */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* fake readline func */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* fake add_history func */
void add_history(char* unused) {}

/* otherwise include the editline headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {

  /* print version & exit info */
  puts("Lispy Version 0.0.1");
  puts("Press Ctrl+C to exit\n");

  // main repl loop
  while (1) {
    /* prompt for input */
    char * input = readline("lispy> ");

    /* log history */
    add_history(input);

    /*echo input to user */
    printf("=> %s\n", input);

    /* free input */
    free(input);
  }
  return 0;
}
