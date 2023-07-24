#include "3D_Viewer.h"
/// @brief Передвигает по x
/// @param tmp Массив вершин и их количество
/// @param val На сколько передвигаем
void shift_dot_x(obj_data *tmp, double val) {
  for (unsigned int i = 0; i < tmp->verts_count * 3; i = i + 3) {
    tmp->verts[i] = tmp->verts[i] + val;
  }
}
/// @brief Передвигает по y
/// @param tmp Массив вершин и их количество
/// @param val На сколько передвигаем
void shift_dot_y(obj_data *tmp, double val) {
  for (unsigned int i = 1; i < tmp->verts_count * 3; i = i + 3) {
    tmp->verts[i] = tmp->verts[i] + val;
  }
}
/// @brief Передвигает по z
/// @param tmp Массив вершин и их количество
/// @param val На сколько передвигаем
void shift_dot_z(obj_data *tmp, double val) {
  for (unsigned int i = 2; i < tmp->verts_count * 3; i = i + 3) {
    tmp->verts[i] = tmp->verts[i] + val;
  }
}

/// @brief Поворачиваем по x
/// @param tmp  Массив вершин и их количество
/// @param angle Угол поворота
void rotate_x(obj_data *tmp, double angle) {
  angle = angle * M_PI / 180;
  double cosA = cos(angle);
  double sinA = sin(angle);
  unsigned int j = 0;
  for (unsigned int i = 0; i < tmp->verts_count; i++) {
    double y = tmp->verts[j + 1];
    double z = tmp->verts[j + 2];
    tmp->verts[j + 1] = y * cosA - z * sinA;
    tmp->verts[j + 2] = y * sinA + z * cosA;
    j = j + 3;
  }
}
/// @brief Поворачиваем по y
/// @param tmp Массив вершин и их количество
/// @param angle Угол поворота
void rotate_y(obj_data *tmp, double angle) {
  angle = angle * M_PI / 180;
  double cosA = cos(angle);
  double sinA = sin(angle);
  unsigned int j = 0;
  for (unsigned int i = 0; i < tmp->verts_count; i++) {
    double x = tmp->verts[j];
    double z = tmp->verts[j + 2];
    tmp->verts[j] = x * cosA + z * sinA;
    tmp->verts[j + 2] = (-1) * x * sinA + z * cosA;
    j = j + 3;
  }
}
/// @brief Поворачиваем по z
/// @param tmp Массив вершин и их количество
/// @param angle Угол поворота
void rotate_z(obj_data *tmp, double angle) {
  angle = angle * M_PI / 180;
  double cosA = cos(angle);
  double sinA = sin(angle);
  int j = 0;
  for (unsigned int i = 0; i < tmp->verts_count; i++) {
    double x = tmp->verts[j];
    double y = tmp->verts[j + 1];
    tmp->verts[j] = x * cosA + y * sinA;
    tmp->verts[j + 1] = (-1) * x * sinA + y * cosA;
    j = j + 3;
  }
}
/// @brief Масштабируем
/// @param tmp Массив вершин и их количество
/// @param val на сколько масштабируем
void scale_c(obj_data *tmp) {
  double val = tmp->max_min_verst.Scale_god;
  for (unsigned int i = 0; i < tmp->verts_count * 3; i++) {
    tmp->verts[i] = tmp->verts[i] / val;
  }
}
