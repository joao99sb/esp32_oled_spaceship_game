#pragma once

#include "./matrix.h"
class Buffer : public Matrix
{
private:
public:
  Buffer(int height, int width);
  void resetBuffer();
  void drawImageFromMatrix(Matrix *image, int y, int x);
};
