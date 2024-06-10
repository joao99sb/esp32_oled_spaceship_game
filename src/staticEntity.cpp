#include "../include/staticEntity.h"

StaticEntity::StaticEntity(int height, int width,
                           int initial_y, int initial_x) : Entity(initial_y, initial_x), Matrix(height, width) {}
