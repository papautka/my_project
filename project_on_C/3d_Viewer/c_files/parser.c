#include "3D_Viewer.h"

/** \file
@brief Парсер .obj файлов
*/

/*!
Эта функция считает количество точек и фасетов в файле name и записывает его в
info.verts_count и info.facets_count соответственно Возвращает 1 по умолчанию, 0
если файл не найден
*/
int count(char *name, obj_data *info) {
  int ret = SUCCESS;
  FILE *file = fopen(name, "r");
  info->verts_count = 0;
  info->facets_count = 0;
  if (file == NULL) {
    ret = FAIL;
  } else {
    char str[2048];
    while (fgets(str, 2047, file)) {
      if (str[0] == 'v' && str[1] == ' ') {
        info->verts_count++;
      }
      if (str[0] == 'f' && str[1] == ' ') {
        info->facets_count += number_count(str);
      }
    }
    info->facets_count *= 2;
    fclose(file);
  }
  return ret;
}

/*!
Основной парсер, преобразовывает информацию из .obj файла name в массивы точек и
фасетов, читабельные для qt Возвращает 1 по умолчанию, 0 если файл не найден
*/
int parser(char *name, obj_data *info) {
  int ret = SUCCESS;
  info->verts = (double *)malloc((info->verts_count * 3 + 1) * sizeof(double));
  info->facets = (int *)malloc((info->facets_count + 1) * sizeof(int));
  FILE *file = fopen(name, "r");
  if (file == NULL) {
    ret = FAIL;
  } else {
    char str[2048];
    char *endptr = str + 1;
    int v = 0;
    int f = 0;
    int first_facet;
    info->max_min_verst.Scale_god = 0.0;
    while (fgets(str, 2047, file)) {
      endptr = str + 1;
      if (str[0] == 'o' && str[1] == ' ') {
        strcpy(info->nameobj, str + 2);
      }
      if (str[0] == 'v' && str[1] == ' ') {
        for (int n = 0; n < 3; n++) {
          info->verts[v] = strtod(endptr, &endptr);
          max_min_x_y_z(info->verts[v], info, n);
          v++;
        }
      } else if (str[0] == 'f' && str[1] == ' ') {
        first_facet = f;
        while (endptr - str < (int)strlen(str)) {
          if (*endptr == ' ' && number_count(endptr)) {
            info->facets[f] = (int)strtod(endptr, &endptr);
            if (info->facets[f] < 0) {
              info->facets[f] = info->verts_count + 1 + info->facets[f];
            }
            if (f != first_facet) {
              info->facets[f + 1] = info->facets[f];
              f++;
            }
            f++;
          } else {
            endptr++;
          }
        }
        info->facets[f++] = info->facets[first_facet];
      }
    }
    for (unsigned int i = 0; i < info->facets_count; i++) {
      info->facets[i] -= 1;
    }
    fclose(file);
  }
  return ret;
}

/*!
Считает количество чисел в строке, которым предшествует пробел
*/
unsigned int number_count(char *string) {
  int n = 0;
  for (int i = 0; i < (int)strlen(string); i++) {
    if (string[i] == ' ' && ((string[i + 1] >= '0' && string[i + 1] <= '9') ||
                             string[i + 1] == '.' || string[i + 1] == '-')) {
      n++;
    }
  }
  return n;
}

void max_min_x_y_z(double num, obj_data *info, int n) {
  if (n == 0) {
    if (info->max_min_verst.xMax < num) info->max_min_verst.xMax = num;
    if (info->max_min_verst.xMin > num) info->max_min_verst.xMin = num;
  } else if (n == 1) {
    if (info->max_min_verst.yMax < num) info->max_min_verst.yMax = num;
    if (info->max_min_verst.yMin > num) info->max_min_verst.yMin = num;
  } else if (n == 2) {
    if (info->max_min_verst.zMax < num) info->max_min_verst.zMax = num;
    if (info->max_min_verst.zMin > num) info->max_min_verst.zMin = num;
  }
  if (fabs(num) > info->max_min_verst.Scale_god) {
    info->max_min_verst.Scale_god = fabs(num);
  }
}
