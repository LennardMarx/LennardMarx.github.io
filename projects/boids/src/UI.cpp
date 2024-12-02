#include "../include/UI.h"

UI::UI(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {
  initialize(sizeX, sizeY);
}

UI::~UI() {
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();
}

// TODO: Maybe get rid of wrappers
void UI::clear() {
  SDL_SetRenderDrawColor(renderer, 69, 133, 136, 255); // gruv-blue
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 249, 245, 215, 150); // grub-light
}

void UI::present() {
  // SDL_Delay(10);
  SDL_RenderPresent(renderer);
}
// function to draw pixel on screen (not used)
void UI::drawPixel(int x, int y) {
  // SDL_RenderDrawPoint(renderer, x + sizeX / 2, y + sizeY / 2);
  SDL_RenderDrawPoint(renderer, x, y);
}
// function to draw line between two points
void UI::drawLine(int x1, int y1, int x2, int y2) {
  // SDL_RenderDrawLine(renderer, x1 + sizeX / 2, y1 + sizeY / 2, x2 + sizeX /
  // 2,
  //                    y2 + sizeY / 2);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void UI::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

SDL_Renderer *&UI::getRenderer() // pointer reference to the renderer
{
  return renderer;
}
SDL_Window *UI::getWindow() // pointer to the window
{
  return window;
}

// initializing the UI
void UI::initialize(int sizeX, int sizeY) {
  SDL_Init(SDL_INIT_EVERYTHING);

  // Create a Window
  window = SDL_CreateWindow("Drone Simulation", 0, 0, sizeX, sizeY,
                            SDL_WINDOW_SHOWN);

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  // scale window
  SDL_SetWindowSize(window, sizeX, sizeY);
  // adjust render scale
  SDL_RenderSetScale(renderer, 1, 1);
  // place window in middle of screen after scaling
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
