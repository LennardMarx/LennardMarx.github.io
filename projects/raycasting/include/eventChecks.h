#pragma once

#ifndef EVENT_CHECKS_H
#define EVENT_CHECKS_H

// #include "../include/UI.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <utility>
#include <vector>
#include <array>
#include <iostream>
#include "../include/raycaster.h"
#include "../include/movement.h"
#include "../include/UI.h"

// inline Movement operator|(Movement a, Movement b)
// {
//     return static_cast<Movement>(static_cast<int>(a) | static_cast<int>(b));
// }

// inline Movement operator&(Movement a, Movement b)
// {
//     return static_cast<Movement>(static_cast<int>(a) & static_cast<int>(b));
// }


class EventChecks
{

public:
    EventChecks();
    ~EventChecks();

    void checkEvents(RayCaster& player, UI&, Uint32);

    bool getQuit();
    bool getPause();
    MovementFlag getMovement();
    int getRotationDirection();

    SDL_Event* getEvent();

    void jump(UI&, Uint32);

    void handleKeyboardEvent();
    bool isPressed(int);
    bool isReleased(int);

    void movePlayer(RayCaster&);


private:
    SDL_Event* event_ptr;// = &event;
    bool quit = false;
    bool pause = false;
    int rotation = 0;
    MovementFlag movement;
    int jump_timer = 0;
    bool is_jumping = false;
    int initial_height = 0;

    const float SPEED = 2.0;
    float speed;


    const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);

    bool keyState[];
};

#endif