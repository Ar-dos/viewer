#ifndef QSS_H
#define QSS_H
#include <QMainWindow>

namespace s21 {

class QSS {
 public:
  static QString GetMain();
  static QString GetButtonsStyle();
  static QString GetLineStyle();
  static QString GetSpinBoxStyle();
  static QString GetLabelStyle();
  static QString GetTabWidgetStyle();
  static QString GetComboBoxStyle();
  static QString GetRadioButtonStyle();
};
}  // namespace s21

#endif  // QSS_H
