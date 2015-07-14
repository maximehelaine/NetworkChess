#include <stdio.h>
#include <stdlib.h>

#include "DrawManager.h"
#include "SoundManager.h"

static DrawManager& DRAWMANAGER = DrawManager::Instance();
static SoundManager& SOUNDMANAGER = SoundManager::Instance();

void pause();
void drawTexture(SDL_Window* pWindow, std::string path, float x, float y, float h, float w);
int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
    }
	
	/* Création de la fenêtre */
	
	DRAWMANAGER.initWindow("Chess", 680, 480);
	DRAWMANAGER.initRenderer();
	SOUNDMANAGER.initFMOD();

	if (DRAWMANAGER.getWindow())
	{
		DRAWMANAGER.addImage("WallPaperPrincipal", "src/img/Capture.bmp");
		DRAWMANAGER.drawTexture("WallPaperPrincipal", 0, 0);
		DRAWMANAGER.render();
		pause();
		SDL_DestroyWindow(DRAWMANAGER.getWindow());
		//DRAWMANAGER.freeImages();
		DRAWMANAGER.freeRenderer();
		SOUNDMANAGER.freeFMOD();
	}
	else
	{
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
	}

    SDL_Quit();

    return EXIT_SUCCESS;
}
void pause()
{
	int continuer = 1;
	SDL_Event event;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
		}
	}
}

