#include "parser.h"

int error = 0;

int flag_check(int argc, char *argv[], flags *flag) {
  for (int i = 1; i < argc; i++) {
    int j = 1;
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      while (argv[i][j] != '\0') {
        parser(argv, flag, i, j);
        j++;
      }
    } else if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] != '-') {
      if (strcmp(argv[i], "--number-nonblank") == 0)
        flag->b_flag = 1;
      else if (strcmp(argv[i], "--number") == 0)
        flag->n_flag = 1;
      else if (strcmp(argv[i], "--squeeze-blank") == 0)
        flag->s_flag = 1;
    } else if (argv[j][0] == '-' && argv[j][1] == '-' && argv[j][2] == '-') {
      fprintf(stderr, "stop....\n");
      error = 1;
    }
  }
  return error;
}
void parser(char *argv[], flags *flag, int i, int j) {
  switch (argv[i][j]) {
    case 'b':
      flag->b_flag = 1;
      break;
    case 'e':
      flag->e_flag = 1;
      break;
    case 'n':
      flag->n_flag = 1;
      break;
    case 's':
      flag->s_flag = 1;
      break;
    case 't':
      flag->t_flag = 1;
      break;
    case 'T':
      flag->T_flag = 1;
      break;
    case 'E':
      flag->E_flag = 1;
      break;
    case 'v':
      flag->v_flag = 1;
      break;
    default:
      fprintf(stderr, "no...\n");
      error = 1;
      break;
  }
}