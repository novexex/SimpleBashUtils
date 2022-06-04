CC=gcc
CFLAGS=-Wall -Werror -Wextra -g

all: clean s21_cat s21_grep

s21_cat:
	${CC} ${CFLAGS} ./cat/s21_cat.c -o ./cat/s21_cat

s21_grep:
	${CC} ${CFLAGS} ./grep/s21_grep.c -o ./grep/s21_grep

s21_cat_test: s21_cat
	${CC} ${CFLAGS} ./cat/s21_cat_test.c -o ./cat/s21_cat_test
	./cat/s21_cat_test

s21_grep_test: s21_grep
	${CC} ${CFLAGS} ./grep/s21_grep_test.c -o ./grep/s21_grep_test
	./grep/s21_grep_test

test: s21_cat s21_grep s21_cat_test s21_grep_test

valgrind_grep: s21_grep s21_grep_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./grep/s21_grep_test

valgrind_cat: s21_cat s21_cat_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./cat/s21_cat_test

leaks_grep: s21_grep s21_grep_test
	leaks -atExit -- ./grep/s21_grep_test | grep LEAK:	

leaks_cat: s21_cat s21_cat_test
	leaks -atExit -- ./cat/s21_cat_test | grep LEAK:

clean:
	rm -fr ./grep/s21_grep_test ./grep/s21_grep ./grep/mygreptest ./grep/greptest ./grep/a.out ./grep/*.dSYM 
	rm -fr ./cat/s21_cat_test ./cat/s21_cat ./cat/mycattest ./cat/cattest ./cat/a.out ./cat/*.dSYM

rebuild: clean all
