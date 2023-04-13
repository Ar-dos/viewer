#include "viewer.h"

#include <QTimer>
#include <fstream>

#include "glwidget.h"
#include "qss.h"
#include "ui_viewer.h"

using namespace s21;

Viewer::Viewer(QWidget* parent) : QMainWindow(parent), ui(new Ui::Viewer) {
  ui->setupUi(this);
  SetQss();
  LoadSettings();
  ui->openGLWidget->setUpdatesEnabled(false);
  SetEnabled();
}

Viewer::~Viewer() {
  SaveSettings();
  delete ui;
}

void Viewer::on_open_clicked() {
  QString filter = "Object file (*.obj)";
  QString file_name =
      QFileDialog::getOpenFileName(this, "Open a file", "/", filter);
  ui->pwd->setText(file_name);
  ui->openGLWidget->update();
}

bool Viewer::filecheck(char* filename) {
  std::ifstream file(filename, std::ifstream::in);
  return file.good();
}

void Viewer::on_render_clicked() {
  QByteArray nameobject = ui->pwd->text().toLocal8Bit();
  char* filename = nameobject.data();
  if (!filecheck(filename)) {
    ui->pwd->setText("Damn! My file wont open up.");
    SetEnabled();
  } else {
    contr_ = s21::Controller(filename);
    ui->openGLWidget->contr_ = contr_;
    ui->openGLWidget->setUpdatesEnabled(true);
    ui->openGLWidget->update();
    ui->retranslateUi(this);
    x_ = 0, y_ = 0, z_ = 0, xr_ = 0, yr_ = 0, zr_ = 0, xs_ = 1, ys_ = 1,
    zs_ = 1, s_ = 100;
    SetTrueEnabled();
    ui->vertices->setText("вершин: " +
                          QString::number(contr_.count_of_vertexes_));
    ui->indices->setText("ребер: " +
                         QString::number(contr_.count_of_facets_ / 2));
  }
}

void Viewer::on_pos_x_valueChanged(double arg1) {
  contr_.XPos(arg1 - x_);
  ui->openGLWidget->contr_ = contr_;
  ui->openGLWidget->update();
  x_ = arg1;
}

void Viewer::on_pos_y_valueChanged(double arg1) {
  contr_.YPos(arg1 - y_);
  ui->openGLWidget->contr_ = contr_;
  ui->openGLWidget->update();
  y_ = arg1;
}

void Viewer::on_pos_z_valueChanged(double arg1) {
  contr_.ZPos(arg1 - z_);
  ui->openGLWidget->contr_ = contr_;
  ui->openGLWidget->update();
  z_ = arg1;
}

void Viewer::on_eu_x_valueChanged(double arg1) {
  contr_.RotX(arg1 - xr_);
  ui->openGLWidget->contr_ = contr_;
  ui->openGLWidget->update();
  xr_ = arg1;
}

void Viewer::on_eu_y_valueChanged(double arg1) {
  contr_.RotY(arg1 - yr_);
  ui->openGLWidget->contr_ = contr_;
  ui->openGLWidget->update();
  yr_ = arg1;
}

void Viewer::on_eu_z_valueChanged(double arg1) {
  contr_.RotZ(arg1 - zr_);
  ui->openGLWidget->contr_ = contr_;
  ui->openGLWidget->update();
  zr_ = arg1;
}

void Viewer::on_scale_full_valueChanged(double arg1) {
  ui->openGLWidget->sc = arg1 / 100;
  ui->openGLWidget->update();
}

void Viewer::on_scl_x_valueChanged(double arg1) {
  ui->openGLWidget->sc_x = arg1;
  ui->openGLWidget->update();
}

void Viewer::on_scl_y_valueChanged(double arg1) {
  ui->openGLWidget->sc_y = arg1;
  ui->openGLWidget->update();
}

void Viewer::on_scl_z_valueChanged(double arg1) {
  ui->openGLWidget->sc_z = arg1;
  ui->openGLWidget->update();
}

void Viewer::on_color_background_clicked() {
  QColor color_bgd = QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  if (color_bgd.isValid()) {
    ui->openGLWidget->red = color_bgd.redF();
    ui->openGLWidget->green = color_bgd.greenF();
    ui->openGLWidget->blue = color_bgd.blueF();
  }
  ui->openGLWidget->update();
}

void Viewer::on_color_edges_clicked() {
  QColor color_line = QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  if (color_line.isValid()) {
    ui->openGLWidget->lred = color_line.redF();
    ui->openGLWidget->lgreen = color_line.greenF();
    ui->openGLWidget->lblue = color_line.blueF();
  }
  ui->openGLWidget->update();
}

void Viewer::on_color_vertices_clicked() {
  QColor color_vrts = QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  if (color_vrts.isValid()) {
    ui->openGLWidget->pred = color_vrts.redF();
    ui->openGLWidget->pgreen = color_vrts.greenF();
    ui->openGLWidget->pblue = color_vrts.blueF();
  }
  ui->openGLWidget->update();
}

void Viewer::on_proj_parallel_toggled(bool checked) {
  ui->openGLWidget->proj = 0;
  ui->openGLWidget->update();
}

void Viewer::on_proj_central_toggled(bool checked) {
  ui->openGLWidget->proj = 1;
  ui->openGLWidget->update();
}

void Viewer::on_type_solid_toggled(bool checked) {
  ui->openGLWidget->stip = 0;
  ui->openGLWidget->update();
}

void Viewer::on_type_dashed_toggled(bool checked) {
  ui->openGLWidget->stip = 1;
  ui->openGLWidget->update();
}

void Viewer::on_display_method_currentIndexChanged(int index) {
  ui->openGLWidget->point = index;
  ui->openGLWidget->update();
}

void Viewer::on_thickness_valueChanged(int value) {
  ui->openGLWidget->line = value;
  ui->openGLWidget->update();
}

void Viewer::on_size_vertices_valueChanged(int value) {
  ui->openGLWidget->point_s = value;
  ui->openGLWidget->update();
}

void Viewer::on_actionBMP_triggered() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...", "name", "BMP (*.bmp);; JPEG (*.jpg *.jpeg)");
  ui->openGLWidget->grabFramebuffer().save(file);
}

void Viewer::on_actionGIF_triggered() {
  giffile_ =
      QFileDialog::getSaveFileName(this, "Save as...", "name", "GIF (*.gif)");
  gif_ = new QGifImage;
  frame_ = new QImage;
  timer_ = new QTimer(this);
  time_ = 0;
  connect(timer_, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
  timer_->start(100);
  ui->rec->setVisible(true);
}

void Viewer::saveGifFrame() {
  time_++;
  *frame_ = ui->openGLWidget->grabFramebuffer().scaled(640, 480);
  gif_->addFrame(*frame_);
  if (time_ == 50) {
    timer_->stop();
    ui->rec->setVisible(false);
    if (!giffile_.isNull()) gif_->save(giffile_);
  }
}

void Viewer::SaveSettings() {
  QSettings settings("/Users/Shared/settings.conf", QSettings::IniFormat);
  settings.beginGroup("Color_background");
  settings.setValue("red", ui->openGLWidget->red);
  settings.setValue("green", ui->openGLWidget->green);
  settings.setValue("blue", ui->openGLWidget->blue);
  settings.endGroup();
  settings.beginGroup("Color_edges");
  settings.setValue("red", ui->openGLWidget->lred);
  settings.setValue("green", ui->openGLWidget->lgreen);
  settings.setValue("blue", ui->openGLWidget->lblue);
  settings.endGroup();
  settings.beginGroup("Color_vertices");
  settings.setValue("red", ui->openGLWidget->pred);
  settings.setValue("green", ui->openGLWidget->pgreen);
  settings.setValue("blue", ui->openGLWidget->pblue);
  settings.endGroup();
  settings.beginGroup("Radio_Button");
  settings.setValue("projection_central", ui->openGLWidget->proj);
  settings.setValue("projection_parallel", ui->proj_parallel->isChecked());
  settings.setValue("type_line_solid", ui->type_solid->isChecked());
  settings.setValue("type_line_dashed", ui->type_dashed->isChecked());
  settings.setValue("proj", ui->openGLWidget->proj);
  settings.setValue("stip", ui->openGLWidget->stip);
  settings.endGroup();
  settings.beginGroup("Slider");
  settings.setValue("point", ui->openGLWidget->point);
  settings.setValue("thickness", ui->openGLWidget->line);
  settings.setValue("size_vertices", ui->openGLWidget->point_s);
  settings.endGroup();
}

void Viewer::LoadSettings() {
  QSettings settings("/Users/Shared/settings.conf", QSettings::IniFormat);
  settings.beginGroup("Color_background");
  ui->openGLWidget->red = settings.value("red", 0).toFloat();
  ui->openGLWidget->green = settings.value("green", 0).toFloat();
  ui->openGLWidget->blue = settings.value("blue", 0).toFloat();
  settings.endGroup();
  settings.beginGroup("Color_edges");
  ui->openGLWidget->lred = settings.value("red", 1).toFloat();
  ui->openGLWidget->lgreen = settings.value("green", 1).toFloat();
  ui->openGLWidget->lblue = settings.value("blue", 0).toFloat();
  settings.endGroup();
  settings.beginGroup("Color_vertices");
  ui->openGLWidget->pred = settings.value("red", 1).toFloat();
  ui->openGLWidget->pgreen = settings.value("green", 1).toFloat();
  ui->openGLWidget->pblue = settings.value("blue", 1).toFloat();
  settings.endGroup();
  settings.beginGroup("Radio_Button");
  ui->openGLWidget->proj = settings.value("proj", 0).toInt();
  ui->proj_central->setChecked(settings.value("projection_central").toBool());
  ui->proj_parallel->setChecked(
      settings.value("projection_parallel", true).toBool());
  ui->type_solid->setChecked(settings.value("type_line_solid", true).toBool());
  ui->type_dashed->setChecked(settings.value("type_line_dashed").toBool());
  ui->openGLWidget->stip = settings.value("stip", 0).toInt();
  settings.endGroup();
  settings.beginGroup("Slider");
  ui->display_method->setCurrentIndex(settings.value("point").toInt());
  ui->openGLWidget->point = settings.value("point").toInt();
  ui->thickness->setValue(settings.value("thickness").toInt());
  ui->openGLWidget->line = settings.value("thickness").toFloat();
  ui->size_vertices->setValue(settings.value("size_vertices").toInt());
  ui->openGLWidget->point_s = settings.value("size_vertices", 10).toFloat();
  settings.endGroup();
}

void Viewer::SetEnabled() {
  ui->pos_x->setEnabled(false);
  ui->pos_y->setEnabled(false);
  ui->pos_z->setEnabled(false);
  ui->eu_x->setEnabled(false);
  ui->eu_y->setEnabled(false);
  ui->eu_z->setEnabled(false);
  ui->scl_x->setEnabled(false);
  ui->scl_y->setEnabled(false);
  ui->scl_z->setEnabled(false);
  ui->scale_full->setEnabled(false);
}

void Viewer::SetTrueEnabled() {
  ui->pos_x->setValue(0);
  ui->pos_y->setValue(0);
  ui->pos_z->setValue(0);
  ui->eu_x->setValue(0);
  ui->eu_y->setValue(0);
  ui->eu_z->setValue(0);
  ui->scale_full->setValue(100);
  ui->scl_x->setValue(1.0);
  ui->scl_y->setValue(1.0);
  ui->scl_z->setValue(1.0);
  ui->pos_x->setEnabled(true);
  ui->pos_y->setEnabled(true);
  ui->pos_z->setEnabled(true);
  ui->eu_x->setEnabled(true);
  ui->eu_y->setEnabled(true);
  ui->eu_z->setEnabled(true);
  ui->scl_x->setEnabled(true);
  ui->scl_y->setEnabled(true);
  ui->scl_z->setEnabled(true);
  ui->scale_full->setEnabled(true);
  ui->scale->setVisible(true);
  ui->scale_full->setVisible(true);
}

void Viewer::SetQss() {
  setWindowTitle("Программа для визуализации Зафир");
  this->setStyleSheet(QSS::GetMain());
  ui->pwd->setStyleSheet(QSS::GetLineStyle());
  ui->settings->setStyleSheet(QSS::GetTabWidgetStyle());
  ui->display_method->setStyleSheet(QSS::GetComboBoxStyle());
  ui->rec->setStyleSheet("background-color:rgba(255,255,255,0);");
  ui->rec->setVisible(false);
  ui->scale->setVisible(false);
  ui->scale_full->setVisible(false);

  ui->open->setStyleSheet(QSS::GetButtonsStyle());
  ui->render->setStyleSheet(QSS::GetButtonsStyle());
  ui->color_background->setStyleSheet(QSS::GetButtonsStyle());
  ui->color_edges->setStyleSheet(QSS::GetButtonsStyle());
  ui->color_vertices->setStyleSheet(QSS::GetButtonsStyle());

  ui->pos_x->setStyleSheet(QSS::GetSpinBoxStyle());
  ui->pos_y->setStyleSheet(QSS::GetSpinBoxStyle());
  ui->pos_z->setStyleSheet(QSS::GetSpinBoxStyle());
  ui->eu_x->setStyleSheet(QSS::GetSpinBoxStyle());
  ui->eu_y->setStyleSheet(QSS::GetSpinBoxStyle());
  ui->eu_z->setStyleSheet(QSS::GetSpinBoxStyle());
  ui->scl_x->setStyleSheet(QSS::GetSpinBoxStyle());
  ui->scl_y->setStyleSheet(QSS::GetSpinBoxStyle());
  ui->scl_z->setStyleSheet(QSS::GetSpinBoxStyle());

  ui->position_text->setStyleSheet(QSS::GetLabelStyle());
  ui->euler_text->setStyleSheet(QSS::GetLabelStyle());
  ui->scale_text->setStyleSheet(QSS::GetLabelStyle());
  ui->display_method_text->setStyleSheet(QSS::GetLabelStyle());
  ui->size_vertices_text->setStyleSheet(QSS::GetLabelStyle());
  ui->projection_text->setStyleSheet(QSS::GetLabelStyle());
  ui->type_text->setStyleSheet(QSS::GetLabelStyle());
  ui->thickness_text->setStyleSheet(QSS::GetLabelStyle());

  ui->proj_central->setStyleSheet(QSS::GetRadioButtonStyle());
  ui->proj_parallel->setStyleSheet(QSS::GetRadioButtonStyle());
  ui->type_solid->setStyleSheet(QSS::GetRadioButtonStyle());
  ui->type_dashed->setStyleSheet(QSS::GetRadioButtonStyle());
  int id = QFontDatabase::addApplicationFont(":/resources/Cuprum-Regular.ttf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
}
