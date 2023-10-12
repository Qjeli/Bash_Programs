#ifndef SRC_GREP_PARSER_H_
#define SRC_GREP_PARSER_H_

#include <stdio.h>
#include <string.h>

typedef struct {
  int b_flag;
  int e_flag;
  int E_flag;
  int n_flag;
  int s_flag;
  int t_flag;
  int T_flag;
  int v_flag;
} flags;

// void init_flags(flags *flag);
int flag_check(int argc, char *argv[], flags *flag);
void parser(char *argv[], flags *flag, int i, int j);

#endif  // SRC_GREP_PARSER_H_