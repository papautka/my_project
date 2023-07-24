#include "s21_grep.h"

int main(int argc, char *argv[]) { reader(argc, argv); }

int reader(int argc, char *argv[]) {
  grepFlag opt = {0};
  char E_pattern[1024] = {'\0'};
  char F_pattern[3072] = {'\0'};
  char buffer[bufferSize] = {'\0'};
  char pattern[4096] = {'\0'};
  const char *errstr = NULL;
  int ovector[size_ovector] = {0};

  check_opt(argc, argv, &opt, E_pattern, F_pattern);

  if (!(opt.f || opt.e)) {
    strcat(pattern, argv[optind]);
    opt.name_file = optind + 1;
  } else {
    strcat(pattern, F_pattern);
    opt.name_file = optind;
  }
  if (opt.name_file + 1 == argc) {
    opt.one_file = 1;
  }
  pcre *f_pcre = NULL;

  while (opt.name_file < argc) {
    FILE *fp = NULL;
    fp = fopen(argv[opt.name_file], "r");
    if (fp == NULL) {
      fclose(fp);
      if (!opt.s) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                argv[opt.name_file]);
      }
    } else {
      if ((f_pcre = pcre_compile(pattern, PCRE_MULTILINE, &errstr, &opt.errchar,
                                 NULL)) == NULL) {
        printf("Ошибка: %s Символ N%i Шаблон: %s", errstr, opt.errchar,
               pattern);
      } else
        pcre_free(f_pcre);
      if (opt.i) {
        f_pcre = pcre_compile(pattern, PCRE_MULTILINE | PCRE_CASELESS, &errstr,
                              &opt.errchar, NULL);
      } else {
        f_pcre =
            pcre_compile(pattern, PCRE_MULTILINE, &errstr, &opt.errchar, NULL);
      }
      while (!(feof(fp))) {
        fgets(buffer, bufferSize, fp);
        if (buffer[strlen(buffer) - 1] == '\0') {
          memset(buffer, '\0', bufferSize);
          fclose(fp);
          break;
        }
        opt.pairs = pcre_exec(f_pcre, 0, buffer, strlen(buffer), 0,
                              PCRE_NOTEMPTY, ovector, size_ovector);
        opt.num_line = opt.num_line + 1;
        if (opt.v) {
          opt.pairs = opt.pairs * (-1);
        }
        if (opt.pairs == 1) {
          opt.count = opt.count + 1;
          if (!(opt.c || opt.l)) {
            if (opt.n || opt.h) output_n_h(&opt, buffer, argv, &opt.name_file);
            if ((!opt.n && !opt.h) || (opt.f_all_in))
              output_classic(&opt, buffer, argv, &opt.name_file);
          }
        }
        memset(buffer, '\0', bufferSize);
      }
      pcre_free(f_pcre);
      if (opt.c || opt.l) {
        output_l_c_h(&opt, argv, &opt.name_file);
      }
      fclose(fp);
    }
    opt.count = 0;
    opt.num_line = 0;
    opt.name_file++;
  }
  return 0;
}

void check_opt(int argc, char *argv[], grepFlag *info, char *E_pattern,
               char *F_pattern) {
  int opchar = 0;
  int option_index = 0;

  struct option long_option[] = {{"regexp", 1, 0, 'e'},
                                 {"ignore-case", 0, 0, 'i'},
                                 {"invert-match", 0, 0, 'v'},
                                 {"count", 0, 0, 'v'},
                                 {"files-with-matches", 0, 0, 'l'},
                                 {"line-number", 0, 0, 'n'},
                                 {0, 0, 0, 0}};

  while (-1 != (opchar = getopt_long(argc, argv, "e:f:ivclnhs", long_option,
                                     &option_index))) {
    switch (opchar) {
      case 'e':
        info->e = 1;
        strcat(E_pattern, optarg);
        strcat(E_pattern, "|");
        break;
      case 'i':
        info->i = 1;
        break;
      case 'v':
        info->v = 1;
        break;
      case 'c':
        info->c = 1;
        break;
      case 'l':
        info->l = 1;
        break;
      case 'n':
        info->n = 1;
        break;
      case 'h':
        info->h = 1;
        break;
      case 'f':
        info->f = 1;
        is_f_e(optarg, F_pattern, info);
        strcat(F_pattern, "|");
        break;
      case 's':
        info->s = 1;
        break;
      default:
        printf("%s: illegal option -- %c\n", argv[0], opchar);
        printf("usage: grep [-ivclnhso] [file ...]");
    }
  }
  if (info->f || info->e) {
    strcat(F_pattern, E_pattern);
    F_pattern[strlen(F_pattern) - 1] = '\0';
  }
}
void is_f_e(char *optarg_clone, char *F_pattern_clone, grepFlag *opt) {
  char bufferfile[1024] = {'\0'};
  FILE *f = NULL;
  f = fopen(optarg_clone, "r");
  if (f != NULL) {
    while (fgets(bufferfile, 1024, f) != NULL) {
      if (strlen(bufferfile) == 1 && bufferfile[0] == '\n') {
        opt->f_all_in = 1;
      }
      if (bufferfile[strlen(bufferfile) - 1] == '\n') {
        bufferfile[strlen(bufferfile) - 1] = '|';
      }
      strcat(F_pattern_clone, bufferfile);
      memset(bufferfile, '\0', 1024);
    }
  } else {
    if (!opt->s) printf("grep: %s: No such file or directory", optarg_clone);
  }
  fclose(f);
}

void output_n_h(grepFlag *opt, char *buffer, char *argv[], int *currentFile) {
  if (opt->n && ((opt->h || opt->one_file))) {
    printf("%d:%s", opt->num_line, buffer);
  } else if (!opt->n && ((opt->h || opt->one_file))) {
    printf("%s", buffer);
  } else if (opt->n && (!opt->h)) {
    if (opt->one_file) {
      printf("%d:%s", opt->num_line, buffer);
    } else {
      printf("%s:%d:%s", argv[*currentFile], opt->num_line, buffer);
    }
  }
  proverka_where_enter(buffer);
}

void output_classic(grepFlag *opt, char *buffer, char *argv[],
                    int *currentFile) {
  if (opt->one_file) {
    printf("%s", buffer);
    proverka_where_enter(buffer);
  } else {
    printf("%s:%s", argv[*currentFile], buffer);
    proverka_where_enter(buffer);
  }
}

void output_l_c_h(grepFlag *opt, char *argv[], int *currentFile) {
  if (opt->c && !(opt->h || opt->one_file)) {
    printf("%s:", argv[*currentFile]);
  }
  if (opt->c == 1) {
    printf("%d\n", opt->l ? opt->count > 0 : opt->count);
  }
  if (opt->l && opt->count > 0) {
    printf("%s", argv[*currentFile]);
    proverka_where_enter(argv[*currentFile]);
  }
}

void proverka_where_enter(char *buffer) {
  if (buffer[strlen(buffer) - 1] != '\n') printf("\n");
}
