#include <SDL2/SDL.h>
#include <array>
#include "../include/UI.h"
#include "../include/rectangle.h"


Rectangle::Rectangle(float _x, float _y, float _w, float _h): x(_x), y(_y), w(_w), h(_h)
{
    // defineWalls();
    storeWalls();
}
Rectangle::~Rectangle() {}

void Rectangle::setPos(float _x, float _y)
{
    x = _x;
    y = _y;
    storeWalls(); // update walls
}
std::array<float, 2> Rectangle::getPos()
{
    pos.at(0) = x;
    pos.at(1) = y;
    return pos;
}

void Rectangle::setSize(float _w, float _h)
{
    w = _w;
    h = _h;
    storeWalls(); // update walls
}
std::array<float, 2> Rectangle::getSize()
{
    size.at(0) = w;
    size.at(1) = h;
    return size;
}

void Rectangle::draw(UI& ui)
{
    ui.drawLine(x, y, x, y + h);
    ui.drawLine(x, y, x + w, y);
    ui.drawLine(x + w, y, x + w, y + h);
    ui.drawLine(x, y + h, x + w, y + h);

    // ui.drawLine(x-w/2, y-h/2, x-w/2, y+h/2);
    // ui.drawLine(x-w/2, y-h/2, x+w/2, y-h/2);
    // ui.drawLine(x+w/2, y+h/2, x+w/2, y-h/2);
    // ui.drawLine(x+w/2, y+h/2, x-w/2, y+h/2);
}

void Rectangle::storeWalls()
{
    while (!rect_walls.empty())
    {
        rect_walls.pop_back();
    }
    rect_walls.push_back({ x, y, x, y + h });
    rect_walls.push_back({ x, y, x + w, y });
    rect_walls.push_back({ x + w, y, x + w, y + h });
    rect_walls.push_back({ x, y + h, x + w, y + h });
}

std::vector<std::array<float, 4>> Rectangle::getWalls()
{
    return rect_walls;
}

