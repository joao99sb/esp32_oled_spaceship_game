#pragma once
#include "./entity.h"
#include "./matrix.h"

class StaticEntity : public Entity, public Matrix
{
private:
  /* data */
public:
  StaticEntity(int height, int width, int initial_y, int initial_x);
};
