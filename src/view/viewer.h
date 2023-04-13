#ifndef SRC_VIEW_VIEWER_H_
#define SRC_VIEW_VIEWER_H_

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>

#include "../controller.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

namespace s21 {
class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  Viewer(QWidget *parent = nullptr);
  ~Viewer();

 private slots:
  void on_open_clicked();
  void on_render_clicked();
  bool filecheck(char *filename);

  void on_pos_x_valueChanged(double arg1);
  void on_pos_y_valueChanged(double arg1);
  void on_pos_z_valueChanged(double arg1);

  void on_eu_x_valueChanged(double arg1);
  void on_eu_y_valueChanged(double arg1);
  void on_eu_z_valueChanged(double arg1);

  void on_scl_x_valueChanged(double arg1);
  void on_scl_y_valueChanged(double arg1);
  void on_scl_z_valueChanged(double arg1);
  void on_scale_full_valueChanged(double arg1);

  void on_color_background_clicked();
  void on_color_edges_clicked();
  void on_color_vertices_clicked();

  void on_proj_parallel_toggled(bool checked);
  void on_proj_central_toggled(bool checked);

  void on_type_solid_toggled(bool checked);
  void on_type_dashed_toggled(bool checked);

  void on_display_method_currentIndexChanged(int index);
  void on_thickness_valueChanged(int value);
  void on_size_vertices_valueChanged(int value);

  void on_actionBMP_triggered();
  void on_actionGIF_triggered();
  void saveGifFrame();

 private:
  Ui::Viewer *ui;
  s21::Controller contr_;

  double x_ = 0, y_ = 0, z_ = 0;
  double xr_ = 0, yr_ = 0, zr_ = 0;
  double s_ = 100, xs_ = 1, ys_ = 1, zs_ = 1;
  int time_;

  QGifImage *gif_;
  QImage *frame_;
  QTimer *timer_;
  QString giffile_;
  QSettings *settings_;

  void SaveSettings();
  void LoadSettings();
  void SetEnabled();
  void SetTrueEnabled();
  void SetQss();
};
}  // namespace s21

#endif  // SRC_VIEW_VIEWER_H_
