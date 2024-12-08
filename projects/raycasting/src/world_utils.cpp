#include "../include/world_utils.h"

std::vector<Wall *>
WorldUtils::createWorld2(std::array<std::array<std::string, 16>, 16> worldMap,
                         const int world_w, const int world_h,
                         const int wall_size, SDL_Renderer *&renderer) {
  std::vector<Wall *> walls;
  // const char *brick_wall =
  //     "/home/lennard/Projects/raycast_engine/web/resources/gai_wall_1_240p.png";
  // const char *brick_wall =
  //     "/home/lennard/Projects/raycast_engine/web/textures/gai_wall_1_240p.png";
  // const char *stone_wall = "/home/lennard/Projects/raycast_engine/web/"
  //                          "textures/gai_wall_1_light_240p.png";
  const char *brick_wall = "../resources/gai_wall_1_240p.png";
  const char *stone_wall = "../resources/gai_wall_1_light_240p.png";
  const char *wall_img;
  char tile;
  int texture;
  float wall_coords[4] = {0.0, 0.0, 0.0, 0.0};

  for (float y = 0; y < worldMap.size(); y++) {
    for (float x = 0; x < worldMap[0].size(); x++) {
      if (worldMap[y][x] != "O0") {
        // my first line of AI promt code, omg it's starting
        if (worldMap[y][x].length() >= 2 && isdigit(worldMap[y][x].back())) {
          tile = (char)worldMap[y][x].front();
          texture = worldMap[y][x].back() -
                    '0'; // extract the integer value using ASCII arithmetic
        } else {
          std::cout << "Invalid input" << std::endl;
        }
        switch (texture) {
        case 1:
          wall_img = brick_wall;
          break;
        case 2:
          wall_img = stone_wall;
          break;
        }
        switch (tile) {
        case 'u':
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2, wall_img, renderer));
          break;
        case 'd':
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        case 'l':
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        case 'r':
          walls.push_back(
              new Wall(x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        case 'F':
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2, wall_img, renderer));
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        case 'T':
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2, wall_img, renderer));
          walls.push_back(
              new Wall(x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        case 'L':
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        case 'J':
          walls.push_back(
              new Wall(x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        case 'H':
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          walls.push_back(
              new Wall(x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        case 'B':
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size - (float)world_h / 2, wall_img, renderer));
          walls.push_back(
              new Wall(x * wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2,
                       x * wall_size + wall_size - (float)world_w / 2,
                       y * wall_size + wall_size - (float)world_h / 2, wall_img,
                       renderer));
          break;
        }
      }
    }
  }
  // map borders (not nessecary if map in enclosed with wall "collisions")
  for (int i = 0; i < world_w / wall_size; i++) {
    walls.push_back(new Wall((float)-world_w / 2 + i * wall_size,
                             (float)-world_h / 2,
                             (float)-world_w / 2 + (i + 1) * wall_size,
                             (float)-world_h / 2, brick_wall, renderer));
    walls.push_back(new Wall((float)-world_w / 2 + i * wall_size,
                             (float)world_h / 2,
                             (float)-world_w / 2 + (i + 1) * wall_size,
                             (float)world_h / 2, brick_wall, renderer));
  }
  for (int i = 0; i < world_h / wall_size; i++) {
    walls.push_back(
        new Wall((float)-world_w / 2, (float)-world_h / 2 + i * wall_size,
                 (float)-world_w / 2, (float)-world_h / 2 + (i + 1) * wall_size,
                 brick_wall, renderer));
    walls.push_back(
        new Wall((float)world_w / 2, (float)-world_h / 2 + i * wall_size,
                 (float)world_w / 2, (float)-world_h / 2 + (i + 1) * wall_size,
                 brick_wall, renderer));
  }
  return walls;
}
