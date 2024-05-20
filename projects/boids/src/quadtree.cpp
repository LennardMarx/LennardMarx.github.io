#include "../include/quadtree.h"

QuadTree::QuadTree(int x, int y, int w, int h) {
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
}
QuadTree::~QuadTree() {}

void QuadTree::draw(UI *ui) {
  // SDL_SetRenderDrawColor(ui->getRenderer(), 69, 133, 136, 255); // gruv-blue
  SDL_SetRenderDrawColor(ui->getRenderer(), 249, 245, 215, 50); // grub-light
  ui->drawLine(rect.x - rect.w / 2, rect.y - rect.h / 2, rect.x + rect.w / 2,
               rect.y - rect.h / 2);
  ui->drawLine(rect.x - rect.w / 2, rect.y - rect.h / 2, rect.x - rect.w / 2,
               rect.y + rect.h / 2);
  ui->drawLine(rect.x + rect.w / 2, rect.y - rect.h / 2, rect.x + rect.w / 2,
               rect.y + rect.h / 2);
  ui->drawLine(rect.x - rect.w / 2, rect.y + rect.h / 2, rect.x + rect.w / 2,
               rect.y + rect.h / 2);
  if (children[0] != nullptr) {
    for (std::shared_ptr<QuadTree> child : children) {
      child->draw(ui);
    }
  }
}

std::vector<std::shared_ptr<Boid>>
QuadTree::query(std::shared_ptr<Boid> &boid) {
  std::vector<std::shared_ptr<Boid>> found;
  // check intersection
  glm::vec2 pos = boid->pos;
  float rad = boid->vision;
  int left = rect.x - rect.w / 2;
  int right = rect.x + rect.w / 2;
  int up = rect.y - rect.h / 2;
  int down = rect.y + rect.h / 2;
  // TODO: update to circle, not rectangle!!
  if (pos.x - rad > right || pos.x + rad < left || pos.y - rad > down ||
      pos.y + rad < up) {
    // if (pos.x - rad > left || pos.x + rad < right || pos.y - rad > up ||
    //     pos.y + rad < down) {
    return found;
  } else {
    for (std::shared_ptr<Boid> bird : boids) {
      if (contains(bird)) {
        found.push_back(bird);
      }
    }
    if (isDivided) {
      std::vector<std::shared_ptr<Boid>> found0 = children[0]->query(boid);
      found.insert(found.end(), found0.begin(), found0.end());
      std::vector<std::shared_ptr<Boid>> found1 = children[1]->query(boid);
      found.insert(found.end(), found1.begin(), found1.end());
      std::vector<std::shared_ptr<Boid>> found2 = children[2]->query(boid);
      found.insert(found.end(), found2.begin(), found2.end());
      std::vector<std::shared_ptr<Boid>> found3 = children[3]->query(boid);
      found.insert(found.end(), found3.begin(), found3.end());
    }
    return found;
  }
}

bool QuadTree::contains(std::shared_ptr<Boid> boid) {
  int left = rect.x - rect.w / 2;
  int right = rect.x + rect.w / 2;
  int up = rect.y - rect.h / 2;
  int down = rect.y + rect.h / 2;

  if (boid->pos[0] >= left && boid->pos[0] < right && boid->pos[1] >= up &&
      boid->pos[1] < down) {
    return true;
  } else {
    return false;
  }
}

void QuadTree::insert(std::shared_ptr<Boid> &boid) {
  if (!contains(boid)) {
    return;
  }
  if (boids.size() < capacity) {
    boids.push_back(boid);
    // return;
  } else {
    if (!isDivided) {
      subdivide();
    }
    // boids.pop_back();
    children[0]->insert(boid);
    children[1]->insert(boid);
    children[2]->insert(boid);
    children[3]->insert(boid);
  }
}

void QuadTree::clear() {
  boids.clear();
  isDivided = false;
  if (children[0] != nullptr) {
    for (std::shared_ptr<QuadTree> child : children) {
      child->clear();
    }
  }
}

void QuadTree::subdivide() {
  children[0] = std::make_shared<QuadTree>(
      rect.x - rect.w / 4, rect.y - rect.h / 4, rect.w / 2, rect.h / 2);
  children[1] = std::make_shared<QuadTree>(
      rect.x + rect.w / 4, rect.y - rect.h / 4, rect.w / 2, rect.h / 2);
  children[2] = std::make_shared<QuadTree>(
      rect.x - rect.w / 4, rect.y + rect.h / 4, rect.w / 2, rect.h / 2);
  children[3] = std::make_shared<QuadTree>(
      rect.x + rect.w / 4, rect.y + rect.h / 4, rect.w / 2, rect.h / 2);
  isDivided = true;
}
