#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAIL 0

typedef struct {
  double xMax;
  double yMax;
  double zMax;
  double xMin;
  double yMin;
  double zMin;
  double Scale_god;
} max_min;

typedef struct {
  unsigned int verts_count;
  unsigned int facets_count;
  double *verts;
  int *facets;
  char nameobj[1024];
  max_min max_min_verst;
} obj_data;

int count(char *name, obj_data *info);
int parser(char *name, obj_data *info);
unsigned int number_count(char *string);
void max_min_x_y_z(double num, obj_data *info, int n);
void shift_dot_x(obj_data *tmp, double val);
void shift_dot_y(obj_data *tmp, double val);
void shift_dot_z(obj_data *tmp, double val);
void rotate_x(obj_data *tmp, double angle);
void rotate_y(obj_data *tmp, double angle);
void rotate_z(obj_data *tmp, double angle);
void scale_c(obj_data *tmp);
