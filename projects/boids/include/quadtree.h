#ifndef QUADTREE_H
#define QUADTREE_H

#include "../include/UI.h"
#include "../include/boid.h"
#include "../include/glm/glm/glm.hpp"
#include "../include/glm/glm/vec2.hpp"
#include <array>
// #include <glm/glm.hpp>
// #include <glm/vec2.hpp>
#include <memory>
#include <vector>

struct Rectangle {
  int x;
  int y;
  int w;
  int h;
};

class QuadTree {
public:
  QuadTree(int, int, int, int);
  ~QuadTree();

  void subdivide();
  void insert(std::shared_ptr<Boid> &);
  std::vector<std::shared_ptr<Boid>> query(std::shared_ptr<Boid> &boid);

  bool contains(std::shared_ptr<Boid>);
  void clear();

  void draw(UI *);

public:
  std::array<std::shared_ptr<QuadTree>, 4> children;
  std::vector<std::shared_ptr<Boid>> boids;

private:
  // Layout
  // | 0 | 1 |
  // | 2 | 3 |
  Rectangle rect;
  bool isDivided = false;

  const int capacity = 3;

  float width;
  float height;
};

#endif
