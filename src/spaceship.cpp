#include "../include/spaceship.h"

Spaceship::Spaceship(int height, int width,
                     int initial_y, int initial_x,
                     int max_y, int max_x,
                     int min_y, int min_x)
    : Matrix(height, width),
      DynamicEntity(initial_y, initial_x, max_y, max_x, min_y, min_x)
{

  this->speed = 3;
  const int values[height][width] = {
      {1, 0, 0, 0, 0, 0},
      {1, 1, 0, 0, 0, 0},
      {1, 0, 1, 0, 0, 0},
      {1, 0, 0, 1, 0, 0},
      {1, 0, 0, 0, 1, 0},
      {1, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 1, 0},
      {1, 0, 0, 1, 0, 0},
      {1, 0, 1, 0, 0, 0},
      {1, 1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0, 0}};

  // Copia os valores para a matriz alocada
  for (int i = 0; i < this->height; ++i)
  {
    for (int j = 0; j < this->width; ++j)
    {
      this->matrix[i][j] = values[i][j];
    }
  }
}

void Spaceship::moveUp()
{
  this->y -= speed;
  if (this->y < this->min_y)
  {
    this->y = this->min_y;
  }
}
void Spaceship::moveDown()
{

  this->y += speed;
  if (this->y > this->max_y)
  {
    this->y = this->max_y;
  }
}

void Spaceship::moveLeft()
{
}

void Spaceship::moveRight()
{
}

void Spaceship::setSpeed(int speed)
{
  this->speed = speed;
}

void Spaceship::multSpeed(int t)
{
  this->speed *= t;
}