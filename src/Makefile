CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LFLAGS=-lcheck -lpthread -lsubunit -lm
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -fPIC
CFILES=s21_string.a
CEXE=s21_test

#============= FLAGS FOR OS ======================================================== 
UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lsubunit -lm -lrt -lpthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck -lm
	OPEN_CM=open
endif

#============= ALL ==================================================================
all: clean ${CFILES} test

#============= LIBRIRY & TEST LIBRARY================================================

s21_string.a:
	${CC} ${CFLAGS} -c s21_*.c
	ar rc ${CFILES} *.o
	ranlib ${CFILES}
	rm -f *.o

gcov_s21_string.a: clean
	${CC} ${CFLAGS} -c *.c ${GCOV_FLAGS}
	ar rc s21_string.a *.o
	ranlib s21_string.a
	rm -f *.o

vg: clean
	gcc tests/tests* *.c -o out ${GCOV_FLAGS} -lm ${LDFLAGS}
	chmod a+x out
	valgrind --tool=memcheck --leak-check=yes --leak-check=full out
	rm -rf *.gcno
#============= TEST ==============================================================

test: clean s21_string.a
	$(CC) ${CFLAGS} tests/test*.c  ${CFILES} -o ${CEXE} ${LDFLAGS}
	./${CEXE}

gcov_report: clean gcov_s21_string.a
	$(CC) ${CFLAGS} tests/test*.c s21_string.a -o ${CEXE} ${LDFLAGS} ${GCOV_FLAGS}
	mkdir report
	./${CEXE} >> report/s21_report.txt
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	rm -rf *.gcda *.gcno *.info
	open report/index.html
	

#=========== STYLE ====================================================================
format_check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n tests/*.c tests/*.h *.c *.h
	rm -f .clang-format

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i tests/*.c tests/*.h *.c *.h
	rm -f .clang-format

#========== CLEAN ======================================================================
clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf *.a
	rm -rf s21_test
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.log
	rm -rf *.html
	rm -rf *.css
	rm -rf report
	rm -rf *.dSYM
	rm -rf *.info