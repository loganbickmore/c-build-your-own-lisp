#include "mpc.h"

// windows preprocessor
#ifdef _WIN32

static char buffer[2048];

char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

void add_history(char *unused) {}

#else
#include <editline/history.h>
#include <editline/readline.h>
#endif

int main(int argc, char **argv) {
  // Create parsers
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lispy = mpc_new("lispy");

  // Define them with the following
  // polish notation
  mpca_lang(MPCA_LANG_DEFAULT,
            "                                                        \
            number   : /-?[0-9]+[.]?[0-9]*/ ;                        \
            operator : '+' | '-' | '*' | '/' | '%' ;                 \
            expr     : <number> | '(' < operator><expr> + ')';       \
            lispy    : /^/ <operator><expr> + /$/ | /^/<expr> + /$/; \
            ",
            Number, Operator, Expr, Lispy);

  // standard notation (needs to be fixed)
  // mpca_lang(MPCA_LANG_DEFAULT,
  //           "                                                         \
  //           number   : /-?[0-9]+[.]?[0-9]*/ ;                         \
  //           operator : '+' | '-' | '*' | '/' | '%' ;                  \
  //           expr     : <number> | '(' <expr> <operator> <expr>+ ')' ; \
  //           lispy    : /^/ <expr> + /$/ ;                             \
  //           ",
  //           Number, Operator, Expr, Lispy);

  // print version and exit info
  printf("Lispy Version 0.0.2\n");
  printf("Press ctrl+c to exit\n");

  while (1) {
    char *input = readline("lispy> ");
    add_history(input);

    // attempt parsing user input
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      // success
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      // fail
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    free(input);
  }
  // undefine and delete our parsers
  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}
