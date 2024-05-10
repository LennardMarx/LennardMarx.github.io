#include "../include/interface.h"
#include <SDL2/SDL_render.h>
#include <stdlib.h>

// struct interface {
//   int height;
//   int width;
//   SDL_Window *window;
//   SDL_Window *(*create_window)(char *name);
//   SDL_Renderer *renderer;
//   SDL_Renderer *(*create_renderer)(SDL_Window *window);
// };

SDL_Window *create_window_function(char *name, int width, int height) {
  SDL_Window *window = NULL;
  window =
      SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);
  return window;
}

SDL_Renderer *create_renderer_function(SDL_Window *window) {
  SDL_Renderer *renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  return renderer;
}

void draw_rect_outline_function(SDL_Renderer *renderer, SDL_Rect *r) {
  int x1 = r->x;
  int y1 = r->y;
  int x2 = r->x + r->w;
  int y2 = r->y;
  int x3 = r->x + r->w;
  int y3 = r->y + r->h;
  int x4 = r->x;
  int y4 = r->y + r->h;
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
  SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
  SDL_RenderDrawLine(renderer, x3, y3, x4, y4);
  SDL_RenderDrawLine(renderer, x4, y4, x1, y1);
}

void init_interface(Interface *interface, int width, int height) {
  if (interface == NULL) {
    interface = malloc(sizeof(Interface));
  }

  interface->create_window = create_window_function;
  interface->create_renderer = create_renderer_function;

  interface->draw_rect_outline = draw_rect_outline_function;
  interface->draw_cube = draw_cube_function;

  interface->window = interface->create_window("C Renderer", width, height);
  interface->renderer = interface->create_renderer(interface->window);
}

void destroy_interface(Interface *interface) { free(interface); }

void draw_cube_function(SDL_Renderer *renderer,
                        Cube *cube) { // int screen_pos[8][2]) {

  SDL_RenderDrawLine(renderer, cube->screen_pos[0][0], cube->screen_pos[0][1],
                     cube->screen_pos[1][0], cube->screen_pos[1][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[1][0], cube->screen_pos[1][1],
                     cube->screen_pos[2][0], cube->screen_pos[2][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[2][0], cube->screen_pos[2][1],
                     cube->screen_pos[3][0], cube->screen_pos[3][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[3][0], cube->screen_pos[3][1],
                     cube->screen_pos[0][0], cube->screen_pos[0][1]);

  SDL_RenderDrawLine(renderer, cube->screen_pos[4][0], cube->screen_pos[4][1],
                     cube->screen_pos[5][0], cube->screen_pos[5][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[5][0], cube->screen_pos[5][1],
                     cube->screen_pos[6][0], cube->screen_pos[6][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[6][0], cube->screen_pos[6][1],
                     cube->screen_pos[7][0], cube->screen_pos[7][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[7][0], cube->screen_pos[7][1],
                     cube->screen_pos[4][0], cube->screen_pos[4][1]);

  SDL_RenderDrawLine(renderer, cube->screen_pos[0][0], cube->screen_pos[0][1],
                     cube->screen_pos[4][0], cube->screen_pos[4][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[1][0], cube->screen_pos[1][1],
                     cube->screen_pos[5][0], cube->screen_pos[5][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[2][0], cube->screen_pos[2][1],
                     cube->screen_pos[6][0], cube->screen_pos[6][1]);
  SDL_RenderDrawLine(renderer, cube->screen_pos[3][0], cube->screen_pos[3][1],
                     cube->screen_pos[7][0], cube->screen_pos[7][1]);
}
