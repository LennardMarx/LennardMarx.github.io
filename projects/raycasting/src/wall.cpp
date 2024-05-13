#include "../include/wall.h"

Wall::Wall(float wall_coords[], const char* img_path, SDL_Renderer*& renderer)
{
    position[0] = wall_coords[0];
    position[1] = wall_coords[1];
    position[2] = wall_coords[2];
    position[3] = wall_coords[3];
    wall_sur = IMG_Load(img_path);
    wall_tex = SDL_CreateTextureFromSurface(renderer, wall_sur);

    // SDL_SetTextureBlendMode(wall_tex, SDL_BLENDMODE_BLEND);
    // Uint8 alpha = 0x3F;
    // SDL_SetTextureAlphaMod(wall_tex, alpha);
}

Wall::Wall(float _x1, float _y1, float _x2, float _y2, const char* img_path, SDL_Renderer*& renderer)
{
    position[0] = _x1;
    position[1] = _y1;
    position[2] = _x2;
    position[3] = _y2;
    wall_sur = IMG_Load(img_path);
    wall_tex = SDL_CreateTextureFromSurface(renderer, wall_sur);

    // SDL_SetTextureBlendMode(wall_tex, SDL_BLENDMODE_BLEND);
    // Uint8 alpha = 0x3F;
    // SDL_SetTextureAlphaMod(wall_tex, alpha);
}

Wall::~Wall() {}



// void Wall::draw(UI& ui)
// {
//     ui.drawLine(position[0], position[1], position[2], position[3]);
// }


// void Wall::setPos() {}

std::array<float, 4> Wall::getPos() { return position; }

SDL_Surface* Wall::getSurface() { return wall_sur; }
SDL_Texture* Wall::getTexture() { return wall_tex; }
