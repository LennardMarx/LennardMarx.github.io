#pragma once
#ifndef WORLD_UTILS_H
#define WORLD_UTILS_H

#include "../include/wall.h"
#include <array>
#include <iostream>
#include <vector>

class WorldUtils {
public:
  std::vector<Wall *>
  createWorld2(std::array<std::array<std::string, 16>, 16> worldMap,
               const int world_w, const int world_h, const int wall_size,
               SDL_Renderer *&renderer);
};
// std::vector<Wall *>
// createWorld2(std::array<std::array<std::string, 16>, 16> worldMap,
//              const int world_w, const int world_h, const int wall_size,
//              SDL_Renderer *&renderer) {
//   std::vector<Wall *> walls;
//   const char *brick_wall = "../resources/gai_wall_1_240p.png";
//   const char *stone_wall = "../resources/gai_wall_1_light_240p.png";
//   const char *wall_img;
//   char tile;
//   int texture;
//   float wall_coords[4] = {0.0, 0.0, 0.0, 0.0};
//
//   for (float y = 0; y < worldMap.size(); y++) {
//     for (float x = 0; x < worldMap[0].size(); x++) {
//       if (worldMap[y][x] != "O0") {
//         // my first line of AI promt code, omg it's starting
//         if (worldMap[y][x].length() >= 2 && isdigit(worldMap[y][x].back())) {
//           tile = (char)worldMap[y][x].front();
//           texture = worldMap[y][x].back() -
//                     '0'; // extract the integer value using ASCII arithmetic
//         } else {
//           std::cout << "Invalid input" << std::endl;
//         }
//         switch (texture) {
//         case 1:
//           wall_img = brick_wall;
//           break;
//         case 2:
//           wall_img = stone_wall;
//           break;
//         }
//         switch (tile) {
//         case 'u':
//           walls.push_back(
//               new Wall(x * wall_size - world_w / 2, y * wall_size - world_h /
//               2,
//                        x * wall_size + wall_size - world_w / 2,
//                        y * wall_size - world_h / 2, wall_img, renderer));
//           break;
//         case 'd':
//           walls.push_back(new Wall(x * wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    wall_img, renderer));
//           break;
//         case 'l':
//           walls.push_back(new Wall(
//               x * wall_size - world_w / 2, y * wall_size - world_h / 2,
//               x * wall_size - world_w / 2,
//               y * wall_size + wall_size - world_h / 2, wall_img, renderer));
//           break;
//         case 'r':
//           walls.push_back(new Wall(x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size - world_h / 2,
//                                    x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    wall_img, renderer));
//           break;
//         case 'F':
//           walls.push_back(
//               new Wall(x * wall_size - world_w / 2, y * wall_size - world_h /
//               2,
//                        x * wall_size + wall_size - world_w / 2,
//                        y * wall_size - world_h / 2, wall_img, renderer));
//           walls.push_back(new Wall(
//               x * wall_size - world_w / 2, y * wall_size - world_h / 2,
//               x * wall_size - world_w / 2,
//               y * wall_size + wall_size - world_h / 2, wall_img, renderer));
//           break;
//         case 'T':
//           walls.push_back(
//               new Wall(x * wall_size - world_w / 2, y * wall_size - world_h /
//               2,
//                        x * wall_size + wall_size - world_w / 2,
//                        y * wall_size - world_h / 2, wall_img, renderer));
//           walls.push_back(new Wall(x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size - world_h / 2,
//                                    x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    wall_img, renderer));
//           break;
//         case 'L':
//           walls.push_back(new Wall(
//               x * wall_size - world_w / 2, y * wall_size - world_h / 2,
//               x * wall_size - world_w / 2,
//               y * wall_size + wall_size - world_h / 2, wall_img, renderer));
//           walls.push_back(new Wall(x * wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    wall_img, renderer));
//           break;
//         case 'J':
//           walls.push_back(new Wall(x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size - world_h / 2,
//                                    x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    wall_img, renderer));
//           walls.push_back(new Wall(x * wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    wall_img, renderer));
//           break;
//         case 'H':
//           walls.push_back(new Wall(
//               x * wall_size - world_w / 2, y * wall_size - world_h / 2,
//               x * wall_size - world_w / 2,
//               y * wall_size + wall_size - world_h / 2, wall_img, renderer));
//           walls.push_back(new Wall(x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size - world_h / 2,
//                                    x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    wall_img, renderer));
//           break;
//         case 'B':
//           walls.push_back(
//               new Wall(x * wall_size - world_w / 2, y * wall_size - world_h /
//               2,
//                        x * wall_size + wall_size - world_w / 2,
//                        y * wall_size - world_h / 2, wall_img, renderer));
//           walls.push_back(new Wall(x * wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    x * wall_size + wall_size - world_w / 2,
//                                    y * wall_size + wall_size - world_h / 2,
//                                    wall_img, renderer));
//           break;
//         }
//       }
//     }
//   }
//   // map borders (not nessecary if map in enclosed with wall "collisions")
//   for (int i = 0; i < world_w / wall_size; i++) {
//     walls.push_back(new Wall(-world_w / 2 + i * wall_size, -world_h / 2,
//                              -world_w / 2 + (i + 1) * wall_size, -world_h /
//                              2, brick_wall, renderer));
//     walls.push_back(new Wall(-world_w / 2 + i * wall_size, world_h / 2,
//                              -world_w / 2 + (i + 1) * wall_size, world_h / 2,
//                              brick_wall, renderer));
//   }
//   for (int i = 0; i < world_h / wall_size; i++) {
//     walls.push_back(new Wall(-world_w / 2, -world_h / 2 + i * wall_size,
//                              -world_w / 2, -world_h / 2 + (i + 1) *
//                              wall_size, brick_wall, renderer));
//     walls.push_back(new Wall(world_w / 2, -world_h / 2 + i * wall_size,
//                              world_w / 2, -world_h / 2 + (i + 1) * wall_size,
//                              brick_wall, renderer));
//   }
//   return walls;
// }

// TODO: remove walls if they're on the same spot/ overlapping
// std::vector<Wall*> createWorld(std::array<std::array<int, 16>, 16> worldMap,
// const int world_w, const int world_h, const int wall_size, SDL_Renderer*&
// renderer)
// {
//     std::vector<Wall*> walls;
//     const char* brick_wall = "../resources/gai_wall_1_240p.png";
//     const char* stone_wall = "../resources/gai_wall_1_light_240p.png";
//     const char* wall_img;

//     for (int y = 0; y < worldMap.size(); y++)
//     {
//         for (int x = 0; x < worldMap[0].size(); x++)
//         {
//             if (worldMap[y][x] != 0)
//             {
//                 if (worldMap[y][x] == 1)
//                 {
//                     wall_img = brick_wall;
//                 }
//                 if (worldMap[y][x] == 2)
//                 {
//                     wall_img = stone_wall;
//                 }
//                 walls.push_back(new Wall(x * wall_size - world_w / 2, y *
//                 wall_size - world_h / 2, x * wall_size + wall_size - world_w
//                 / 2, y * wall_size - world_h / 2, wall_img, renderer));
//                 walls.push_back(new Wall(x * wall_size - world_w / 2, y *
//                 wall_size - world_h / 2, x * wall_size - world_w / 2, y *
//                 wall_size + wall_size - world_h / 2, wall_img, renderer));
//                 walls.push_back(new Wall(x * wall_size - world_w / 2, y *
//                 wall_size + wall_size - world_h / 2, x * wall_size +
//                 wall_size - world_w / 2, y * wall_size + wall_size - world_h
//                 / 2, wall_img, renderer)); walls.push_back(new Wall(x *
//                 wall_size + wall_size - world_w / 2, y * wall_size - world_h
//                 / 2, x * wall_size + wall_size - world_w / 2, y * wall_size +
//                 wall_size - world_h / 2, wall_img, renderer));
//             }
//         }
//     }
//     //map borders
//     for (int i = 0; i < world_w / wall_size; i++)
//     {
//         walls.push_back(new Wall(-world_w / 2 + i * wall_size, -world_h / 2,
//         -world_w / 2 + (i + 1) * wall_size, -world_h / 2, brick_wall,
//         renderer)); walls.push_back(new Wall(-world_w / 2 + i * wall_size,
//         world_h / 2, -world_w / 2 + (i + 1) * wall_size, world_h / 2,
//         brick_wall, renderer));
//     }
//     for (int i = 0; i < world_h / wall_size; i++)
//     {
//         walls.push_back(new Wall(-world_w / 2, -world_h / 2 + i * wall_size,
//         -world_w / 2, -world_h / 2 + (i + 1) * wall_size, brick_wall,
//         renderer)); walls.push_back(new Wall(world_w / 2, -world_h / 2 + i *
//         wall_size, world_w / 2, -world_h / 2 + (i + 1) * wall_size,
//         brick_wall, renderer));
//     }
//     return walls;
// }

// lower letter for direction of wall in square (u = up, d = down, l = left, r =
// right) upper letter for corners: F = ┌, T = ┐, L = └, J = ┘
// std::array<std::array<char, 16>, 16> worldMap2;
// worldMap2[0] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[1] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[2] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[3] = {
// 'x','x','x','d','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[4] = {
// 'x','x','r','x','l','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[5] = {
// 'x','x','x','u','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[6] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[7] = {
// 'x','x','x','x','x','x','d','x','x','x','x','x','x','x','x','x' };
// worldMap2[8] = {
// 'x','x','x','x','x','x','x','F','x','x','x','x','x','x','x','x' };
// worldMap2[9] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[a] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[b] = {
// 'x','x','x','x','x','x','x','x','x','F','x','x','x','x','x','x' };
// worldMap2[c] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[d] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[e] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };
// worldMap2[f] = {
// 'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x' };

// std::array<std::array<int, 16>, 16> worldMap;
// worldMap[0] = { 0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0 };
// worldMap[1] = { 0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0 };
// worldMap[2] = { 0,1,1,1,2,1,1,0,1,1,1,1,1,0,0,0 };
// worldMap[3] = { 0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0 };
// worldMap[4] = { 0,1,0,1,2,1,1,0,1,1,1,1,1,0,0,0 };
// worldMap[5] = { 0,1,0,1,0,0,1,0,1,0,0,0,0,0,0,0 };
// worldMap[6] = { 0,1,0,1,0,0,1,2,1,0,0,0,0,0,0,0 };
// worldMap[7] = { 0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0 };
// worldMap[8] = { 0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0 };
// worldMap[9] = { 0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0 };
// worldMap[a] = { 0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0 };
// worldMap[b] = { 0,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0 };
// worldMap[c] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
// worldMap[d] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
// worldMap[e] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
// worldMap[f] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//

#endif
