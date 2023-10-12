CC = gcc 
CFLAGS = -Wall -Werror -Wextra

all: clean s21_cat

clean:
	rm -rf *.o s21_cat rm -rf *.o *.out log.txt

rebuild:
	$(MAKE) clean
	$(MAKE) all

s21_cat: parser.o s21_cat.o
	$(CC) $(CFLAGS) parser.c s21_cat.c -o s21_cat

test:
	sh testing_cat.sh