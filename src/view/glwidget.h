#ifndef SRC_VIEW_GLWIDGET_H_
#define SRC_VIEW_GLWIDGET_H_

#include <QBasicTimer>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QVector2D>

#include "../controller.h"
#include "viewer.h"

class glwidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  int wight, height;
  float red = 0, green = 0, blue = 0;
  float lred = 1, lgreen = 1, lblue = 1;
  float pred = 1, pgreen = 1, pblue = 1;
  double sc_x, sc_y, sc_z, sc;
  int proj, stip, point;
  float line = 1, point_s;
  s21::Controller contr_;

  using QOpenGLWidget::QOpenGLWidget;
  ~glwidget();
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
};

#endif  // SRC_VIEW_GLWIDGET_H_
