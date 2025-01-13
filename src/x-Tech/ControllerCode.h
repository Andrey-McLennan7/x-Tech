#pragma once

#ifndef X_TECH_CONTROLLERCODE_H
#define X_TECH_CONTROLLERCODE_H

#include <SDL2/SDL_gamecontroller.h>

namespace xTech
{
    enum ControllerButton
    {
        CONTROLLER_BUTTON_INV = SDL_CONTROLLER_BUTTON_INVALID,

        CONTROLLER_BUTTON_A = SDL_CONTROLLER_BUTTON_A,
        CONTROLLER_BUTTON_B = SDL_CONTROLLER_BUTTON_B,
        CONTROLLER_BUTTON_X = SDL_CONTROLLER_BUTTON_X,
        CONTROLLER_BUTTON_Y = SDL_CONTROLLER_BUTTON_Y,

        CONTROLLER_BUTTON_BACK = SDL_CONTROLLER_BUTTON_BACK,
        CONTROLLER_BUTTON_GUIDE = SDL_CONTROLLER_BUTTON_GUIDE,
        CONTROLLER_BUTTON_START = SDL_CONTROLLER_BUTTON_START,

        CONTROLLER_BUTTON_LSTICK = SDL_CONTROLLER_BUTTON_LEFTSTICK,
        CONTROLLER_BUTTON_RSTICK = SDL_CONTROLLER_BUTTON_RIGHTSTICK,

        CONTROLLER_BUTTON_LSHOULDER = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        CONTROLLER_BUTTON_RSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,

        CONTROLLER_BUTTON_DPAD_UP = SDL_CONTROLLER_BUTTON_DPAD_UP,
        CONTROLLER_BUTTON_DPAD_DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        CONTROLLER_BUTTON_DPAD_LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        CONTROLLER_BUTTON_DPAD_RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,

        CONTROLLER_BUTTON_MISC1 = SDL_CONTROLLER_BUTTON_MISC1,

        CONTROLLER_BUTTON_PADDLE1 = SDL_CONTROLLER_BUTTON_PADDLE1,
        CONTROLLER_BUTTON_PADDLE2 = SDL_CONTROLLER_BUTTON_PADDLE2,
        CONTROLLER_BUTTON_PADDLE3 = SDL_CONTROLLER_BUTTON_PADDLE3,
        CONTROLLER_BUTTON_PADDLE4 = SDL_CONTROLLER_BUTTON_PADDLE4,

        CONTROLLER_BUTTON_TOUCHPAD = SDL_CONTROLLER_BUTTON_TOUCHPAD,

        CONTROLLER_BUTTON_MAX = SDL_CONTROLLER_BUTTON_MAX
    };
}

#endif