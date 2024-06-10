#include "../include/enemies.h"

Enemies::Enemies(int height, int width,
                 int initial_y, int initial_x,
                 int max_y, int max_x,
                 int min_y, int min_x)
    : Matrix(height, width),
      DynamicEntity(initial_y, initial_x, max_y, max_x, min_y, min_x)
{
  this->speed = 3;
  const int values[height][height] = {
      {0, 0, 0, 1, 0, 0, 0},
      {0, 0, 1, 0, 1, 0, 0},
      {0, 1, 0, 0, 0, 1, 0},
      {1, 0, 0, 0, 0, 0, 1},
      {0, 1, 0, 0, 0, 1, 0},
      {0, 0, 1, 0, 1, 0, 0},
      {0, 0, 0, 1, 0, 0, 0},
      {0, 0, 1, 0, 1, 0, 0},
      {0, 1, 0, 0, 0, 1, 0},
      {1, 1, 1, 1, 1, 1, 1}};

  // Copia os valores para a matriz alocada
  for (int i = 0; i < this->height; ++i)
  {
    for (int j = 0; j < this->width; ++j)
    {
      this->matrix[i][j] = values[i][j];
    }
  }
}

void Enemies::moveUp()
{
  this->y -= speed;
  if (this->y < this->min_y)
  {
    this->y = this->min_y;
  }
}
void Enemies::moveDown()
{
  this->y += speed;
  if (this->y > this->max_y)
  {
    this->y = this->max_y;
  }
}

void Enemies::moveLeft()
{
  this->x -= speed;
  if (this->x < this->min_x)
  {
    this->x = this->min_x;
  }
}

void Enemies::moveRight()
{
  this->x += speed;
  if (this->x > this->max_x)
  {
    this->x = this->max_x;
  }
}

