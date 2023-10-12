#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int res;
  char pattern[99999];
  flags flag = {0};
  res = flag_check(argc, argv, pattern, &flag);
  if (argc >= 3 && res != 1) {
    s21_grep(argc, argv, pattern, &flag);
  }
  return res;
}

int flag_check(int argc, char **argv, char *pattern, flags *flag) {
  int c = 0, res = 0;
  while ((c = getopt(argc, argv, "e:ivclnhsof:")) != -1) {
    switch (c) {
      case 'e':
        flag->e_flag = 1;
        sprintf(pattern, "%s", optarg);
        break;
      case 'i':
        flag->i_flag = 1;
        break;
      case 'v':
        flag->v_flag = 1;
        break;
      case 'c':
        flag->c_flag = 1;
        break;
      case 'l':
        flag->l_flag = 1;
        break;
      case 'n':
        flag->n_flag = 1;
        break;
      case 'h':
        flag->h_flag = 1;
        break;
      case 's':
        flag->s_flag = 1;
        break;
      case 'o':
        flag->o_flag = 1;
        break;
      case 'f':
        flag->f_flag = 1;
        sprintf(pattern, "%s", optarg);
        break;
      default:
        res = 1;
        if (!flag->s_flag) {
          printf("nah ah stap");
        }
        break;
    }
  }
  return res;
}

void check_pos(int argc, char **argv, char *pattern, flags *flag) {
  char patternL[99999] = {0};
  int file_count = 0;
  int cols = 0;

  if (!flag->f_flag && !flag->e_flag) {
    sprintf(patternL, "%s", argv[optind++]);
  } else if (flag->f_flag) {
    cols = pattern_check(patternL, pattern);
  } else if (!flag->f_flag && flag->e_flag) {
    sprintf(patternL, "%s", pattern);
  }

  if (cols != -1) {
    if (argc - optind > 1) {
      file_count = 1;
    }
    for (int i = optind; i < argc; i++) {
      prep(argv[i], file_count, patternL, flag);
    }
  }
}

void s21_grep(int argc, char **argv, char *pattern, flags *flag) {
  int check = 1;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      check = 0;
    }
    if (check == 0 && argv[i][0] == '-') {
      check = -1;
    }
  }
  if (check == -1) {
    flag->e_flag = 1, flag->i_flag = 1, flag->v_flag = 1, flag->c_flag = 1,
    flag->l_flag = 1, flag->n_flag = 1, flag->h_flag = 1, flag->s_flag = 1,
    flag->o_flag = 1, flag->f_flag = 1;
    // check_pos(argc, argv, pattern, flag);
    fprintf(stderr, "why...\n");
  } else {
    check_pos(argc, argv, pattern, flag);
  }
}

void prep(char *file, int file_count, char *pattern, flags *flag) {
  int sflags = (flag->i_flag == 1) ? REG_ICASE | REG_EXTENDED : REG_EXTENDED;
  regex_t reg;
  FILE *file_path = fopen(file, "r");

  if (file != NULL) {
    regcomp(&reg, pattern, sflags);
    output(file_path, reg, file, file_count, flag);
    regfree(&reg);
    fclose(file_path);
  } else if (!flag->s_flag) {
    printf("%s: No such file or directory\n", file);
  }
}

int pattern_check(char *pattern, char *temp) {
  FILE *file_path = fopen(temp, "r");
  int err = 0;
  if (file_path != NULL) {
    err = 0;
    int fileBuf, i = 0;
    while ((fileBuf = fgetc(file_path)) != EOF) {
      if (fileBuf == '\n' || fileBuf == 13) {
        pattern[i++] = '|';
      }
      if (fileBuf != '\n' && fileBuf != 13) {
        pattern[i++] = fileBuf;
      }
    }
    if (pattern[i--] == '|') {
      pattern[i--] = '\0';
    }
    fclose(file_path);
  } else {
    err = -1;
  }
  return err;
}
