#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../include/UI.h"
#include <array>
#include <vector>

class Rectangle {
public:
  Rectangle(float, float, float, float);
  ~Rectangle();

  void setPos(float, float);
  std::array<float, 2> getPos();

  void setSize(float, float);
  std::array<float, 2> getSize();

  void draw(UI &ui);

  void storeWalls();
  std::vector<std::array<float, 4>> getWalls();

private:
  float x, y, w, h;
  std::array<float, 2> pos;
  std::array<float, 2> size;
  std::vector<std::array<float, 4>> rect_walls;
};

#endif
