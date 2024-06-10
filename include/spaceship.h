#pragma once
#include "./matrix.h"
#include "./dinamycEntity.h"

class Spaceship : public Matrix, public DynamicEntity
{
public:
  Spaceship(int height, int width,
            int initial_y, int initial_x,
            int max_y, int max_x,
            int min_y, int min_x);
  void moveUp() override;
  void moveDown() override;
  void laserUp();


};