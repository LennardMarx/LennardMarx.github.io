#include "../include/UI.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

UI::UI(int sizeX, int sizeY, int posX)
    : sizeX(sizeX), sizeY(sizeY), posX(posX) {
  initialize(sizeX, sizeY, posX);
}

UI::~UI() {
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  if (font)
    TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

void UI::clear() {
  setDrawColor(0, 0, 0, 255);
  SDL_RenderClear(renderer);
  setDrawColor(255, 255, 255, 255);
}

void UI::present() { SDL_RenderPresent(renderer); }

void UI::drawPixel(int x, int y) {
  SDL_RenderDrawPoint(renderer, x + sizeX / 2, y + sizeY / 2);
}

void UI::drawLine(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(renderer, x1 + sizeX / 2, y1 + sizeY / 2, x2 + sizeX / 2,
                     y2 + sizeY / 2);
}

void UI::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void UI::drawWalls(std::vector<Wall *> walls) {
  setDrawColor(255, 255, 255, 255);
  for (int i = 0; i < walls.size(); i++) {
    drawLine(walls[i]->getPos()[0], walls[i]->getPos()[1],
             walls[i]->getPos()[2], walls[i]->getPos()[3]);
  }
}
void UI::drawRays(std::vector<std::array<float, 4>> rays) {
  setDrawColor(200, 200, 200, 10);
  for (int i = 0; i < rays.size(); i++) {
    drawLine(rays[i][0], rays[i][1], rays[i][2], rays[i][3]);
  }
}

void UI::drawMiniMap(std::vector<Wall *> walls,
                     std::vector<std::array<float, 4>> rays) {
  SDL_Rect map_location;
  map_location.x = sizeX - mini_w;
  map_location.y = 0;
  map_location.w = mini_w;
  map_location.h = mini_h;

  setDrawColor(0, 0, 0, 100);
  SDL_RenderFillRect(renderer, &map_location);

  int offset_x = sizeX / 2 - (float)mini_w / 2;
  int offset_y = -sizeY / 2 + (float)mini_h / 2;

  setDrawColor(255, 255, 255, 100);
  for (int i = 0; i < walls.size(); i++) {
    drawLine(walls[i]->getPos()[0] / 800 * mini_w + offset_x,
             walls[i]->getPos()[1] / 800 * mini_h + offset_y,
             walls[i]->getPos()[2] / 800 * mini_w + offset_x,
             walls[i]->getPos()[3] / 800 * mini_h + offset_y);
  }
  setDrawColor(255, 255, 255, 5);
  for (int i = 0; i < rays.size(); i++) {
    drawLine(rays[i][0] / 800 * mini_w + offset_x,
             rays[i][1] / 800 * mini_h + offset_y,
             rays[i][2] / 800 * mini_w + offset_x,
             rays[i][3] / 800 * mini_h + offset_y);
  }
}

void UI::drawTexturedWalls(std::vector<float> distances,
                           std::vector<int> position_on_wall,
                           std::vector<SDL_Texture *> textures) {
  // std::cout << distances.size() << ", " << position_on_wall.size() << ", "
  //           << textures.size() << std::endl;
  // if (!textures[0]) {
  //   std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
  //   return;
  // }
  for (int i = 0; i < distances.size(); i++) {
    tile_width = sizeX / distances.size();
    tile_height = 50000 / distances[i];

    SDL_Rect rect;
    rect.x = i * tile_width;
    rect.y =
        (sizeY - tile_height) / 2 + view_angle - jump_height / distances[i];
    rect.w = std::ceil(tile_width);
    rect.h = tile_height;

    alpha = tile_height / 1.5;
    // alpha = -0.00008 * tile_height * tile_height + 0.6 * tile_height - 10.0;
    if (alpha > 255)
      alpha = 255;
    if (alpha < 0)
      alpha = 0;

    setDrawColor(0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    // check if rendere is null
    // std::cout << (renderer == nullptr) << std::endl;

    // setDrawColor(249, 245, 215, 255 - alpha);
    // setDrawColor(249, 245, 215, alpha);
    // setDrawColor(0, 0, 0, alpha);
    setDrawColor(0, 0, 0, 255 - alpha);

    float WALL_SIZE = 50;
    float IMAGE_SIZE = 240;

    SDL_Rect part_of_image;
    part_of_image.x = (float)position_on_wall[i] / WALL_SIZE * IMAGE_SIZE;
    part_of_image.y = 0;
    part_of_image.w = IMAGE_SIZE / WALL_SIZE;
    part_of_image.h = IMAGE_SIZE;

    SDL_RenderCopy(renderer, textures[i], &part_of_image, &rect);
    SDL_RenderFillRect(renderer, &rect);
  }
}

void UI::drawBackground() {
  SDL_Rect sky_rect;
  sky_rect.x = 0;
  sky_rect.y = 0 - 500;
  sky_rect.w = sizeX;
  sky_rect.h = sizeY / 2 + view_angle + 500;
  SDL_Rect floor_rect;
  floor_rect.x = 0;
  floor_rect.y = sizeY / 2 + view_angle;
  floor_rect.w = sizeX;
  floor_rect.h = sizeY / 2 - view_angle;

  // setDrawColor(17, 0, 51, 200);
  // setDrawColor(0, 150, 200, 200);
  setDrawColor(69, 133, 136, 200);
  SDL_RenderFillRect(renderer, &sky_rect);
  setDrawColor(40, 40, 40, 200);
  // setDrawColor(249, 245, 215, 200);
  SDL_RenderFillRect(renderer, &floor_rect);
}

void UI::drawCrossHair() {
  setDrawColor(255, 255, 255, 100);
  // drawLine(sizeX / 2, sizeY / 2, sizeX / 2, sizeY / 2 + 10);
  drawLine(5, 0, 10, 0);
  drawLine(-5, 0, -10, 0);
  drawLine(0, 5, 0, 10);
  drawLine(0, -5, 0, -10);
}

void UI::setViewAngle(int height) { view_angle = height; }
int UI::getViewAngle() { return view_angle; }

void UI::setJumpHeight(int height) { jump_height = height; }
int UI::getJumpHeight() { return jump_height; }

void UI::printText(const char *text, int x, int y, SDL_Color color) {
  SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);

  SDL_Surface *optimizedSurface =
      SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
  if (!optimizedSurface) {
    std::cerr << "Failed to optimize surface: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(surface);
    return;
  }

  // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(renderer, optimizedSurface);
  SDL_Rect dest_rect = {x + (int)sizeX / 2 - surface->w * 3 / 2,
                        y + (int)sizeY / 2 - surface->h * 3 / 2, surface->w * 3,
                        surface->h * 3};

  SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);
}

void UI::initialize(int sizeX, int sizeY, int posX) {
  SDL_Init(SDL_INIT_EVERYTHING);
  // Create a Window
  window =
      SDL_CreateWindow("Ray Casting", 0, 0, sizeX, sizeY, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(
      window, -1,
      SDL_RENDERER_ACCELERATED |
          SDL_RENDERER_PRESENTVSYNC); // | SDL_RENDERER_PRESENTVSYNC
  SDL_SetWindowSize(window, sizeX, sizeY);

  TTF_Init();
  font = TTF_OpenFont("../resources/RetroGaming.ttf", 24);

  if (!font) {
    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    return;
  }

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  // place window in middle of screen after scaling
  // SDL_SetWindowPosition(window, posX, SDL_WINDOWPOS_CENTERED);
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

SDL_Renderer *&UI::getRenderer() { return renderer; }
