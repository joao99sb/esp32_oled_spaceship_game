#include "../include/entity.h"

Entity::Entity(int initial_y, int initial_x)
{

  this->y = initial_y;
  this->x = initial_x;
}

int Entity::getCurrentY()
{
  return this->y;
}

int Entity::getCurrentX()
{
  return this->x;
}

void Entity::setCurrentY(int y)
{
  this->y = y;
}

void Entity::setCurrentX(int x)
{
  this->x = x;
}