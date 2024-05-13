# pragma once

#ifndef SRC_UI_H_
#define SRC_UI_H_

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <string>

#include "../include/wall.h"
#include "../include/movement.h"

class UI
{
public:
    float sizeX;
    float sizeY;
    float posX;

    UI(int, int, int);

    ~UI();

    void clear();
    void present();

    void drawPixel(int x, int y);
    void drawLine(int x1, int y1, int x2, int y2);
    void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void drawWalls(std::vector<Wall*>);
    void drawRays(std::vector<std::array<float, 4>>);
    void drawMiniMap(std::vector<Wall*>, std::vector<std::array<float, 4>>);
    void drawTexturedWalls(std::vector<float>, std::vector<int>, std::vector<SDL_Texture*>);
    void drawBackground();
    void drawCrossHair();

    void setViewAngle(int);
    int getViewAngle();

    void setJumpHeight(int);
    int getJumpHeight();

    void printText(const char*, int, int, SDL_Color);

    SDL_Renderer*& getRenderer(); // pointer reference to the renderer


private:
    void initialize(int, int, int);

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    int x1, x2, y1, y2;
    float tile_width, tile_height;
    int up, down, left, right;
    float alpha;

    int mini_w = 300, mini_h = 300;
    int view_angle = -150;

    int jump_height = 0;
};

#endif /* SRC_UI_H_ */