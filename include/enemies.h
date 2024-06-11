#pragma once

#include "./matrix.h"
#include "./dinamycEntity.h"

class Enemies : public Matrix, public DynamicEntity
{
public:
  Enemies(int height, int width,
          int initial_y, int initial_x, int speed,
          int max_y, int max_x,
          int min_y, int min_x);

  void moveUp() override;
  void moveDown() override;
  void moveLeft() override;
  void moveRight() override;

  // static Enemies *createEnemies(int height, int width,
  //                               int initial_y, int initial_x,
  //                               int max_y, int max_x,
  //                               int min_y, int min_x);
};
