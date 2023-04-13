#include "glwidget.h"

#include <cmath>

glwidget::~glwidget() {}

void glwidget::initializeGL() {
  initializeOpenGLFunctions();
  sc_x = 1.0, sc_y = 1.0, sc_z = 1.0;
}

void glwidget::resizeGL(int w, int h) {}

void glwidget::paintGL() {
  glClearColor(red, green, blue, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (proj) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScaled(sc_x, sc_y, sc_z);
    glTranslated(0, 0, -3.0);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glScaled(sc_x, sc_y, sc_z);
    glOrtho(-1, 1, -1, 1, -100, 100);
  }
  glScaled(sc, sc, sc);

  glEnableClientState(GL_VERTEX_ARRAY);
  glLineWidth(line);
  if (stip) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glVertexPointer(3, GL_DOUBLE, 0, contr_.vertices_);
  glPointSize(point_s);
  glColor3d(pred, pgreen, pblue);
  if (point == 2)
    glEnable(GL_POINT_SMOOTH);
  else
    glDisable(GL_POINT_SMOOTH);
  if (point) glDrawArrays(GL_POINTS, 0, contr_.count_of_vertexes_);
  glColor3d(lred, lgreen, lblue);
  glDrawElements(GL_LINES, contr_.count_of_facets_, GL_UNSIGNED_INT,
                 contr_.indices_);
  glDisableClientState(GL_VERTEX_ARRAY);
}
