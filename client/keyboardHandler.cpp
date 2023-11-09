#include "keyboardHandler.h"

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "Action.h"

KBHandler::KBHandler(Queue<std::shared_ptr<Action>>& actionQ, std::atomic<bool>& quit):
        action_queue(actionQ), quit(quit) {}

void KBHandler::run() {
    SDL_Event e;
    while (not quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;

            } else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                switch (e.key.keysym.sym) {

                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    case SDLK_LEFT:
                        this->action_queue.push(std::make_shared<StartMoving>(Direction::LEFT));
                        break;

                    case SDLK_RIGHT:
                        this->action_queue.push(std::make_shared<StartMoving>(Direction::RIGHT));
                        break;

                    case SDLK_RETURN:
                        this->action_queue.push(std::make_shared<Jump>(JumpDir::FRONT));
                        break;

                    case SDLK_BACKSPACE:
                        this->action_queue.push(std::make_shared<Jump>(JumpDir::BACK));
                        break;


                    // Fight
                    case SDLK_UP:
                        this->action_queue.push(std::make_shared<ADSAngle>(ADSAngleDir::UP));
                        break;

                    case SDLK_DOWN:
                        this->action_queue.push(std::make_shared<ADSAngle>(ADSAngleDir::DOWN));
                        break;

                    case SDLK_SPACE:
                        this->action_queue.push(std::make_shared<FirePower>());
                        break;

                    case SDLK_1:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::ONE));
                        break;

                    case SDLK_2:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::TWO));
                        break;

                    case SDLK_3:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::THREE));
                        break;

                    case SDLK_4:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::FOUR));
                        break;

                    case SDLK_5:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::FIVE));
                        break;

                    case SDLK_F1:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::BAZOOKA));
                        break;

                    case SDLK_F2:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::MORTAR));
                        break;

                    case SDLK_F3:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::GREEN_GRENADE));
                        break;

                    case SDLK_F4:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::RED_GRANADE));
                        break;

                    case SDLK_F5:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::BANANA));
                        break;

                    case SDLK_F6:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::HOLY_GRENADE));
                        break;

                    case SDLK_F7:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::DYNAMITE));
                        break;

                    case SDLK_F8:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::BASEBALL_BAT));
                        break;

                    case SDLK_F9:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::AIR_STRIKE));
                        break;

                    case SDLK_F10:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::TELEPORT));
                        break;

                    // ---------- LOBBY ------------
                    case SDLK_c:
                        this->action_queue.push(std::make_shared<CreateGame>());
                        break;

                    case SDLK_j:
                        this->action_queue.push(
                                std::make_shared<JoinGame>(0));  // PLACE HOLDER DE GAME ID
                        break;

                    case SDLK_r:
                        this->action_queue.push(std::make_shared<Ready>());
                        break;

                    default:
                        break;
                }

            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        this->action_queue.push(std::make_shared<StopMoving>());
                        break;

                    case SDLK_RIGHT:
                        this->action_queue.push(std::make_shared<StopMoving>());
                        break;

                    case SDLK_SPACE:
                        this->action_queue.push(std::make_shared<Shoot>());
                        break;

                    case SDLK_UP:
                        this->action_queue.push(std::make_shared<StopADSAngle>());
                        break;

                    case SDLK_DOWN:
                        this->action_queue.push(std::make_shared<StopADSAngle>());
                        break;

                    default:
                        break;
                }
            }
        }
    }
}