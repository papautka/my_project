#include "s21_cat.h"

#define bufferSize 4096

void check_flags(int argc, char *argv[], catFlag *info) {
  int opchar = 0;
  int option_index = 0;

  struct option long_option[] = {{"number-nonblank", 0, 0, 'b'},
                                 {"number", 0, 0, 'n'},
                                 {"squeeze-blank", 0, 0, 's'},
                                 {0, 0, 0, 0}};
  while (-1 != (opchar = getopt_long(argc, argv, "+benstvTE", long_option,
                                     &option_index))) {
    switch (opchar) {
      case 'b':
        info->b = 1;
        break;
      case 'n':
        info->n = 1;
        break;
      case 's':
        info->s = 1;
        break;
      case 't':
        info->t = 1;
        info->v = 1;
        break;
      case 'v':
        info->v = 1;
        break;
      case 'T':
        info->t = 1;
        break;
      case 'E':
        info->e = 1;
        break;
      case 'e':
        info->e = 1;
        info->v = 1;
        break;
      default:
        printf("%s: illegal option -- %c\n", argv[0], opchar);
        printf("usage: cat [-benstuv] [file ...]");
    }
  }
}

void Reader(int argc, char *argv[]) {
  catFlag flags = {0};
  check_flags(argc, argv, &flags);
  char buffer[bufferSize] = {'\0'};
  int currentFile = optind;
  FILE *fp = NULL;
  while (currentFile < argc) {
    fp = fopen(argv[currentFile], "r");
    if (fp != NULL) {
      int start_line = 1;
      int n_empty_line = 1;
      char now_char = '\n';
      char next_char = ' ';
      while ((*buffer = fgetc(fp)) != EOF) {
        if (flags.s && flag_s(now_char, next_char, *buffer)) continue;
        if (flags.b) {
          flags.n = 0;
          flag_b(now_char, &n_empty_line, *buffer);
        }
        if (flags.n) {
          flags.b = 0;
          start_line = flag_n(start_line, &n_empty_line, *buffer);
        }

        if (flags.v) flag_v(buffer);
        if (flags.e) flag_e(*buffer);
        next_char = now_char;
        now_char = *buffer;
        if (flags.t && flag_t(*buffer)) continue;
        if (*buffer == '\0')
          fputc(*buffer, stdout);
        else
          fputs(buffer, stdout);
        memset(buffer, '\0', bufferSize);
      }
      fclose(fp);
    } else {
      fclose(fp);
      fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
              argv[currentFile]);
    }
    currentFile++;
  }
}

int flag_b(char now_char, int *n_empty_line, char buffer) {
  if (now_char == '\n' && buffer != '\n') {
    printf("%6d\t", (*n_empty_line)++);
  }
  return buffer == '\n';
}

int flag_t(char symbol) {
  int tab = 0;
  if (symbol == '\t') tab = printf("^I");
  return tab;
}

int flag_e(char symbol) {
  if (symbol == '\n') printf("$");
  return symbol == '\n';
}

int flag_n(int start_line, int *n_all_line, char symbol) {
  if (start_line) printf("%6d\t", (*n_all_line)++);
  return symbol == '\n';
}

int flag_s(char now_char, char next_char, char symbol) {
  return (symbol == '\n' && now_char == '\n' && next_char == '\n');
}

int flag_v(char *buffer) {
  unsigned char number = *buffer;
  if ((number <= 8) || (number >= 11 && number <= 31) ||
      (number >= 127 && number <= 159))
    strcpy(buffer, spec_symbol[number]);
  return number;
}

int main(int argc, char *argv[]) { Reader(argc, argv); }
