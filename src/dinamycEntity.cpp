#include "../include/dinamycEntity.h"

DynamicEntity::DynamicEntity(int initial_y, int initial_x, int max_y, int max_x, int min_y, int min_x) : Entity(initial_y, initial_x)
{
  this->min_y = min_y;
  this->min_x = min_x;
  this->max_y = max_y;
  this->max_x = max_x;
}

void DynamicEntity::increaseSpeed()
{
  this->speed++;
}