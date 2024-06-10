#include "../include/matrix.h"

Matrix::~Matrix()
{
  for (int i = 0; i < height; ++i)
  {
    delete[] this->matrix[i];
  }
  delete[] this->matrix;
}

Matrix::Matrix(int height, int width)
{

  int **matrix = new int *[height];
  for (int i = 0; i < height; ++i)
  {
    matrix[i] = new int[width];

    memset(matrix[i], 0, width * sizeof(int));
  }

  this->matrix = matrix;
  this->height = height;
  this->width = width;
}

Matrix *Matrix::createInverseMatrix()
{

  Matrix *inverse = new Matrix(this->height, this->width);

  for (int i = 0; i < this->height; ++i)
  {
    for (int j = 0; j < this->width; ++j)
    {
      inverse->matrix[i][j] = !this->matrix[i][j];
    }
  }

  return inverse;
}

void Matrix::populateMatrix(int value)
{
  for (int i = 0; i < this->height; ++i)
  {
    for (int j = 0; j < this->width; ++j)
    {
      this->setMatrixValue(i, j, value);
    }
  }
}

int Matrix::getWidth()
{
  return this->width;
}

int Matrix::getHeight()
{
  return this->height;
}

int **Matrix::getMatrix()
{
  return this->matrix;
}

void Matrix::setMatrixValue(int i, int j, int value)
{
  if (i < this->height && j < this->width)
  {

    this->matrix[i][j] = value;
  }
}

int Matrix::getMatrixValue(int i, int j)
{
  if (i < this->height && j < this->width)
  {
    return this->matrix[i][j];
  }
  return -1;
}