#pragma once

// #include "./matrix.h"

class Entity
{
protected:

  int y;
  int x;

public:
  Entity(int initial_y, int initial_x);
  void setCurrentY(int y);
  void setCurrentX(int x);
  int getCurrentY();
  int getCurrentX();
};