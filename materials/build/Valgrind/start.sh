#!/bin/bash

make
gcc -g -std=c99 -Wall -Werror -Wextra test_s21_grep.c -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
