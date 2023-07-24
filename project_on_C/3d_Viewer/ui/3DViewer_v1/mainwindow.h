#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>


#include "oglwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


 private slots:
  void on_horizontalSlider_4_sliderMoved(int position);

  void on_pushButton_clicked();

  void on_move__y_sliderMoved(int position);

  void on_move__x_sliderMoved(int position);

  void on_move__z_sliderMoved(int position);

  void on_x_rotate_slider_sliderMoved(int position);

  void on_y_rotate_slider_sliderMoved(int position);

  void on_z_rotate_slider_sliderMoved(int position);

  void on_background_1_sliderMoved(int position);

  void on_background_2_sliderMoved(int position);

  void on_background_3_sliderMoved(int position);

  void on_line_1_sliderMoved(int position);

  void on_line_2_sliderMoved(int position);

  void on_line_3_sliderMoved(int position);

  void on_vert_1_sliderMoved(int position);

  void on_vert_2_sliderMoved(int position);

  void on_vert_3_sliderMoved(int position);

  void on_vert_size_sliderMoved(int position);

  void on_line_size_sliderMoved(int position);

  void on_none_clicked();

  void on_square_clicked();

  void on_circle_clicked();

  void on_checkBox_stateChanged(int arg1);

  void on_bjpeg_clicked();

  void on_bbmp_clicked();

//  void on_bgif_clicked();

//  void bla();

  void on_bgif_clicked();

  void bla();

  void on_checkBox_2_stateChanged(int arg1);

private:
  Ui::MainWindow *ui;
  OGLWidget *widget;
  QImage grabFramebuffer();
  QGifImage *gif;
  QTimer *timer;
  int time;
};

#endif  // MAINWINDOW_H
