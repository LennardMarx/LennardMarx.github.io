#ifndef BOID_H
#define BOID_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES

#include "../include/UI.h"
// #include <glm/glm.hpp>
#include "../include/glm/glm/glm.hpp"
#include "../include/glm/glm/gtx/rotate_vector.hpp"
#include "../include/glm/glm/gtx/vector_angle.hpp"
#include "../include/glm/glm/vec2.hpp"
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtx/rotate_vector.hpp>
// #include <glm/gtx/vector_angle.hpp>
// #include <glm/mat4x4.hpp>
// #include <glm/vec2.hpp>
// #include <glm/vec3.hpp>
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>

struct Boid;

struct Flock {
  std::vector<std::shared_ptr<Boid>> mates;
  glm::vec2 vel;
  glm::vec2 center;
};

class Boid {

public:
  Boid(glm::vec2, glm::vec2);
  ~Boid();

  void getBoidsInVision(std::vector<std::shared_ptr<Boid>> &);
  glm::vec2 separate();
  glm::vec2 align();
  glm::vec2 fightForPosition();

  glm::vec2 limitForce(glm::vec2);

  glm::vec2 avoidBorder(UI *);
  void wrapAround(UI *);

  glm::vec2 avoidMouse(glm::vec2);
  glm::vec2 chaseMouse(glm::vec2);

  void fly();
  void draw(UI *);
  void drawRange(UI *);
  void drawRed(UI *);
  // void drawTexture(UI *, TexturedRectangle *);
  void drawTexture(UI *, std::unique_ptr<TexturedRectangle> &);
  void drawAnimation(UI *, std::unique_ptr<AnimatedSprite> &);

public:
  glm::vec2 pos;
  glm::vec2 vel;
  glm::vec2 acc = glm::vec2(0, 0);
  float vision = 50.0f;
  std::shared_ptr<Flock> flock; // NOTE: might decrease performance?

private:
  float maxVel = 3.0f;
  float maxForce = 0.2f;

  float length = 20.0f;
  float width = 16.0f;

  int framesInAnimation = 12;
  int frame = rand() % (framesInAnimation);
  unsigned int frameCount = 0;
};

#endif
