#pragma once

#ifndef X_TECH_CONTROLLERCODE_H
#define X_TECH_CONTROLLERCODE_H

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL.h>

namespace xTech
{
    enum ControllerButton
    {
        CONTROLLER_BUTTON_A = 0,
        CONTROLLER_BUTTON_B,
        CONTROLLER_BUTTON_X,
        CONTROLLER_BUTTON_Y,

        CONTROLLER_BUTTON_LSHOULDER,
        CONTROLLER_BUTTON_RSHOULDER,

        CONTROLLER_BUTTON_BACK,
        CONTROLLER_BUTTON_START,

        CONTROLLER_BUTTON_LSTICK,
        CONTROLLER_BUTTON_RSTICK,
    };
}

#endif