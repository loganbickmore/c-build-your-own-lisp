#include <stdio.h>

// function declaration ex
int add_together(int x, int y) {
  int result = x + y;
  return result;
}

// struct declaration ex
typedef struct {
  float x;
  float y;
} point;

int hello_n(int n, char *str) {
  for (int i = 0; i < n; i++) {
    printf("func hello_n iteration %d - %s\n", i + 1, str);
  }
  return 0;
}

int loops(char *str) {
  // for loop
  for (int i = 0; i < 5; i++) {
    printf("for iteration %d - %s\n", i + 1, str);
  }

  // while loop
  int i = 0;
  while (i < 5) {
    printf("while iteration %d - %s\n", i + 1, str);
    i++;
  }

  return 0;
}

int main(int argc, char **argv) {
  char *str = "Hello World!";

  int x = add_together(1, 2);
  printf("add_together results: %d\n", x);

  loops(str);

  hello_n(2, str);

  return 0;
}
