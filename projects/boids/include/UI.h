#ifndef UI_H
#define UI_H

#include "../include/AnimatedSprite.hpp"
#include "../include/TexturedRectangle.hpp"
#include <SDL2/SDL.h>

class UI {
public:
  const int sizeX;
  const int sizeY;

  UI(int, int);
  ~UI();

  void clear();
  void present();
  void drawPixel(int, int);
  void drawLine(int, int, int, int);
  void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  SDL_Renderer *&getRenderer(); // pointer reference to the renderer
  SDL_Window *getWindow();      // pointer to the window

private:
  void initialize(int, int);

private:
  SDL_Window *window = nullptr;     // create window pointer
  SDL_Renderer *renderer = nullptr; // create renderer pointer

  // TexturedRectangle birdTex;

  bool quit;
};

#endif
