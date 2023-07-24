#include "oglwidget.h"
#include <QSettings> // new

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  timer.start(16);
}

OGLWidget::~OGLWidget() {}

void OGLWidget::initializeGL() {
  scale = 0.5;
  x_rotate = 30;
  y_rotate = 30;
  z_rotate = 30;
  x_rotate_buff = x_rotate;
  y_rotate_buff = y_rotate;
  z_rotate_buff = z_rotate;
  scale_buff = scale;
  file_name = "nan";
  x_moved = 0.0;
  y_moved = 0.0;
  z_moved = 0.0;
  QSettings mySettings;
  color_red = mySettings.value("red").toDouble();
  color_green = mySettings.value("green").toDouble();
  color_blue = mySettings.value("blue").toDouble();
  line_red = mySettings.value("line_red").toDouble();
  line_green = mySettings.value("line_green").toDouble();
  line_blue = mySettings.value("line_blue").toDouble();
  vert_red = mySettings.value("vert_red").toDouble();
  vert_green = mySettings.value("vert_green").toDouble();
  vert_blue = mySettings.value("vert_blue").toDouble();
  vert_size = mySettings.value("vert_size").toDouble();
  line_size = mySettings.value("line_size").toDouble();
  none = mySettings.value("none").toDouble();
  square = mySettings.value("square").toDouble();
  circle = mySettings.value("circle").toDouble();
  stripe = mySettings.value("stripe").toDouble();
  cent_proek_buff = cent_proek;

  glClearColor(color_red, color_green, color_blue, 1);
}

void OGLWidget::paintGL() {
  update_view();

  glClearColor(color_red, color_green, color_blue, 1);

  obj_data info;
  info.facets_count = 0;
  info.verts_count = 0;

  std::string s = file_name.toStdString();
  char *name = const_cast<char *>(s.c_str());

  int status = count(name, &info);
  if (status == SUCCESS) {
    draw_obj(name, &info);
  }
  QSettings mySettings;
  mySettings.setValue("red", color_red);
  mySettings.setValue("green", color_green);
  mySettings.setValue("blue", color_blue);
  mySettings.setValue("line_red", line_red);
  mySettings.setValue("line_green", line_green);
  mySettings.setValue("line_blue", line_blue);
  mySettings.setValue("vert_red", vert_red);
  mySettings.setValue("vert_green", vert_green);
  mySettings.setValue("vert_blue", vert_blue);
  mySettings.setValue("vert_size", vert_size);
  mySettings.setValue("line_size", line_size);
  mySettings.setValue("none", none);
  mySettings.setValue("square", square);
  mySettings.setValue("circle", circle);
  mySettings.setValue("stripe", stripe);
}

void OGLWidget::resizeGL(int w, int h) {}

void OGLWidget::draw_obj(char *name, obj_data *info) {
  parser(name, info);
  x_move(info);
  y_move(info);
  z_move(info);
  sscale(info);

  rot(info);

  if (none == 0) {
      glPointSize(vert_size);
      glColor3d(vert_red, vert_green, vert_blue);
      if (circle) glEnable(GL_POINT_SMOOTH);
      if (square) glDisable(GL_POINT_SMOOTH);
      for (unsigned int point = 0; point < info->verts_count; point++) {
        glBegin(GL_POINTS);
        glVertex3d(info->verts[point * 3], info->verts[point * 3 + 1],
                   info->verts[point * 3 + 2]);
        glEnd();
      }
  }
  glLineWidth(line_size);
  glColor3d(line_red, line_green, line_blue);
  if (stripe) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00F0);
  } else {
      glDisable(GL_LINE_STIPPLE);
  }
  glBegin(GL_LINES);
  for (unsigned int line = 0; line < info->facets_count / 2; line++) {
    if (info->facets[line * 2] != info->facets[line * 2 + 1]) {
      unsigned int point_number = info->facets[line * 2];
      glVertex3d(info->verts[point_number * 3],
                 info->verts[point_number * 3 + 1],
                 info->verts[point_number * 3 + 2]);
      point_number = info->facets[line * 2 + 1];
      glVertex3d(info->verts[point_number * 3],
                 info->verts[point_number * 3 + 1],
                 info->verts[point_number * 3 + 2]);
    }
  }
  glEnd();
}

void OGLWidget::update_view() {
  if (scale != 1) {
    do_scaling();
    scale_buff = scale;
  }
  if (x_rotate != x_rotate_buff || y_rotate != y_rotate_buff ||
      z_rotate != z_rotate_buff || cent_proek != cent_proek_buff) {
    scale = scale_buff;
    do_scaling();
  }
  x_rotate_buff = x_rotate;
  y_rotate_buff = y_rotate;
  z_rotate_buff = z_rotate;
  cent_proek_buff = cent_proek;
  scale = 1;
}

void OGLWidget::do_scaling() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (cent_proek) {
      glFrustum(-1, 1, -1, 1, 2, 15);
      glTranslated(0, 0, -6);

  } else {
      glOrtho(-1, 1, -1, 1, 100, -100);
  }
  glScaled(scale, scale, scale);
}

void OGLWidget::x_move(obj_data *info) { shift_dot_x(info, x_moved); }

void OGLWidget::y_move(obj_data *info) { shift_dot_y(info, y_moved); }

void OGLWidget::z_move(obj_data *info) { shift_dot_z(info, z_moved); }

void OGLWidget::rot(obj_data *info) {
  rotate_z(info, z_rotate);
  rotate_x(info, x_rotate);
  rotate_y(info, y_rotate);
}

void OGLWidget::sscale(obj_data *info) { scale_c(info); }
