#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YELLOW "\e[0;33m"
#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define RESET "\e[0m"
#define CYAN "\e[1;96m"

void grep_tests();

int main() {
    grep_tests();
}

void grep_tests() {
  char flags[10][3] = {"-e", "-i", "-v", "-c", "-l", "-n", "-h", "-s", "-f", "-o"};
  char grep[512] = {0};
  char s21grep[512] = {0};
  int test = 0;
  int size = sizeof(flags) / sizeof(flags[0]);
  for (int i = 0; i < size; i++) {
    strcat(grep, "grep ");
    strcat(s21grep, "./grep/s21_grep ");
    strcat(grep, flags[i]);
    strcat(s21grep, flags[i]);
    if (flags[i][1] == 'f') {
      strcat(grep, " ./grep/find ./grep/grtest.txt > ./grep/greptest");
      strcat(s21grep, " ./grep/find ./grep/grtest.txt > ./grep/mygreptest");
    } else {
      strcat(grep, " qwe ./grep/grtest.txt > ./grep/greptest");
      strcat(s21grep, " qwe ./grep/grtest.txt > ./grep/mygreptest");
    }
    printf("%sGrep test #%d%s\n", CYAN, ++test, RESET);
    printf("%s\n", s21grep);
      system(grep);
      system(s21grep);
      if (system("diff ./grep/greptest ./grep/mygreptest")) {
          printf("%sFAIL!%s\n\n", RED, RESET);
      } else {
          printf("%sOK!%s\n\n", GRN, RESET);
      }
      for (int i = 0; i < 512; i++) {
          grep[i] = 0;
          s21grep[i] = 0;
      }
  }
}

