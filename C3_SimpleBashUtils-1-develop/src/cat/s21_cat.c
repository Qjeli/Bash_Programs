#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flags flag = {0};
  if (argc > 1) {
    if (!flag_check(argc, argv, &flag)) {
      if (flag.b_flag == 1) flag.n_flag = 0;
      if (flag.t_flag == 1 || flag.e_flag == 1) flag.v_flag = 1;
      s21_cat(argc, argv, &flag);
    }
  } else {
  }
  return 1;
}

void check_pos(int argc, char *argv[], flags *flag) {
  int sym;
  char lin = '\n';
  unsigned int buff_str = 0;
  FILE *file;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, "%s: No such file or directory\n", argv[i]);
      } else {
        int i = 1;
        while ((sym = fgetc(file)) != EOF) {
          if ((flag->s_flag == 1 && sym == '\n') &&
              (lin == '\n' || lin == '\0')) {
            buff_str++;
            if (buff_str > 1) continue;
          } else {
            buff_str = 0;
          }
          if ((flag->b_flag == 1 && sym != '\n' && lin == '\n') ||
              (flag->n_flag == 1 && lin == '\n' && flag->b_flag != 1)) {
            printf("%6d\t", i++);
          }
          if (((flag->e_flag == 1) || (flag->E_flag == 1)) && sym == '\n') {
            putchar('$');
          }
          if (((flag->t_flag == 1) || (flag->T_flag == 1)) && sym == '\t') {
            putchar('^');
            sym = 'I';
          }
          if (flag->v_flag == 1 && sym != '\n') {
            flag_v(&sym);
          }
          lin = sym;
          putchar(sym);
        }
        fclose(file);
      }
    }
  }
}

void s21_cat(int argc, char *argv[], flags *flag) {
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
    flag->b_flag = 0, flag->e_flag = 0, flag->e_flag = 0, flag->n_flag = 0,
    flag->s_flag = 0, flag->t_flag = 0, flag->t_flag = 0, flag->v_flag = 0;
    check_pos(argc, argv, flag);
    fprintf(stderr, "why...\n");
  } else {
    check_pos(argc, argv, flag);
  }
}
void flag_v(int *ch) {
  if (*ch >= 0 && *ch <= 31 && *ch != 9 && *ch != 10) {
    *ch += 64;
    printf("^");
  } else if (*ch == 127) {
    *ch -= 64;
    printf("^");
  }
}
