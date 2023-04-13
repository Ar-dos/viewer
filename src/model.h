#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_
#include <cmath>
#include <iostream>

namespace s21 {

class Model {
 public:
  Model();
  Model(char *filename);
  Model(const Model &other);
  Model &operator=(const Model &o);
  ~Model();

  unsigned int GetCountOfVertexes();
  unsigned int GetCountOfFacets();
  double *GetVertices();
  unsigned int *GetIndices();

  void XPos(double x);
  void YPos(double y);
  void ZPos(double z);

  void RotX(double s);
  void RotY(double s);
  void RotZ(double s);

 private:
  unsigned int count_of_vertexes_;
  unsigned int count_of_facets_;
  double *vertices_;
  unsigned int *indices_;

  void FirstOpen(char *filename);
  void SecondOpen(char *filename);

  unsigned int CountDataInLine(char *line_buf);
  void DoTheCounting(char *line_buf);
  char *SkipNonDigit(char *line_buf);
  void InputIndex(unsigned int res, unsigned int *j);

  void SaveVertices(char *line_buf, unsigned int *i);
  void SaveFacets(char *line_buf, unsigned int *j);

  void Delete();
};
}  // namespace s21

#endif  // SRC_MODEL_H_
