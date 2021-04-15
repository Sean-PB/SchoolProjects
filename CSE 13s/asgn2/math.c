#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PI M_PI
#define OPTIONS "ascte"

// Prototypes:
int Sin();
int Cos();
int Tan();
int Exp();

int main(int argc, char **argv) {
  char choice;
  if (argc == 2 && strlen(argv[1]) == 2) {
    while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
      switch (choice) {
      case 'a':
        Sin();
        Cos();
        Tan();
        Exp();
        break;
      case 's':
        Sin();
        break;
      case 'c':
        Cos();
        break;
      case 't':
        Tan();
        break;
      case 'e':
        Exp();
        break;
      default:
        printf("Error: program must use a one of the following arguments:\n- "
               "a:\truns all functions (sin, cos, tan, exp)\n- s:\truns sin "
               "functions\n- c:\truns cos function\n- t:\truns tan function\n- "
               "e:\truns exp function\n");
        break;
      }
    }
  } else {
    puts("Error: a single arguement is required");
    return 0;
  }
  return 0;
}

int Sin() {
  printf(
      "x\t Sin\t\t Library\t Difference\n-\t ---\t\t -------\t ----------\n");
  double my_ans;
  double lib_ans;
  for (double x = (-2 * PI); x <= (2 * PI); x += (PI / 16)) {
    double x_sq = x * x;
    my_ans = (x
                 * ((x_sq * (52785432 - 479249 * x_sq) - 1640635920) * x_sq
                       + 11511339840))
             / (((18361 * x_sq + 3177720) * x_sq + 277920720) * x_sq
                   + 11511339840);
    lib_ans = sin(x);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, my_ans, lib_ans,
        (my_ans - lib_ans));
  }
  return 0;
}

int Cos() {
  printf(
      "x\t Cos\t\t Library\t Difference\n-\t ---\t\t -------\t ----------\n");
  double my_ans;
  double lib_ans;
  for (double x = (-2 * PI); x <= (2 * PI); x += (PI / 16)) {
    double x_sq = x * x;
    my_ans = ((x_sq * (1075032 - 14615 * x_sq) - 18471600) * x_sq + 39251520)
             / (((127 * x_sq + 16632) * x_sq + 1154160) * x_sq + 39251520);
    lib_ans = cos(x);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, my_ans, lib_ans,
        (my_ans - lib_ans));
  }
  return 0;
}

int Tan() {
  printf(
      "x\t Tan\t\t Library\t Difference\n-\t ---\t\t -------\t ----------\n");
  double my_ans;
  double lib_ans;
  for (double x = (-PI / 3); x <= (PI / 3); x += (PI / 16)) {
    double x_sq = x * x;
    my_ans = (x
                 * ((((x_sq - 990) * x_sq + 135135) * x_sq - 4729725) * x_sq
                       + 34459425))
             / ((((45 * x_sq - 13860) * x_sq + 945945) * x_sq - 16216200) * x_sq
                   + 34459425);
    lib_ans = tan(x);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, my_ans, lib_ans,
        (my_ans - lib_ans));
  }
  return 0;
}

int Exp() {
  printf(
      "x\t Exp\t\t Library\t Difference\n-\t ---\t\t -------\t ----------\n");
  double my_ans;
  double lib_ans;
  double numerator;
  double denominator;
  double part;
  double epsilon = 0.000000001;
  for (double x = 0; x <= 9; x += 0.1) {
    my_ans = 1.0;
    numerator = 1.0;
    denominator = 1.0;
    part = 1.0;
    for (int i = 1; part > epsilon; i++) {
      numerator *= x;
      denominator *= i;
      part = numerator / denominator;
      my_ans += part;
    }
    double lib_ans = exp(x);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, my_ans, lib_ans,
        (my_ans - lib_ans));
  }
  return 0;
}
