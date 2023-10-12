CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: clean s21_grep

clean:
	rm -rf *.o s21_grep rm -rf *.o *.out log.txt
	
rebuild:
	$(MAKE) clean
	$(MAKE) all

s21_grep: s21_grep.o output.o
	$(CC) $(CFLAGS) s21_grep.c output.c -o s21_grep

test:
	sh testing_grep.sh