#include "mainwindow.h"
#include <QSettings> // new


#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QSettings mySettings;
  ui->background_1->setValue(mySettings.value("red_slider").toInt());
  ui->background_2->setValue(mySettings.value("green_slider").toInt());
  ui->background_3->setValue(mySettings.value("blue_slider").toInt());
  ui->line_1->setValue(mySettings.value("red_slider_line").toInt());
  ui->line_2->setValue(mySettings.value("green_slider_line").toInt());
  ui->line_3->setValue(mySettings.value("blue_slider_line").toInt());
  ui->vert_1->setValue(mySettings.value("red_slider_vert").toInt());
  ui->vert_2->setValue(mySettings.value("green_slider_vert").toInt());
  ui->vert_3->setValue(mySettings.value("blue_slider_vert").toInt());
  ui->vert_size->setValue(mySettings.value("vert_size_slider").toInt());
  ui->line_size->setValue(mySettings.value("line_size_slider").toInt());
  ui->none->setChecked(mySettings.value("none_check").toInt());
  ui->square->setChecked(mySettings.value("square_check").toInt());
  ui->circle->setChecked(mySettings.value("circle_check").toInt());
  ui->checkBox->setChecked(mySettings.value("checkBox").toInt());
}

MainWindow::~MainWindow() {
    QSettings mySettings;
    mySettings.setValue("red_slider", ui->background_1->value());
    mySettings.setValue("green_slider", ui->background_2->value());
    mySettings.setValue("blue_slider", ui->background_3->value());
    mySettings.setValue("red_slider_line", ui->line_1->value());
    mySettings.setValue("green_slider_line", ui->line_2->value());
    mySettings.setValue("blue_slider_line", ui->line_3->value());
    mySettings.setValue("red_slider_vert", ui->vert_1->value());
    mySettings.setValue("green_slider_vert", ui->vert_2->value());
    mySettings.setValue("blue_slider_vert", ui->vert_3->value());
    mySettings.setValue("vert_size_slider", ui->vert_size->value());
    mySettings.setValue("line_size_slider", ui->line_size->value());
    mySettings.setValue("none_check", ui->none->isChecked());
    mySettings.setValue("square_check", ui->square->isChecked());
    mySettings.setValue("circle_check", ui->circle->isChecked());
    mySettings.setValue("checkBox", ui->checkBox->isChecked());
    delete ui;
}

void MainWindow::on_horizontalSlider_4_sliderMoved(int position) {
  ui->openGLWidget->scale = position * 1. / 100.;
}

void MainWindow::on_pushButton_clicked() {
  ui->openGLWidget->file_name =
      QFileDialog::getOpenFileName(nullptr, QObject::tr("open a file"), "/",
                                   QObject::tr("Objects Files (*.obj)"));
  QString file = ui->openGLWidget->file_name;

      QFile f(file);
      QFileInfo fileInfo(f.fileName());
      QString filename(fileInfo.fileName());

      ui->file_name->setText(filename);


  obj_data info;
  info.facets_count = 0;
  info.verts_count = 0;

  std::string s = ui->openGLWidget->file_name.toStdString();
  char *name = const_cast<char *>(s.c_str());

  int status = count(name, &info);
  if (status == SUCCESS) {
    ui->facet_count->setText(QString::number(info.facets_count / 2));
    ui->vertex_count->setText(QString::number(info.verts_count));
    parser(name, &info);
    ui->obj_name->setText(info.nameobj);
  }
}

void MainWindow::on_move__y_sliderMoved(int position) {
  qreal doubleValue = static_cast<qreal>(position);
  doubleValue = doubleValue / 10.;
  ui->openGLWidget->y_moved = doubleValue;
}

void MainWindow::on_move__x_sliderMoved(int position) {
  qreal doubleValue = static_cast<qreal>(position);
  doubleValue = doubleValue / 10.;
  ui->openGLWidget->x_moved = doubleValue;
}

void MainWindow::on_move__z_sliderMoved(int position) {
  qreal doubleValue = static_cast<qreal>(position);
  doubleValue = doubleValue / 10.;
  ui->openGLWidget->z_moved = doubleValue;
}

void MainWindow::on_x_rotate_slider_sliderMoved(int position) {
  qreal doubleValue = static_cast<qreal>(position);
  ui->openGLWidget->x_rotate = doubleValue;
}

void MainWindow::on_y_rotate_slider_sliderMoved(int position) {
  qreal doubleValue = static_cast<qreal>(position);
  ui->openGLWidget->y_rotate = doubleValue;
}

void MainWindow::on_z_rotate_slider_sliderMoved(int position) {
  qreal doubleValue = static_cast<qreal>(position);
  ui->openGLWidget->z_rotate = doubleValue;
}

void MainWindow::on_background_1_sliderMoved(int position)
{
    ui->openGLWidget->color_red = position * 0.01;
}


void MainWindow::on_background_2_sliderMoved(int position)
{
    ui->openGLWidget->color_green = position * 0.01;
}


void MainWindow::on_background_3_sliderMoved(int position)
{
    ui->openGLWidget->color_blue = position * 0.01;
}


void MainWindow::on_line_1_sliderMoved(int position)
{
    ui->openGLWidget->line_red = position * 0.01;
}


void MainWindow::on_line_2_sliderMoved(int position)
{
    ui->openGLWidget->line_green = position * 0.01;
}


void MainWindow::on_line_3_sliderMoved(int position)
{
    ui->openGLWidget->line_blue = position * 0.01;
}


void MainWindow::on_vert_1_sliderMoved(int position)
{
    ui->openGLWidget->vert_red = position * 0.01;
}


void MainWindow::on_vert_2_sliderMoved(int position)
{
    ui->openGLWidget->vert_green = position * 0.01;
}


void MainWindow::on_vert_3_sliderMoved(int position)
{
    ui->openGLWidget->vert_blue = position * 0.01;
}


void MainWindow::on_vert_size_sliderMoved(int position)
{
    ui->openGLWidget->vert_size = position * 0.3;
}


void MainWindow::on_line_size_sliderMoved(int position)
{
    ui->openGLWidget->line_size = position * 0.2;
}

void MainWindow::on_none_clicked()
{
    ui->openGLWidget->none = 1;
    ui->openGLWidget->square = 0;
    ui->openGLWidget->circle = 0;
}


void MainWindow::on_square_clicked()
{
    ui->openGLWidget->none = 0;
    ui->openGLWidget->square = 1;
    ui->openGLWidget->circle = 0;
}


void MainWindow::on_circle_clicked()
{
    ui->openGLWidget->none = 0;
    ui->openGLWidget->square = 0;
    ui->openGLWidget->circle = 1;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->openGLWidget->stripe = arg1;
}


void MainWindow::on_bjpeg_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "JPEG (*.jpg *.jpeg)");
        ui->openGLWidget->grab().save(file);

}


void MainWindow::on_bbmp_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "BMP (*.bmp)");
        ui->openGLWidget->grab().save(file);

}



void MainWindow::bla() {
  if (time < 55) {
    QImage image;
  image = ui->openGLWidget->grab().toImage();
    gif->addFrame(image, 10);
    time++;
  } else {
    QString gif_save_path_ = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    gif->save(gif_save_path_);
    timer->stop();
    delete timer;
    delete gif;
  }
}

void MainWindow::on_bgif_clicked()
{
        time = 0;
        gif = new QGifImage();
        timer = new QTimer(this);
        gif->setDefaultDelay(100);
        connect(timer, &QTimer::timeout, this, &MainWindow::bla);
        timer->start(100);
}




void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    ui->openGLWidget->cent_proek = arg1;
}

