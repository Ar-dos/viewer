#include "model.h"

#include <fstream>

namespace s21 {

Model::Model()
    : count_of_vertexes_(0),
      count_of_facets_(0),
      vertices_(nullptr),
      indices_(nullptr) {}

Model::Model(char *filename) : Model() {
  if (filename != nullptr) {
    FirstOpen(filename);
    SecondOpen(filename);
  }
}

Model::Model(const Model &other) { operator=(other); }

Model &Model::operator=(const Model &o) {
  Delete();
  count_of_vertexes_ = o.count_of_vertexes_;
  count_of_facets_ = o.count_of_facets_;
  vertices_ = new double[count_of_vertexes_ * 3]{0};
  indices_ = new unsigned int[count_of_facets_]{0};
  for (unsigned int i = 0; i < count_of_vertexes_ * 3; i++)
    vertices_[i] = o.vertices_[i];
  for (unsigned int i = 0; i < count_of_facets_; i++)
    indices_[i] = o.indices_[i];
  return *this;
}

Model::~Model() { Delete(); }

unsigned int Model::CountDataInLine(char *line_buf) {
  unsigned int res = 0;
  for (int i = 1; line_buf[i] != '\0'; i++) {
    if ((line_buf[i] == ' ' && line_buf[i + 1] != ' ') &&
        (line_buf[i] == ' ' && line_buf[i + 1] != '\n') &&
        (line_buf[i] == ' ' && line_buf[i + 1] != '\0'))
      res++;
  }
  return res;
}

void Model::DoTheCounting(char *line_buf) {
  if (line_buf[0] == 'v' && line_buf[1] == ' ') count_of_vertexes_++;
  unsigned int line = 0;
  if (line_buf[0] == 'f' && line_buf[1] == ' ')
    line = CountDataInLine(line_buf);
  count_of_facets_ += line * 2;
}

void Model::SaveVertices(char *line_buf, unsigned int *i) {
  while (*line_buf != '\0') {
    if ((*(line_buf) <= '9' && *(line_buf) >= '0') || *(line_buf) == '-') {
      vertices_[*i] = strtod(line_buf, &line_buf);
      (*i)++;
    } else {
      line_buf++;
    }
  }
}

char *Model::SkipNonDigit(char *line_buf) {
  while (!(*(line_buf) <= '9' && *(line_buf) > '0')) line_buf++;
  return line_buf;
}

void Model::InputIndex(unsigned int res, unsigned int *j) {
  indices_[*j] = res;
  (*j)++;
}

void Model::SaveFacets(char *line_buf, unsigned int *j) {
  unsigned int count = CountDataInLine(line_buf);

  line_buf = SkipNonDigit(line_buf);

  unsigned int start = (unsigned int)strtod(line_buf, &line_buf) - 1;
  InputIndex(start, j);
  count--;
  while (count > 0) {
    if (*line_buf == '/')
      while (*line_buf != ' ') line_buf++;
    line_buf = SkipNonDigit(line_buf);
    unsigned int res = (unsigned int)strtod(line_buf, &line_buf) - 1;
    InputIndex(res, j);
    InputIndex(res, j);
    count--;
  }
  InputIndex(start, j);
}

void Model::Delete() {
  delete[](indices_);
  delete[](vertices_);
}

unsigned int Model::GetCountOfVertexes() { return count_of_vertexes_; }

unsigned int Model::GetCountOfFacets() { return count_of_facets_; }

double *Model::GetVertices() { return vertices_; }

unsigned int *Model::GetIndices() { return indices_; }

void Model::FirstOpen(char *filename) {
  std::ifstream file(filename);
  std::string str;

  while (std::getline(file, str)) {
    char *line_buf = const_cast<char *>(str.c_str());
    DoTheCounting(line_buf);
  }
}

void Model::SecondOpen(char *filename) {
  std::ifstream file(filename);
  vertices_ = new double[count_of_vertexes_ * 3]{0};
  indices_ = new unsigned int[count_of_facets_]{0};
  std::string str;
  unsigned int i = 0, j = 0;

  while (std::getline(file, str)) {
    char *line_buf = const_cast<char *>(str.c_str());
    if (line_buf[0] == 'v' && line_buf[1] == ' ') SaveVertices(line_buf, &i);

    if (line_buf[0] == 'f' && line_buf[1] == ' ') SaveFacets(line_buf, &j);
  }
}

void Model::XPos(double x) {
  for (unsigned int i = 0; i < count_of_vertexes_ * 3; i += 3)
    vertices_[i] += x;
}

void Model::YPos(double y) {
  for (unsigned int i = 1; i < count_of_vertexes_ * 3; i += 3)
    vertices_[i] += y;
}

void Model::ZPos(double z) {
  for (unsigned int i = 2; i < count_of_vertexes_ * 3; i += 3)
    vertices_[i] += z;
}

void Model::RotX(double s) {
  for (unsigned int i = 0; i < count_of_vertexes_ * 3; i++) {
    i++;
    double temp = vertices_[i];
    vertices_[i] = vertices_[i] * cos(s) + vertices_[i + 1] * sin(s);
    i++;
    vertices_[i] = -(temp)*sin(s) + vertices_[i] * cos(s);
  }
}

void Model::RotY(double s) {
  for (unsigned int i = 0; i < count_of_vertexes_ * 3; i++) {
    double temp = vertices_[i];
    vertices_[i] = vertices_[i] * cos(s) + vertices_[i + 2] * sin(s);
    i += 2;
    vertices_[i] = -(temp)*sin(s) + vertices_[i] * cos(s);
  }
}

void Model::RotZ(double s) {
  for (unsigned int i = 0; i < count_of_vertexes_ * 3; i += 2) {
    double temp = vertices_[i];
    vertices_[i] = vertices_[i] * cos(s) - vertices_[i + 1] * sin(s);
    i++;
    vertices_[i] = temp * sin(s) + vertices_[i] * cos(s);
  }
}
}  // namespace s21
