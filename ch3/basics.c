#include <stdio.h>

int hello_n(int n, char* str) {
  for (int i = 0; i < n; i++) {
    printf("func hello_n iteration %d - %s\n", i + 1, str);
  }
  return 0;
}

int main(int argc, char** argv) {
  char* str = "Hello World!";

  for (int i = 0; i < 5; i++) {
    printf("for iteration %d - %s\n", i + 1, str);
  }

  int i = 0;
  while ( i < 5 ) {
    printf("while iteration %d - %s\n", i + 1, str);
    i++;
  }

  hello_n(2,str);

  return 0;
}
