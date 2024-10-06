#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>
void testTextColorAndEffect() {
  char *af_cmd = tgetstr("AF", NULL);
  char *reset_cmd = tgetstr("me", NULL);
  char *blink_cmd = tgetstr("mb", NULL);
  char *bold_cmd = tgetstr("md", NULL);
  char *underline_cmd = tgetstr("us", NULL);

  tputs(tparm(af_cmd, COLOR_RED), 1, putchar);
  printf("Texte rouge\n");

  tputs(tparm(af_cmd, COLOR_GREEN), 1, putchar);
  printf("Texte vert\n");

  tputs(tparm(af_cmd, COLOR_BLUE), 1, putchar);
  printf("Texte bleu\n");

  tputs(reset_cmd, 1, putchar);
  tputs(blink_cmd, 1, putchar);
  printf("Texte clignotant\n");

  tputs(tparm(af_cmd, COLOR_GREEN), 1, putchar);
  printf("Texte vert clignotant\n");

  tputs(reset_cmd, 1, putchar);
  tputs(bold_cmd, 1, putchar);
  printf("Texte en gras\n");

  tputs(tparm(af_cmd, COLOR_RED), 1, putchar);
  printf("Texte rouge en gras\n");

  tputs(reset_cmd, 1, putchar);
  tputs(tparm(af_cmd, COLOR_GREEN), 1, putchar);
  tputs(underline_cmd, 1, putchar);
  printf("Texte vert souligné\n");

  tputs(tparm(af_cmd, COLOR_BLUE), 1, putchar);
  tputs(bold_cmd, 1, putchar);
  tputs(blink_cmd, 1, putchar);
  tputs(underline_cmd, 1, putchar);
  printf("Texte blue en gras souligné clignotant\n");
  tputs(reset_cmd, 1, putchar);
}

void print_escape_seq(char *str) {

  unsigned i = 0;
  while (str[i] != '\0') {
    if (str[i] == '\x1b') {
      printf("ESC");
    } else {
      putchar_unlocked(str[i]);
    }
    i++;
  }
  putchar('\n');
}
int main(void) {
  int ret;
  char *term_type = getenv("TERM");
  if (term_type == NULL) {
    fprintf(stderr, "TERM not defined");
    exit(0);
  }
  ret = tgetent(NULL, term_type);
  if (ret == -1) {
    fprintf(stderr, "Could not access to the database\n");
    exit(0);
  }
  if (ret == 0) {
    fprintf(stderr, "Terminal type %s is not defined in termcap databse\n",
            term_type);
    exit(0);
  }

  if (ret == 1) {
    int col_count = tgetnum("co");
    int line_count = tgetnum("li");
    // int os_flag = tgetflag("os");
    // char *cl_cap = tgetstr("cl", NULL);
    // tputs(cl_cap, 1, putchar);
    printf("the col is %d - line is %d\n", col_count, line_count);
    char *color_cap = tgetstr("AF", NULL);
    tputs(tparm(color_cap, COLOR_GREEN), 1, putchar);

    char *us_cap = tgetstr("us", NULL);
    tputs(us_cap, 1, putchar);

    char *md_cap = tgetstr("md", NULL);
    tputs(md_cap, 1, putchar);

    char *mb_cap = tgetstr("mb", NULL);
    tputs(mb_cap, 1, putchar);

    printf("NOW I AM WRITING IN GREEN\n");

    char *cwin = tgetstr("CW", NULL);
    tputs(cwin, 1, putchar);
    printf("NOW I AM WRITING IN GREEN\n");
    printf("NOW I AM WRITING IN GREEN\n");
    printf("NOW I AM WRITING IN GREEN\n");
    printf("NOW I AM WRITING IN GREEN\n");
    printf("NOW I AM WRITING IN GREEN\n");
    // char *cm_comp = tgetstr("cm", NULL);
    // tputs(tgoto(cm_comp, 0, 0), 1, putchar);
    // char *reset_cmd = tgetstr("me", NULL);
    // tputs(reset_cmd, 1, putchar);
    // printf("cool it is now reseted\n");
    // testTextColorAndEffect();
  }
  return 0;
}
