#pragma once
#include <Wire.h>

class Matrix
{
protected:
  int **matrix;
  int height;
  int width;

public:
  Matrix(int height, int width);
  ~Matrix();
  Matrix *createInverseMatrix();
  void populateMatrix(int value);
  int **getMatrix();
  int getHeight();
  int getWidth();
  void setMatrixValue(int i, int j, int value);
  int getMatrixValue(int i, int j);
};
