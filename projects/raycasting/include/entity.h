#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <array>
#include <vector>
#include <SDL2/SDL.h>
#include "../include/movement.h"
#include "../include/wall.h"
// #include "../include/eventChecks.h"
#include <iostream>
#include <cmath>

enum class EntityType { Player, Snapshot };

class Entity
    /* TODO:
    *   - Memorize player movements
    *   - Raycaster moves along w player
    *   - Place sprite in env?
    */
{
public:
    /**
     * Initialize the player
    */
    // Entity();
    Entity(float x, float y);
    // Entity(Coordinate);
    ~Entity();

    void setPosition(float x, float y);
    Coordinate getPosition();

    void setOrientation(float);
    float getOrientation();

    /**
     * Move the entity
    */
    void move(MovementFlag movement);

    // void move2(EventChecks&);

    void rotate(int direction);

    void collideVertical(int, int);
    void collideHorizontal(int, int);

    void updatePreviousPosition();
    void checkCollision(std::vector<Wall*>);


protected:
    Coordinate position;
    Coordinate previous_position;
    float orientation = 90;
    EntityType entityType;
    std::pair<int, int> movementSpeed;
    SDL_Texture* texture;
    bool horizontal_collision = false, vertical_collision = false;
    const int BODY_RADIUS = 10;
};


#endif