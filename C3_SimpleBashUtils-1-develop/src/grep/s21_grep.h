#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include "output.h"

int flag_check(int argc, char **argv, char *pattern, flags *flag);
void s21_grep(int argc, char **argv, char *pattern, flags *flag);
void check_pos(int argc, char **argv, char *pattern, flags *flag);
void prep(char *file, int file_count, char *pattern, flags *flag);
int pattern_check(char *pattern, char *temp);

#endif  // SRC_GREP_S21_GREP_H_