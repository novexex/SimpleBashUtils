#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YELLOW "\e[0;33m"
#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define RESET "\e[0m"
#define PURP "\e[1;95m"

void cat_tests();

int main() {
  cat_tests();
}

void cat_tests() {
    char flags[6][3] = {"-b", "-e", "-n", "-s", "-t", "-v"};
    char cat[512] = {0};
    char s21cat[512] = {0};
    int test = 0;
    int size = sizeof(flags) / sizeof(flags[0]);
    for (int i = 0; i < size; i++) {
      strcat(cat, "cat ");
      strcat(s21cat, "./cat/s21_cat ");
      strcat(cat, flags[i]);
      strcat(s21cat, flags[i]);
      strcat(cat, " ./cat/testing > ./cat/cattest");
      strcat(s21cat, " ./cat/testing > ./cat/mycattest");
      printf("%sCat test #%d%s\n", PURP, ++test, RESET);
      printf("%s\n", s21cat);
        system(cat);
        system(s21cat);
        if (system("diff ./cat/cattest ./cat/mycattest")) {
            printf("%sFAIL!%s\n\n", RED, RESET);
        } else {
            printf("%sOK!%s\n\n", GRN, RESET);
        }
        for (int i = 0; i < 512; i++) {
            cat[i] = 0;
            s21cat[i] = 0;
        }
    }
}
