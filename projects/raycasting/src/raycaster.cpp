#include <SDL2/SDL.h>
#include <cmath>
// #include <utility>
#include <array>
#include <vector>

#include "../include/raycaster.h"
// #include <iostream>

RayCaster::~RayCaster() {}

std::vector<float> RayCaster::getDistances() { return distances; }
std::vector<Coordinate> RayCaster::getIntersections() {
  return intersection_buffer;
}
std::vector<int> RayCaster::getPositionOnWall() { return position_on_wall; }
std::vector<std::array<float, 4>> RayCaster::getRays() { return rays; }
std::vector<SDL_Texture *> RayCaster::getTextureInfo() { return texture_info; }
// WallInfo RayCaster::getWallInfo() { return wallInfo; }

Coordinate RayCaster::calcIntersection() {
  intersection.x = x3 + u * (x4 - x3);
  intersection.y = y3 + u * (y4 - y3);
  return intersection;
}
Coordinate RayCaster::getClosestIntersection() {
  closestDistance = 1000000;
  for (int i = 0; i < intersections.size(); i++) {
    distance = sqrt(pow(intersections[i].y - position.y, 2) +
                    pow(intersections[i].x - position.x, 2));
    if (distance < closestDistance) {
      closestDistance = distance;
      closestIntersection = intersections[i];
      wall_horizontal = wall_horizontal_vec[i];
      texture = texture_buffer[i];
    }
  }
  whatDoISee();
  return closestIntersection;
}

void RayCaster::whatDoISee() {
  // should be passed somehow
  const int WORLD_OFFSET_W = 400;
  const int WORLD_OFFSET_H = 400;
  const int WALL_SIZE = 50;

  // intersection in world coordinates
  intersection_buffer.push_back(closestIntersection);
  // texture of hit wall
  texture_info.push_back(texture);
  // point on individual wall, where it was hit (for texture mapping)
  if (wall_horizontal) {
    position_on_wall.push_back(((int)closestIntersection.x + WORLD_OFFSET_W) %
                               WALL_SIZE);
  } else {
    position_on_wall.push_back(((int)closestIntersection.y + WORLD_OFFSET_H) %
                               WALL_SIZE);
  }
}

void RayCaster::forgetWhatISaw() {
  while (!wall_horizontal_vec.empty()) {
    wall_horizontal_vec.pop_back();
  }
  while (!texture_buffer.empty()) {
    texture_buffer.pop_back();
  }
  while (!intersections.empty()) {
    intersections.pop_back();
  }
  closestIntersection = {0, 0};
}

void RayCaster::calcIntersections(std::vector<Wall *> &_walls) {
  for (int i = 0; i < _walls.size(); i++) {
    x3 = x;
    y3 = y;
    x4 = c1;
    y4 = c2;
    x1 = _walls[i]->getPos()[0];
    y1 = _walls[i]->getPos()[1];
    x2 = _walls[i]->getPos()[2];
    y2 = _walls[i]->getPos()[3];

    denom = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    if (denom == 0) {
      continue;
    }
    t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
    u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / denom;
    if (0 < t && t < 1 && u > 0 && u < 1) {
      intersection = calcIntersection();
      intersections.push_back(intersection);
      if (x2 - x1 == 0)
        wall_horizontal_vec.push_back(false);
      else if (y2 - y1 == 0)
        wall_horizontal_vec.push_back(true);
      texture_buffer.push_back(_walls[i]->getTexture());
      // std::cout << texture_buffer[0] << std::endl;
    }
  }
}

void RayCaster::emitLight(std::vector<Wall *> &_walls) {
  distances.clear();
  intersection_buffer.clear();
  position_on_wall.clear();
  texture_info.clear();
  rays.clear();

  int min = (orientation - (float)fov / 2);
  int max = (orientation + (float)fov / 2);

  for (int i = min; i < max; i++) {
    x = position.x;
    y = position.y;
    for (int j = 0; j < 20;
         j++) // NOTE: max iteration = SCREEN_W / FOV -> results in tile width
              // of exactly 1 pixel -> max resolution!!
    {
      ang = (i + (float)j / 20) * pi / 180;
      // coords outside of screen (needed for calculation of intersection!)
      c1 = x + 10000 * cos(ang);
      c2 = y + 10000 * sin(ang);

      calcIntersections(_walls);
      closestIntersection = getClosestIntersection();
      if (!intersections.empty()) {
        rays.push_back({x, y, closestIntersection.x, closestIntersection.y});
      }

      float orient_ang = orientation * pi / 180;
      float perp_dist = calcPerpDist(
          closestIntersection.x, closestIntersection.y, x, y,
          x + 50 * cos(orient_ang + pi / 2), y + 50 * sin(orient_ang + pi / 2));
      distances.push_back(perp_dist);

      forgetWhatISaw();
    }
  }
}

void RayCaster::lineAsFunction(float x1, float y1, float x2, float y2, float &a,
                               float &b, float &c) {
  a = y1 - y2;
  b = x2 - x1;
  c = x1 * y2 - x2 * y1;
}

float RayCaster::calcPerpDist(float pX, float pY, float lineX1, float lineY1,
                              float lineX2, float lineY2) {
  float a, b, c;
  lineAsFunction(lineX1, lineY1, lineX2, lineY2, a, b, c);
  return abs(a * pX + b * pY + c) / sqrt(a * a + b * b);
}
