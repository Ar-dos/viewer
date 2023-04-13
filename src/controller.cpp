#include "controller.h"
using namespace s21;

Controller::Controller()
    : count_of_vertexes_(0),
      count_of_facets_(0),
      vertices_(nullptr),
      indices_(nullptr) {}

Controller::Controller(char *filename) : Controller() {
  md_ = Model(filename);
  count_of_vertexes_ = md_.GetCountOfVertexes();
  count_of_facets_ = md_.GetCountOfFacets();
  Calloc();
  Copy();
}

Controller::Controller(const Controller &other) { operator=(other); }

Controller &Controller::operator=(const Controller &o) {
  Delete();
  md_ = o.md_;
  count_of_vertexes_ = o.count_of_vertexes_;
  count_of_facets_ = o.count_of_facets_;
  Calloc();
  Copy();
  return *this;
}

Controller::~Controller() { Delete(); }

void Controller::Delete() {
  delete[](indices_);
  delete[](vertices_);
}

void Controller::Calloc() {
  vertices_ = new double[count_of_vertexes_ * 3]{0};
  indices_ = new unsigned int[count_of_facets_]{0};
}

void Controller::Copy() {
  for (unsigned int i = 0; i < count_of_vertexes_ * 3; i++)
    vertices_[i] = md_.GetVertices()[i];

  for (unsigned int i = 0; i < count_of_facets_; i++)
    indices_[i] = md_.GetIndices()[i];
}

void Controller::XPos(double x) {
  md_.XPos(x);
  Copy();
}

void Controller::YPos(double y) {
  md_.YPos(y);
  Copy();
}

void Controller::ZPos(double z) {
  md_.ZPos(z);
  Copy();
}

void Controller::RotX(double s) {
  md_.RotX(s);
  Copy();
}

void Controller::RotY(double s) {
  md_.RotY(s);
  Copy();
}

void Controller::RotZ(double s) {
  md_.RotZ(s);
  Copy();
}
