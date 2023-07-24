#ifndef S21_CAT_GREP_CAT_S21_GREP_H_
#define S21_CAT_GREP_CAT_S21_GREP_H_

#include <getopt.h>
#include <pcre.h>
#include <stdio.h>
#include <string.h>

#define bufferSize 4096
#define size_ovector 1024

typedef struct {
  int e;
  int f;
  int i;
  int v;
  int c;
  int l;
  int n;
  int s;
  int h;
  int j;
  int one_file;
  int num_line;
  int count;
  int f_all_in;
  int errchar;
  int pairs;
  int name_file;
} grepFlag;

int reader(int argc, char *argv[]);
void check_opt(int argc, char *argv[], grepFlag *info, char *E_pattern,
               char *F_pattern);
void is_f_e(char *optarg_clone, char *F_pattern_clone, grepFlag *flags);
void output_n_h(grepFlag *flags, char *buffer, char *argv[], int *currentFile);
void output_classic(grepFlag *flags, char *buffer, char *argv[],
                    int *currentFile);
void proverka_where_enter(char *buffer);
void output_l_c_h(grepFlag *flags, char *argv[], int *currentFile);

#endif  // S21_CAT_GREP_CAT_S21_c_GREP_