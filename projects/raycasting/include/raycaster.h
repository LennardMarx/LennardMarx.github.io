#pragma once

#ifndef APPLE_H
#define APPLE_H

#include <array>
#include "../include/wall.h"
#include "../include/UI.h"
#include "../include/movement.h"
#include "../include/entity.h"

class RayCaster: public Entity
{
public:
    using Entity::Entity;
    ~RayCaster();

    std::vector<float> getDistances();
    std::vector<Coordinate> getIntersections();
    std::vector<int> getPositionOnWall();
    std::vector<SDL_Texture*> getTextureInfo();

    std::vector<std::array<float, 4>> getRays();

    Coordinate calcIntersection();
    Coordinate getClosestIntersection();
    void calcIntersections(std::vector<Wall*>&);

    void emitLight(std::vector<Wall*>&);

    void lineAsFunction(float, float, float, float, float&, float&, float&);

    float calcPerpDist(float, float, float, float, float, float);


    // TODO: restructure passing of wall information seen by rays
    struct WallInfo {
        std::vector<Coordinate> intersection_buffer;

        std::vector<int> position_on_wall;

        std::vector<bool> wall_horizontal_vec;
        bool wall_horizontal;

        std::vector<SDL_Texture*> texture_buffer;
        std::vector<SDL_Texture*> texture_info;
        SDL_Texture* texture;
    };
    WallInfo wallInfo;


    // WallInfo getWallInfo();

    void whatDoISee();
    void forgetWhatISaw();

private:
    float x, y, c1, c2;
    float x1, x2, x3, x4, y1, y2, y3, y4;
    float t, u, denom;
    float pi = 3.14159265358979323846;
    float ang;
    int fov = 80; //field of view
    bool check = false;

    std::vector<std::array<float, 4>> rays;

    Coordinate intersection;
    Coordinate closestIntersection;
    float distance, lastDistance = 0, closestDistance;
    std::vector<Coordinate> intersections;
    std::vector<float> distances;


    std::vector<Coordinate> intersection_buffer;
    std::vector<int> position_on_wall;
    std::vector<bool> wall_horizontal_vec;
    bool wall_horizontal;
    std::vector<SDL_Texture*> texture_buffer;
    std::vector<SDL_Texture*> texture_info;
    SDL_Texture* texture;
};
#endif
