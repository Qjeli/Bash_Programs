#include "output.h"

void output(FILE *file_path, regex_t reg, char *file, int file_count,
            flags *flag) {
  char text[99999];
  regmatch_t pmatch[1];
  int line_matchs = 0, nline = 1, status = 0;

  while (fgets(text, 99999, file_path) != NULL) {
    status = regexec(&reg, text, 1, pmatch, 0);
    int match = 0;

    if (file_count && status == 0 && !flag->l_flag && !flag->c_flag &&
        !flag->h_flag) {
      printf("%s:", file);
    }

    if ((status == 0 && !flag->v_flag) ||
        (status == REG_NOMATCH && flag->v_flag)) {
      match = 1;
    }

    if (match && !flag->l_flag && !flag->c_flag && flag->n_flag) {
      printf("%d:", nline);
    }

    if (match && !flag->l_flag && !flag->c_flag && !flag->o_flag) {
      printf("%s", text);
      if (strrchr(text, '\n') == NULL) {
        printf("\n");
      }
    }

    if (match && flag->o_flag) {
      for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
        printf("%c", text[i]);
      }
      printf("\n");
    }

    nline++;
    line_matchs += match;
  }

  if (flag->l_flag && line_matchs > 0 && !flag->h_flag) {
    printf("%s\n", file);
  }
  if (flag->c_flag && !flag->l_flag && file_count) {
    printf("%s:", file);
    printf("%d\n", line_matchs);
  } else if (flag->c_flag && !flag->l_flag) {
    printf("%d\n", line_matchs);
  }
}
