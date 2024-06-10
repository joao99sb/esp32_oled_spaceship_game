#include "../include/buffer.h"

Buffer::Buffer(int height, int width) : Matrix(height, width)
{
}

void Buffer::drawImageFromMatrix(Matrix *image, int yOffset, int xOffset)
{
  for (int i = 0; i < image->getHeight(); i++)
  {
    for (int j = 0; j < image->getWidth(); j++)
    {
      if ((j + xOffset >= 0 && j + xOffset < this->width) &&
          (i + yOffset >= 0 && i + yOffset < this->height))
      {
        if (image->getMatrixValue(i, j) == 1)
        {
          this->setMatrixValue(i + yOffset, j + xOffset, 1);
        }
      }
    }
  }
}

void Buffer::resetBuffer()
{
  this->populateMatrix(0);
}