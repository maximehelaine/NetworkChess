#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {

    }



    SDL_Quit();

    return EXIT_SUCCESS;
}