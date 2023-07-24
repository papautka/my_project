#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>
#include "qgifimage.h"
// #include <iostream>

extern "C" {
#include "../../c_files/3D_Viewer.h"
}

class OGLWidget : public QOpenGLWidget {
 public:
  OGLWidget(QWidget *parent = 0);
  ~OGLWidget();
  double scale;
  double x_rotate;
  double y_rotate;
  double z_rotate;
  QString file_name;
  double x_moved;
  double y_moved;
  double z_moved;
  double color_red;
  double color_green;
  double color_blue;
  double line_red;
  double line_green;
  double line_blue;
  double vert_red;
  double vert_green;
  double vert_blue;
  double vert_size;
  double line_size;
  int none;
  int square;
  int circle;
  int stripe;
  int cent_proek;
  int cent_proek_buff;

 protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

 private:
  QTimer timer;
  void do_scaling();
  void do_rotation();
  double x_rotate_buff;
  double y_rotate_buff;
  double z_rotate_buff;
  double scale_buff;
  void draw_obj(char *name, obj_data *info);
  void update_view();

  void x_move(obj_data *info);
  void y_move(obj_data *info);
  void z_move(obj_data *info);

  void rot(obj_data *info);
  void sscale(obj_data *info);
};

#endif  // OGLWIDGET_H
