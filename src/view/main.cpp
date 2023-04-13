#include <QApplication>
#include <QLabel>

#include "../controller.h"
#include "glwidget.h"
#include "viewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Viewer w;
  w.show();
  return a.exec();
}
