#pragma once

#ifndef WALL_H
#define WALL_H

#include <array>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
// #include "../include/UI.h"

class Wall
{
public:
    Wall(float[], const char*, SDL_Renderer*&);
    Wall(float, float, float, float, const char*, SDL_Renderer*&);

    ~Wall();

    // void draw(UI& ui);

    // void setPos();
    std::array<float, 4> getPos();

    SDL_Surface* getSurface();
    SDL_Texture* getTexture();

private:
    // float x1, y1, x2, y2;
    std::array<float, 4> position;
    SDL_Surface* wall_sur = nullptr;
    SDL_Texture* wall_tex = nullptr;
};

#endif