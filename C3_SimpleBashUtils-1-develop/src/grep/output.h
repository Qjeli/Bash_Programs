#ifndef SRC_GREP_OUTPUT_H_
#define SRC_GREP_OUTPUT_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e_flag;
  int i_flag;
  int v_flag;
  int c_flag;
  int l_flag;
  int n_flag;
  int h_flag;
  int s_flag;
  int o_flag;
  int f_flag;
} flags;

void init_flags(flags *flag);
void output(FILE *fp, regex_t reg, char *file, int file_count, flags *flag);

#endif  // SRC_GREP_OUTPUT_H_