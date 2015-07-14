#include "DrawManager.h"

DrawManager DrawManager::m_instance = DrawManager();

DrawManager::DrawManager()
{
	cout << "Creation DrawManager" << endl;
}

DrawManager::~DrawManager()
{
	cout << "Destruction DrawManager" << endl;
}

DrawManager& DrawManager::Instance()
{
	return m_instance;
}
void DrawManager::initWindow(string name, int w, int h)
{
	this->mWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		w,
		h,
		SDL_WINDOW_SHOWN);
}
void DrawManager::initRenderer()
{
	this->mRenderer = SDL_CreateRenderer(this->mWindow, -1, SDL_RENDERER_ACCELERATED); // Création d'un SDL_Renderer utilisant l'accélération matérielle
}
void DrawManager::freeRenderer()
{
	SDL_DestroyRenderer(this->mRenderer); // Libération de la mémoire du SDL_Renderer
}
/*void DrawManager::freeImages()
{
	for (std::map<string, SDL_Surface*>::iterator it = this->mImageList.begin(); it != this->mImageList.end(); ++it)
	{
		SDL_FreeSurface(it->second); // Libération de la ressource occupée par le sprite
		it = this->mImageList.erase(it);
	}
}
void DrawManager::freeImage(string name)
{
	for (std::map<string, SDL_Surface*>::iterator it = this->mImageList.begin(); it != this->mImageList.end(); ++it)
	{
		if (name == it->first)
		{
			SDL_FreeSurface(it->second); // Libération de la ressource occupée par le sprite
			it = this->mImageList.erase(it);
			return;
		}
	}
}*/


SDL_Window* DrawManager::getWindow()
{
	return this->mWindow;
}
void DrawManager::addImage(string name, string imagePath)
{
	this->mImageList[name] = SDL_LoadBMP(imagePath.c_str());
}

void DrawManager::render()
{
	SDL_RenderPresent(this->mRenderer); // Affichage
}
void DrawManager::drawTexture(string name, int x, int y, int w, int h)
{
	if (this->mRenderer)
	{
		if (this->mImageList[name])
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(this->mRenderer, this->mImageList[name]); // Préparation du sprite
			if (pTexture)
			{
				SDL_Rect dest = { x, y, w, h };
				SDL_RenderCopy(this->mRenderer, pTexture, NULL, &dest); // Copie du sprite grâce au SDL_Renderer
				SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture
			}
			else
			{
				fprintf(stdout, "Échec de création de la texture (%s)\n", SDL_GetError());
			}
		}
		else
		{
			fprintf(stdout, "Échec de chargement du sprite (%s)\n", SDL_GetError());
		}
	}
	else
	{
		fprintf(stdout, "Échec de création du renderer (%s)\n", SDL_GetError());
	}
}
void DrawManager::drawTexture(string name, int x, int y)
{
	if (this->mRenderer)
	{
		if (this->mImageList[name])
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(this->mRenderer, this->mImageList[name]); // Préparation du sprite
			if (pTexture)
			{
				SDL_Rect dest = { x, y, this->mImageList[name]->w, this->mImageList[name]->h };
				SDL_RenderCopy(this->mRenderer, pTexture, NULL, &dest); // Copie du sprite grâce au SDL_Renderer
				SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture
			}
			else
			{
				fprintf(stdout, "Échec de création de la texture (%s)\n", SDL_GetError());
			}
		}
		else
		{
			fprintf(stdout, "Échec de chargement du sprite (%s)\n", SDL_GetError());
		}
	}
	else
	{
		fprintf(stdout, "Échec de création du renderer (%s)\n", SDL_GetError());
	}
}
//1er appel de Instance: on alloue le pointeur DrawManager::m_instance
//DrawManager& ptr1 = DrawManager::Instance();
