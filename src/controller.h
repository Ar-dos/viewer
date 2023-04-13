#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_
#include <string>

#include "model.h"
using namespace std;

namespace s21 {

class Controller {
 public:
  unsigned int count_of_vertexes_;
  unsigned int count_of_facets_;
  double *vertices_;
  unsigned int *indices_;

  Controller();
  Controller(char *filename);
  Controller(const Controller &other);
  Controller &operator=(const Controller &o);
  ~Controller();

  void XPos(double x);
  void YPos(double y);
  void ZPos(double z);

  void RotX(double s);
  void RotY(double s);
  void RotZ(double s);

 private:
  s21::Model md_;

  void Calloc();
  void Copy();
  void Delete();
};
}  // namespace s21

#endif  // SRC_CONTROLLER_H_
