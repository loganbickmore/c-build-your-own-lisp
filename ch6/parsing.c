#include "parsing.h"

int main(int argc, char** argv)
{
  /* Create some parsers */
  mpc_parser_t* Number   = mpc_new("number");
  mpc_parser_t* Int      = mpc_new("int");
  mpc_parser_t* Float    = mpc_new("float");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Lispy    = mpc_new("lispy");

  /* Define them with the following Language */
  // number as float and int in one regex: /-?[0-9]+\\.?[0-9]*/
  mpca_lang(MPCA_LANG_DEFAULT,
      "                                                                                \
      int      : /-?[0-9]+/ ;                                                          \
      float    : /-?[0-9]+\\.{1}[0-9]+/ ;                                              \
      number   : <float> | <int> ;                                                     \
      operator : '+' | '-' | '*' | '/' | '%' | \"add\" | \"sub\" | \"mul\" | \"div\" ; \
      expr     : <number> | '(' <operator> <expr>+ ')' ;                               \
      lispy    : /^/ <operator> <expr>+ /$/ ;                                          \
      ",
      Int, Float, Number, Operator, Expr, Lispy);

  /* Print Version and Exit Info */
  puts("Lispy Version 0.0.0.0.2");
  puts("Press Ctrl+c to Exit\n");

  /* Main Loop */
  while (1) {
    char* input = readline("lispy> ");
    add_history(input);
    /* Attempt to Parse the user Input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* On Success Print the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise Print the Error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    free(input);
  }

  /* Undefine and delete our parsers */
  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}
