#include "../include/eventChecks.h"

EventChecks::EventChecks() { event_ptr = new SDL_Event; }
EventChecks::~EventChecks() {
  delete event_ptr;
  // std::cout << "clean up done!" << std::endl;
}

bool EventChecks::getQuit() { return quit; }
bool EventChecks::getPause() { return pause; }
MovementFlag EventChecks::getMovement() { return movement; }
int EventChecks::getRotationDirection() { return rotation; }

SDL_Event *EventChecks::getEvent() { return event_ptr; }

// void EventChecks::handleKeyboardEvent() {
//     keyState[event_ptr->key.keysym.sym] = event.state;
// }

bool EventChecks::isPressed(int keyCode) { return (keyState[keyCode] == true); }

bool EventChecks::isReleased(int keyCode) {
  return (keyState[keyCode] == true);
}

void EventChecks::checkEvents(RayCaster &player, UI &ui,
                              Uint32 frameStart) { // SDL_Event event
  // stop when pressing "x" (?)
  float angle = player.getOrientation() / 180 * PI;
  while (SDL_PollEvent(event_ptr)) {

    if (event_ptr->motion.type == SDL_MOUSEMOTION && !pause) {
      player.setOrientation(player.getOrientation() +
                            (float)event_ptr->motion.xrel / 2);
      ui.setViewAngle(ui.getViewAngle() - event_ptr->motion.yrel * 2);
      // std::cout << rotation;
      // std::cout << "\n";
    }
    if (event_ptr->window.event == SDL_WINDOWEVENT_CLOSE) {
      quit = true;
    }
    // key presses
    if (event_ptr->type == SDL_KEYDOWN) {
      if (keyboard_state_array[SDL_SCANCODE_W] &&
          !(keyboard_state_array[SDL_SCANCODE_S])) {
        player.setPosition(player.getPosition().x + cos(angle),
                           player.getPosition().y + sin(angle));
      }
      if (event_ptr->key.repeat == 0) {
        switch (event_ptr->key.keysym.sym) {
          // case SDLK_:
          //     quit = true;
          //     break;
        case SDLK_ESCAPE:
          // std::cout << (event_ptr->key.keysym.scancode);
          pause = !pause;
          break;
        case SDLK_SPACE:
          if (!is_jumping && !pause) {
            jump_timer = frameStart;
            initial_height = ui.getJumpHeight();
          }
          is_jumping = true;
          break;
        case SDLK_a:
          // movement.set(Movement::Left);
          // player.setPosition(player.getPosition().x + cos(angle - PI / 2),
          // player.getPosition().y + sin(angle - PI / 2));
          keyState[SDLK_a] = true;
          break;
        case SDLK_d:
          keyState[SDLK_d] = true;
          // movement.set(Movement::Right);
          break;
        case SDLK_w:
          keyState[SDLK_w] = true;
          // movement.set(Movement::Forward);
          // player.setPosition(player.getPosition().x + cos(angle),
          // player.getPosition().y + sin(angle));
          break;
        case SDLK_s:
          keyState[SDLK_s] = true;
          // movement.set(Movement::Backward);
          break;
        case SDLK_q:
          if (event_ptr->key.repeat == 0) {
            rotation = -1;
          }
          break;
        case SDLK_e:
          if (event_ptr->key.repeat == 0) {
            rotation = 1;
          }
          break;
        case SDLK_UP:
          // std::cout << "Key UP" << std::endl;
          ui.setJumpHeight(ui.getJumpHeight() + 5000);
          break;
        case SDLK_DOWN:
          ui.setJumpHeight(ui.getJumpHeight() - 5000);

          break;
        default:
          break;
        }
      }
    }
    if (event_ptr->type == SDL_KEYUP) {
      switch (event_ptr->key.keysym.sym) {
      case SDLK_a:
        // movement.unset(Movement::Left);
        keyState[SDLK_a] = false;
        break;
      case SDLK_w:
        // movement.unset(Movement::Forward);
        keyState[SDLK_w] = false;

        break;
      case SDLK_s:
        // movement.unset(Movement::Backward);
        keyState[SDLK_s] = false;

        break;
      case SDLK_d:
        // movement.unset(Movement::Right);
        keyState[SDLK_d] = false;

        break;
      case SDLK_q:
        rotation = 0;
        break;
      case SDLK_e:
        rotation = 0;
        break;
      default:
        break;
      }
    }
  }
  // if (!pause)
  jump(ui, frameStart);
  // std::cout << isPressed(SDLK_a) << std::endl;
  movePlayer(player);
}

void EventChecks::movePlayer(RayCaster &player) {
  float angle = player.getOrientation() / 180 * PI;
  speed = SPEED;

  if (isPressed(SDLK_w)) {
    if (isPressed(SDLK_a) || isPressed(SDLK_d)) {
      speed = SPEED * 0.7071;
    } // sqrt(2)/2
    player.setPosition(player.getPosition().x + cos(angle) * speed,
                       player.getPosition().y + sin(angle) * speed);
  }
  if (isPressed(SDLK_a)) {
    player.setPosition(player.getPosition().x + cos(angle - PI / 2) * speed,
                       player.getPosition().y + sin(angle - PI / 2) * speed);
  }
  if (isPressed(SDLK_s)) {
    if (isPressed(SDLK_a) || isPressed(SDLK_d)) {
      speed = SPEED * 0.7071;
    } // sqrt(2)/2
    player.setPosition(player.getPosition().x + cos(angle + PI) * speed,
                       player.getPosition().y + sin(angle + PI) * speed);
  }
  if (isPressed(SDLK_d)) {
    player.setPosition(player.getPosition().x + cos(angle + PI / 2) * speed,
                       player.getPosition().y + sin(angle + PI / 2) * speed);
  }
  // std::cout << speed << std::endl;
}

// NOTE: actual jumping by adjusting tile position on screen based on position!
void EventChecks::jump(UI &ui, Uint32 frameStart) {
  if (frameStart - jump_timer <= 300)
    // ui.setViewAngle(ui.getViewAngle() + (500 - (frameStart - jump_timer)) /
    // 25);
    ui.setJumpHeight(ui.getJumpHeight() -
                     (300 - (frameStart - jump_timer)) * 8);
  else if (frameStart - jump_timer > 300 && frameStart - jump_timer < 600)
    // else if (initial_height < ui.getViewHeight())
    // ui.setViewAngle(ui.getViewAngle() - (frameStart - jump_timer - 500) /
    // 25);
    ui.setJumpHeight(ui.getJumpHeight() + (frameStart - jump_timer - 300) * 8);
  else if (ui.getJumpHeight() < 0)
    ui.setJumpHeight(ui.getJumpHeight() + (frameStart - jump_timer - 300) * 8);
  // else if (ui.getJumpHeight() > 0)
  //     ui.setJumpHeight(0);
  else if (frameStart - jump_timer > 600)
    is_jumping = false;
  // std::cout << ui.getJumpHeight() << std::endl;
}

//         std::cout << event_ptr->key.repeat;

//             if (event_ptr->key.keysym.scancode == SDL_SCANCODE_UP)
//                 {
//                     movement.up = 1;
//                 }

//                 if (event_ptr->key.keysym.scancode == SDL_SCANCODE_DOWN)
//                 {
//                     movement.down = 1;
//                 }

//                 if (event_ptr->key.keysym.scancode == SDL_SCANCODE_LEFT)
//                 {
//                     movement.left = 1;
//                 }

//                 if (event_ptr->key.keysym.scancode == SDL_SCANCODE_RIGHT)
//                 {
//                     movement.right = 1;
//                 }
//         } else {
//             switch (event_ptr->key.keysym.sym)
//             {
//                 case SDLK_ESCAPE:
//                     quit = true;
//                     break;
//                 case SDLK_SPACE:
//                     pause = !pause;
//                     break;
//                 default:
//                     break;
//             }
//         }
// 	} else if (event_ptr->type == SDL_KEYUP){
//         if (event_ptr->key.keysym.scancode == SDL_SCANCODE_UP)
//         {
//             movement.up = 0;
//         }

//         if (event_ptr->key.keysym.scancode == SDL_SCANCODE_DOWN)
//         {
//             movement.down = 0;
//         }

//         if (event_ptr->key.keysym.scancode == SDL_SCANCODE_LEFT)
//         {
//             movement.left = 0;
//         }

//         if (event_ptr->key.keysym.scancode == SDL_SCANCODE_RIGHT)
//         {
//             movement.right = 0;
//         }
// 			break;
//     }

//     }
// }
