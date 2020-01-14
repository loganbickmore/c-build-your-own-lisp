#include "parsing.h"

int number_of_nodes(mpc_ast_t* t)
{
  if (t->children_num == 0) { return 1; }
  if (t->children_num >= 1) { 
    int total = 1;
    for (int i = 0; i < t->children_num; i++) {
      total = total + number_of_nodes(t->children[i]);
    }
    return total;
   }
   return 0;
}

typedef long double number;
number eval_op(number x, char* op, number y)
{
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  if (strcmp(op, "%") == 0) { return (long)x % (long)y; }
  return 0;
}

number eval(mpc_ast_t* t)
{
  /* If tagged as a number return directlly */
  if (strstr(t->tag, "double")){
    char *end;
    return strtod(t->contents, &end);
  }
  if (strstr(t->tag, "long")){
    return atoi(t->contents);
  }

  /* The operator is always the second child */
  char* op = t->children[1]->contents;

  /* We store the third child in x */
  number x = eval(t->children[2]);

  /* Iterate the remaining children and combining */
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }
  return x;
}
int main(int argc, char** argv)
{
  /* Create some parsers */
  mpc_parser_t* Number   = mpc_new("number");
  mpc_parser_t* Long     = mpc_new("long");
  mpc_parser_t* Double   = mpc_new("double");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Lispy    = mpc_new("lispy");

  /* Define them with the following Language */
  // number as float and int in one regex: /-?[0-9]+\\.?[0-9]*/
  mpca_lang(MPCA_LANG_DEFAULT,
      "                                                                                \
      long     : /-?[0-9]+/ ;                                                          \
      double   : /-?[0-9]+\\.{1}[0-9]+/ ;                                              \
      number   : <double> | <long> ;                                                   \
      operator : '+' | '-' | '*' | '/' | '%' | \"add\" | \"sub\" | \"mul\" | \"div\" ; \
      expr     : <number> | '(' <operator> <expr>+ ')' ;                               \
      lispy    : /^/ <operator> <expr>+ /$/ ;                                          \
      ",
      Long, Double, Number, Operator, Expr, Lispy);

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
      number result = eval(r.output);
      char c[2048];
      sprintf(c, "%.*Lg",1000, result);
      printf("%s\n", c);
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
