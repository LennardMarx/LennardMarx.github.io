#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <cstdint>
#include <vector>

#define PI 3.14159265358979323846

struct Coordinate {
  float x;
  float y;

  Coordinate operator+(Coordinate &p) {
    return (Coordinate){this->x - p.x, this->y - p.y};
  }
  Coordinate operator-(Coordinate &p) {
    return (Coordinate){this->x - p.x, this->y - p.y};
  }
  Coordinate operator+=(Coordinate &p) {
    this->x += p.x;
    this->y += p.y;
    return *this;
  }
};

enum class Movement {
  None = 1 << 0,
  Forward = 1 << 1,
  Backward = 1 << 2,
  Left = 1 << 3,
  Right = 1 << 4
};

inline Movement operator|(Movement a, Movement b) {
  return static_cast<Movement>(static_cast<int>(a) | static_cast<int>(b));
}

struct MovementFlag {
  uint8_t flagValue = 0;

  void set(Movement flag) { flagValue |= (int)flag; }

  void unset(Movement flag) { flagValue &= ~(int)flag; }

  bool has(Movement flag) { return (flagValue & (int)flag) == (int)flag; }

  bool any(Movement multiFlag) { return (flagValue & (int)multiFlag) != 0; }
};

#endif
