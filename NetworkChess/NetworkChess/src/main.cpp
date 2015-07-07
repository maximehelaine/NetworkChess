#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#include "fmod.h"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {

    }

    FMOD_SYSTEM* sys;

    FMOD_System_Create(&sys);
    FMOD_System_Init(sys, 2, FMOD_INIT_NORMAL, nullptr);

    FMOD_System_Close(sys);
    FMOD_System_Release(sys);

    SDL_Quit();

    return EXIT_SUCCESS;
}