#include <SDL2/SDL.h>

#include <vector>
#include <array>

#include "../include/entity.h"


// Entity::Entity() {}

Entity::Entity(float x, float  y) {
    position.x = x;
    position.y = y;
    previous_position.x = x;
    previous_position.y = y;
};

// Entity::Entity(Coordinate position) {
//     this->position=position;
// }

Entity::~Entity() {
};


void Entity::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
};

Coordinate Entity::getPosition()
{
    return position;
};


float Entity::getOrientation() {
    return orientation;
};

void Entity::setOrientation(float orientation) {
    this->orientation = orientation;
};

void Entity::rotate(int direction) {
    orientation = orientation + direction * 1;
}

void Entity::move(MovementFlag movement)
{
    float direction = orientation * PI / 180;
    if (movement.any(Movement::Forward | Movement::Backward | Movement::Left | Movement::Right)) {
        if (movement.has(Movement::Left))
        {
            if (movement.has(Movement::Forward)) {
                direction = direction - PI / 4;
            }
            else if (movement.has(Movement::Backward)) {
                direction = direction + PI / 4;
            }
            else {
                direction = direction - PI / 2;
            }
        }
        else if (movement.has(Movement::Right))
        {
            if (movement.any(Movement::Forward)) {
                direction = direction + PI / 4;
            }
            else if (movement.has(Movement::Backward)) {
                direction = direction - PI / 4;
            }
            else {
                direction = direction + PI / 2;
            }
        }

        if (movement.has(Movement::Backward)) {
            direction = direction + PI;
        }
        position.y += round(sin(direction)) * 2;
        position.x += round(cos(direction)) * 2;
        // if (vertical_collision)
        //     position.x = previous_position.x;
        // std::cout << "set back!" << std::endl;
    }
}


// void Entity::move2(EventChecks& eventChecks)
// {
//     float angle = orientation / 180 * PI;
//     if (eventChecks.isPressed(SDLK_a))
//     {
//         setPosition(getPosition().x + cos(angle - PI / 2), getPosition().y + sin(angle - PI / 2));

//     }
// }

void Entity::collideHorizontal(int wall_pos, int sign) { position.x = wall_pos + sign * BODY_RADIUS; }
void Entity::collideVertical(int wall_pos, int sign) { position.y = wall_pos + sign * BODY_RADIUS; }

void Entity::updatePreviousPosition() { previous_position = position; }

void Entity::checkCollision(std::vector<Wall*> walls)
{
    for (int i = 0; i < walls.size();i++)
    {
        int x1 = walls[i]->getPos()[0];
        int y1 = walls[i]->getPos()[1];
        int x2 = walls[i]->getPos()[2];
        int y2 = walls[i]->getPos()[3];

        if (position.y > y1 - 1 && position.y < y2 + 1 && (abs(position.x - x1) <= BODY_RADIUS)) //&& abs(previous_position.x - x1) > 10
        {
            if (position.x < x1)
                collideHorizontal(x1, -1);
            if (position.x > x1)
                collideHorizontal(x1, 1);
        }
        if (position.x > x1 - 1 && position.x < x2 + 1 && (abs(position.y - y1) <= BODY_RADIUS)) //&& abs(previous_position.x - x1) > 10
        {
            if (position.y < y1)
                collideVertical(y1, -1);
            if (position.y > y1)
                collideVertical(y1, 1);
        }
    }
    // std::cout << position.x << ", " << position.y << std::endl;

    // std::cout << vertical_collision << std::endl;
}
