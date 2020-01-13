#include <stdio.h>
#include <math.h>


int sum(int a, int b)
{
  return a + b;
}

typedef struct {
  float x;
  float y;
} point;

float calc_length(point p)
{
  return sqrt(p.x * p.x + p.y * p.y);
}

void hello_n(int n)
{
  for (int i = 0; i < n; i++) {
    puts("Hello World!");
  }
}

int main(int argc, char** argv)
{
  puts("sum()");
  printf("%d\n", sum(1,1));

  puts("calc_length()");
  point p = { .x = 0.1, .y = 10.0 };
  //printf("%f\n", calc_length((point){ .x = 0.1, .y = 10.0 })); // define point p inline
  printf("%f\n", calc_length(p));

  puts("Use a for loop to print Hello World! five times.");
  for (int i = 0; i < 5; i++) {
    puts("Hello World!");
  }

  puts("Use a while loop to print Hello World! five times.");
  int i = 0;
  while (i < 5) {
    puts("Hello World!");
    i++;
  }

  puts("Declare a function that outputs Hello World! n number of times. Call this from main.");
  hello_n(2);

  return 0;
}
