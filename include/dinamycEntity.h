#pragma once
#include "./entity.h"
class DynamicEntity : public Entity
{
protected:
  int speed;
  int min_y;
  int min_x;
  int max_y;
  int max_x;

public:
  DynamicEntity(int initial_y, int initial_x, int max_y, int max_x, int min_y, int min_x);
  virtual void moveUp() = 0;
  virtual void moveDown() = 0;
};