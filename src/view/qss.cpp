#include "qss.h"

using namespace s21;

QString QSS::GetMain() {
  return "QWidget{"
         "background-color: rgb(53, 54, 58);"
         "}";
}

QString QSS::GetButtonsStyle() {
  return "QPushButton{"
         "color: rgb(237, 235, 235);"
         "border: none;"
         "border-radius: 10px;"
         "background-color: rgb(55, 126, 247);"
         "font-family: 'Cuprum';"
         "font-size: 22px;"
         "}"
         "QPushButton::hover{"
         "background-color: rgb(56, 101, 241);"
         "}"
         "QPushButton::pressed{"
         "background-color: rgb(55, 126, 247);"
         "}";
}

QString QSS::GetLineStyle() {
  return "QLineEdit{"
         "color: rgb(142, 138, 139);"
         "border: none;"
         "border-radius: 5px;"
         "padding: 0 5px;"
         "background-color: rgb(32, 33, 36);"
         "font-family: 'Cuprum';"
         "font-size:14px;"
         "}";
}

QString QSS::GetSpinBoxStyle() {
  return "QDoubleSpinBox{"
         "color: rgb(142, 138, 139);"
         "border: none;"
         "border-radius: 5px;"
         "padding: 0 8px;"
         "background-color: rgb(32, 33, 36);"
         "font-family: 'Cuprum';"
         "font-size:14px;"
         "}";
}

QString QSS::GetLabelStyle() {
  return "QLabel{"
         "color: rgb(55, 126, 247);"
         "font-family: 'Cuprum';"
         "font-size: 22px;"
         "}";
}

QString QSS::GetTabWidgetStyle() {
  return "QTabBar::tab {"
         "color: rgb(237, 235, 235);"
         "background: rgb(55, 126, 247);"
         "border: 1px solid rgb(55, 126, 247);"
         "font-family: 'Cuprum';"
         "font-size: 18px;"
         "min-width: 200px;"
         "}";
}

QString QSS::GetComboBoxStyle() {
  return "QComboBox {"
         "color: rgb(142, 138, 139);"
         "border: none;"
         "border-radius: 6px;"
         "background-color: rgb(32, 33, 36);"
         "font-family: 'Cuprum';"
         "font-size: 18px;"
         "}"
         "QComboBox::drop-down {"
         "border-radius: 4px;"
         "background-color: rgb(55, 126, 247);"
         "}"
         "QComboBox::down-arrow {"
         "image: url(:/resources/0.png);"
         "width: 14px;"
         "height: 14px;"
         "}";
}

QString QSS::GetRadioButtonStyle() {
  return "QRadioButton {"
         "color: rgb(142, 138, 139);"
         "font-family: 'Cuprum';"
         "font-size:18px;"
         "}";
}
