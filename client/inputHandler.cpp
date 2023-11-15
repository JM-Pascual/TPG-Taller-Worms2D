#include "inputHandler.h"

#include <memory>

#include "Action.h"
#include "camera.h"

IHandler::IHandler(Queue<std::shared_ptr<Action>>& actionQ, std::atomic<bool>& quit,
                   std::atomic<bool>& my_turn, Camera& camera):
        action_queue(actionQ), quit(quit), my_turn(my_turn), camera(camera) {}

void IHandler::run() {
    SDL_Event event;
    bool kb_priority = false;

    while (not quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;

            } else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                kb_priority = true;
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    default:
                        keyDown(event.key.keysym.sym);
                        break;
                }

            } else if (event.type == SDL_KEYUP) {
                kb_priority = false;
                keyUp(event.key.keysym.sym);

            } else if (not kb_priority) {
                if (event.type == SDL_MOUSEMOTION) {
                    camera.fixMouse(event.motion.x, event.motion.y);

                } else if (event.type == SDL_MOUSEBUTTONDOWN) {

                } else if (event.type == SDL_MOUSEBUTTONUP) {

                } else if (event.type == SDL_MOUSEWHEEL_FLIPPED) {
                }
            }
        }
    }
}

void IHandler::keyUp(const SDL_Keycode& key) {
    if (not my_turn) {
        return;
    }

    switch (key) {
        case SDLK_LEFT:
            this->action_queue.push(std::make_shared<StopMoving>());
            return;

        case SDLK_RIGHT:
            this->action_queue.push(std::make_shared<StopMoving>());
            return;

        case SDLK_SPACE:
            this->action_queue.push(std::make_shared<Shoot>());
            return;

        case SDLK_UP:
            this->action_queue.push(std::make_shared<StopADSAngle>());
            return;

        case SDLK_DOWN:
            this->action_queue.push(std::make_shared<StopADSAngle>());
            return;

        default:
            return;
    }
}

void IHandler::keyDown(const SDL_Keycode& key) {
    if (not my_turn) {
        return;
    }

    switch (key) {
        case SDLK_LEFT:
            this->action_queue.push(std::make_shared<StartMoving>(Direction::LEFT));
            return;

        case SDLK_RIGHT:
            this->action_queue.push(std::make_shared<StartMoving>(Direction::RIGHT));
            return;

        case SDLK_RETURN:
            this->action_queue.push(std::make_shared<Jump>(JumpDir::FRONT));
            return;

        case SDLK_BACKSPACE:
            this->action_queue.push(std::make_shared<Jump>(JumpDir::BACK));
            return;


        // Fight
        case SDLK_UP:
            this->action_queue.push(std::make_shared<ADSAngle>(ADSAngleDir::UP));
            return;

        case SDLK_DOWN:
            this->action_queue.push(std::make_shared<ADSAngle>(ADSAngleDir::DOWN));
            return;

        case SDLK_SPACE:
            this->action_queue.push(std::make_shared<FirePower>());
            return;

        case SDLK_1:
            this->action_queue.push(std::make_shared<Delay>(DelayAmount::ONE));
            return;

        case SDLK_2:
            this->action_queue.push(std::make_shared<Delay>(DelayAmount::TWO));
            return;

        case SDLK_3:
            this->action_queue.push(std::make_shared<Delay>(DelayAmount::THREE));
            return;

        case SDLK_4:
            this->action_queue.push(std::make_shared<Delay>(DelayAmount::FOUR));
            return;

        case SDLK_5:
            this->action_queue.push(std::make_shared<Delay>(DelayAmount::FIVE));
            return;

        case SDLK_F1:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::BAZOOKA));
            return;

        case SDLK_F2:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::MORTAR));
            return;

        case SDLK_F3:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::GREEN_GRENADE));
            return;

        case SDLK_F4:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::RED_GRENADE));
            return;

        case SDLK_F5:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::BANANA));
            return;

        case SDLK_F6:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::HOLY_GRENADE));
            return;

        case SDLK_F7:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::DYNAMITE));
            return;

        case SDLK_F8:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::BASEBALL_BAT));
            return;

        case SDLK_F9:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::AIR_STRIKE));
            return;

        case SDLK_F10:
            this->action_queue.push(std::make_shared<ChangeGadget>(WeaponsAndTools::TELEPORT));
            return;

        default:
            return;
    }
}
