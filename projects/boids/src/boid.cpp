#include "../include/boid.h"
// #include <glm/ext/matrix_float4x4.hpp>

Boid::Boid(glm::vec2 pos, glm::vec2 vel) : pos(pos), vel(vel) {
  // Memory allocation for local flock.
  flock = std::make_shared<Flock>();
}
Boid::~Boid() {}

// Get local flock and information about it.
// -> maybe separate, but would add additional loop.
void Boid::getBoidsInVision(std::vector<std::shared_ptr<Boid>> &boids) {
  // Reset values.
  flock->mates.clear();
  flock->center = glm::vec2(0, 0);
  flock->vel = glm::vec2(0, 0);

  // Get flock mates and info.
  for (int j = 0; j < boids.size(); j++) {
    if (boids[j].get() == this) {
      continue;
    }
    if (glm::length(boids[j]->pos - pos) < vision) {
      flock->mates.push_back(boids[j]);
      flock->center += boids[j]->pos;
      flock->vel += boids[j]->vel;
    }
  }

  // Average collected info over local flock size.
  if (flock->mates.size() != 0) {
    flock->center /= flock->mates.size();
    flock->vel /= flock->mates.size();
  } else {
    flock->center = this->pos;
    flock->vel = this->vel;
  }
}

// Seperate from boids in local flock.
glm::vec2 Boid::separate() {
  glm::vec2 weightedDistance = glm::vec2(0, 0);
  // glm::vec2 weightedDistance = this->vel;
  if (flock->mates.size() != 0) {
    for (std::shared_ptr<Boid> boid : flock->mates) {
      if (glm::length(pos - boid->pos) != 0) {
        weightedDistance +=
            (pos - boid->pos) / glm::length(pos - boid->pos); // * vision;
      }
    }
    weightedDistance /= flock->mates.size();
  } else {
    weightedDistance = this->vel;
  }

  weightedDistance = glm::normalize(weightedDistance) * 7.0f;
  glm::vec2 force = weightedDistance - vel;
  return limitForce(force);
}

// NOTE: Play around with (max) velocities to find good rules.

// Aligning with local flock.
glm::vec2 Boid::align() {
  flock->vel = glm::normalize(flock->vel) * maxVel;
  glm::vec2 force = flock->vel - vel;

  return limitForce(force);
}

// Steering towards center of local flock.
glm::vec2 Boid::fightForPosition() {
  glm::vec2 desiredVel;
  if (flock->center != pos) {
    desiredVel = flock->center - pos;
  } else {
    desiredVel = vel;
  }
  // desiredVel = glm::normalize(desiredVel) * maxVel;
  glm::vec2 force = desiredVel - vel;

  return limitForce(force);
}

// Limiting the steering force to have boids fly smooth curves.
glm::vec2 Boid::limitForce(glm::vec2 force) {
  if (glm::length(force) > maxForce) {
    force = glm::normalize(force) * maxForce;
  }
  return force;
}

// Generating force away from UI borders.
glm::vec2 Boid::avoidBorder(UI *ui) {
  if (pos[0] < 50.0f) {
    glm::vec2 desiredVel = glm::vec2(1.0f, 0.0f);
    desiredVel = glm::normalize(desiredVel) * maxVel;
    glm::vec2 force = desiredVel - vel;
    return limitForce(force);
  } else if (pos[0] > ui->sizeX - 50.0f) {
    glm::vec2 desiredVel = glm::vec2(-1.0f, 0.0f);
    desiredVel = glm::normalize(desiredVel) * maxVel;
    glm::vec2 force = desiredVel - vel;
    return limitForce(force);
  } else if (pos[1] < 50.0f) {
    glm::vec2 desiredVel = glm::vec2(0.0f, 1.0f);
    desiredVel = glm::normalize(desiredVel) * maxVel;
    glm::vec2 force = desiredVel - vel;
    return limitForce(force);
  } else if (pos[1] > ui->sizeY - 50.0f) {
    glm::vec2 desiredVel = glm::vec2(0.0f, -1.0f);
    desiredVel = glm::normalize(desiredVel) * maxVel;
    glm::vec2 force = desiredVel - vel;
    return limitForce(force);
  } else
    return glm::vec2(0, 0);
}

void Boid::wrapAround(UI *ui) {
  if (pos[0] <= 0.0f) {
    pos[0] = ui->sizeX;
  } else if (pos[0] >= ui->sizeX) {
    pos[0] = 0.0f;
  } else if (pos[1] <= 0.0f) {
    pos[1] = ui->sizeY;
  } else if (pos[1] >= ui->sizeY) {
    pos[1] = 0.0f;
  }
}

// Generating force to move away from mouse.
glm::vec2 Boid::avoidMouse(glm::vec2 mouse) {
  glm::vec2 desiredVel;
  if (mouse != pos && glm::length(pos - mouse) < 200.0f) {
    desiredVel = pos - mouse;
  } else {
    desiredVel = vel;
  }
  desiredVel = glm::normalize(desiredVel) * maxVel;
  glm::vec2 force = desiredVel - vel;
  return limitForce(force);
}

// Generating force to move towards mouse.
glm::vec2 Boid::chaseMouse(glm::vec2 mouse) {
  glm::vec2 desiredVel;
  if (mouse != pos && glm::length(pos - mouse) < 100.0f) {
    desiredVel = mouse - pos;
  } else {
    desiredVel = vel;
  }
  desiredVel = glm::normalize(desiredVel) * maxVel;
  glm::vec2 force = desiredVel - vel;
  return limitForce(force);
}

// Updating position and velocity.
void Boid::fly() {
  if (glm::length(vel) > maxVel) {
    vel = glm::normalize(vel) * maxVel;
  }
  pos += vel;
  vel += acc;

  // Resetting acceleration for next iteration.
  acc *= 0.0f;
}

void Boid::draw(UI *ui) {
  glm::vec2 dir = glm::normalize(vel);
  ui->drawLine(pos[0], pos[1], pos[0] + dir[0] * length,
               pos[1] + dir[1] * length);
  ui->drawLine(pos[0] + dir[1] * width / 2, pos[1] - dir[0] * width / 2,
               pos[0] - dir[1] * width / 2, pos[1] + dir[0] * width / 2);
  ui->drawLine(pos[0] + dir[1] * width / 2, pos[1] - dir[0] * width / 2,
               pos[0] + dir[0] * length, pos[1] + dir[1] * length);
  ui->drawLine(pos[0] - dir[1] * width / 2, pos[1] + dir[0] * width / 2,
               pos[0] + dir[0] * length, pos[1] + dir[1] * length);
}

void Boid::drawRange(UI *ui) {
  ui->setDrawColor(200, 100, 100, 255);
  ui->drawLine(pos.x - vision, pos.y, pos.x + vision, pos.y);
  ui->drawLine(pos.x, pos.y - vision, pos.x, pos.y + vision);
}

void Boid::drawRed(UI *ui) {
  glm::vec2 dir = glm::normalize(vel);
  ui->drawLine(pos[0], pos[1], pos[0] + dir[0] * length,
               pos[1] + dir[1] * length);
  ui->drawLine(pos[0] + dir[1] * width / 2, pos[1] - dir[0] * width / 2,
               pos[0] - dir[1] * width / 2, pos[1] + dir[0] * width / 2);
  ui->drawLine(pos[0] + dir[1] * width / 2, pos[1] - dir[0] * width / 2,
               pos[0] + dir[0] * length, pos[1] + dir[1] * length);
  ui->drawLine(pos[0] - dir[1] * width / 2, pos[1] + dir[0] * width / 2,
               pos[0] + dir[0] * length, pos[1] + dir[1] * length);
}

void Boid::drawTexture(UI *ui, std::unique_ptr<TexturedRectangle> &tex) {
  tex->Draw(pos[0] - 25.0f, pos[1] - 15.0f, 50.0f, 30.0f);
  float angle = glm::degrees(std::atan2(vel[0], vel[1]));
  tex->Render(ui->getRenderer(), -angle + 180.0f);
}

void Boid::drawAnimation(UI *ui, std::unique_ptr<AnimatedSprite> &tex) {

  // tex->Draw(pos[0] - 30.0f, pos[1] - 15.0f, 60.0f, 30.0f);
  tex->Draw(pos[0] - 20.0f, pos[1] - 10.0f, 40.0f, 20.0f);
  tex->PlayFrame(0, 0, 130, 65,
                 frame); // frame width and heigt and vertical position
  float angle = glm::degrees(std::atan2(vel[0], vel[1]));
  tex->Render(ui->getRenderer(), -angle + 180.0f);

  // Continue animation every X frame.
  int frameDelay = 4;
  frameCount++;
  if (frameCount % frameDelay == 0) {
    frame++;
    if (frame > framesInAnimation - 1) {
      frame = 0;
    }
  }
}

// void Boid::getBoidsInVision(std::vector<std::shared_ptr<Boid>> &boids) {
//   mates.clear();
//   flockVel = glm::vec2(0, 0);
//   flockCenter = glm::vec2(0, 0);
//
//   for (int j = 0; j < boids.size(); j++) {
//     if (boids[j].get() == this) {
//       continue;
//     }
//     if (glm::length(boids[j]->pos - pos) < vision) {
//       mates.push_back(boids[j]);
//
//       flockVel += boids[j]->vel;
//       flockCenter += boids[j]->pos;
//     }
//   }
//   if (mates.size() != 0) {
//     flockCenter /= mates.size();
//     flockVel /= mates.size();
//   } else {
//     flockCenter = this->pos;
//     flockVel = this->vel;
//   }
// }
