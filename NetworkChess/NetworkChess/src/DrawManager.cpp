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
	SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 0, 255);
}
void DrawManager::freeRenderer()
{
	SDL_DestroyRenderer(this->mRenderer); // Libération de la mémoire du SDL_Renderer
}
void DrawManager::freeImages()
{
	for (std::map<string, SDL_Surface*>::iterator it = this->mImageList.begin(); it != this->mImageList.end(); ++it)
	{
		SDL_FreeSurface(it->second); // Libération de la ressource occupée par le sprite
	}
	this->mImageList.clear();
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
}


SDL_Window* DrawManager::getWindow()
{
	return this->mWindow;
}
SDL_Surface* DrawManager::getSurface(string name)
{
	return this->mImageList[name];
}
SDL_Rect* DrawManager::getRect(string name)
{
	return this->mRectList[name];
}
string DrawManager::getNameTextureClicked(const SDL_Rect mousePosition)
{
	for (std::map<string, SDL_Rect*>::iterator it = this->mRectList.begin(); it != this->mRectList.end(); ++it)
	{
		if (SDL_HasIntersection(&mousePosition, it->second))
			return it->first;
		
	}
	return "None";
}
void DrawManager::addImage(string name, string imagePath)
{
	this->mImageList[name] = IMG_Load(imagePath.c_str());
}
void DrawManager::addText(string name, string text, TTF_Font* font, SDL_Color color)
{
	this->mImageList[name] = TTF_RenderText_Solid(font, text.c_str(), color);
}
void DrawManager::render()
{
	SDL_RenderPresent(this->mRenderer); // Affichage
}
void DrawManager::clear(SDL_Color color)
{
	// Clear the entire screen to our selected color.
	SDL_SetRenderDrawColor(this->mRenderer, color.r, color.g, color.b, 255);
	SDL_RenderClear(this->mRenderer);
}
void DrawManager::drawTexture(string nameImage, int x, int y, int w, int h)
{
	if (this->mRenderer)
	{
		if (this->mImageList[nameImage])
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(this->mRenderer, this->mImageList[nameImage]); // Préparation du sprite
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
void DrawManager::drawTexture(string nameImage, int x, int y)
{
	if (this->mRenderer)
	{
		if (this->mImageList[nameImage])
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(this->mRenderer, this->mImageList[nameImage]); // Préparation du sprite
			if (pTexture)
			{
				SDL_Rect dest = { x, y, this->mImageList[nameImage]->w, this->mImageList[nameImage]->h };
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
void DrawManager::drawTexture(string nameObject, string nameImage, int x, int y)
{
	if (this->mRenderer)
	{
		if (this->mImageList[nameImage])
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(this->mRenderer, this->mImageList[nameImage]); // Préparation du sprite
			if (pTexture)
			{
				SDL_Rect* dest = new SDL_Rect({ x, y, this->mImageList[nameImage]->w, this->mImageList[nameImage]->h });
				this->mRectList[nameObject] = dest;
				SDL_RenderCopy(this->mRenderer, pTexture, NULL, dest); // Copie du sprite grâce au SDL_Renderer
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
void DrawManager::drawTexture(string nameObject, string nameImage, int x, int y, int w, int h)
{
	if (this->mRenderer)
	{
		if (this->mImageList[nameImage])
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(this->mRenderer, this->mImageList[nameImage]); // Préparation du sprite
			if (pTexture)
			{
				SDL_Rect* dest = new SDL_Rect({ x, y, w, h });
				this->mRectList[nameObject] = dest;
				SDL_RenderCopy(this->mRenderer, pTexture, NULL, dest); // Copie du sprite grâce au SDL_Renderer
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
void DrawManager::drawTexture(SDL_Surface* picture, SDL_Rect position)
{
	if (this->mRenderer)
	{
		if (picture)
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(this->mRenderer, picture); // Préparation du sprite
			if (pTexture)
			{
				SDL_RenderCopy(this->mRenderer, pTexture, NULL, &position); // Copie du sprite grâce au SDL_Renderer
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
void DrawManager::drawText(string input, int x, int y, TTF_Font* font, SDL_Color color)
{
	if (this->mRenderer)
	{
		SDL_Surface* pSprite = TTF_RenderText_Solid(font, input.c_str(), color);
		if (pSprite)
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(this->mRenderer, pSprite); // Préparation du sprite
			if (pTexture)
			{
				SDL_Rect dest = { x, y, pSprite->clip_rect.w, pSprite->clip_rect.h };
				SDL_RenderCopy(this->mRenderer, pTexture, NULL, &dest); // Copie du sprite grâce au SDL_Renderer

				SDL_RenderPresent(this->mRenderer); // Affichage
				SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture
			}
			else
			{
				fprintf(stdout, "Échec de création du Text (%s)\n", SDL_GetError());
			}

			SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite
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
void DrawManager::drawInputText(string text, string fieldTexture , string fieldPos, TTF_Font* font, SDL_Color color)
{
	this->drawTexture(fieldTexture, this->mRectList[fieldPos]->x, this->mRectList[fieldPos]->y, this->mRectList[fieldPos]->w, this->mRectList[fieldPos]->h);
	this->drawText(text, this->mRectList[fieldPos]->x, this->mRectList[fieldPos]->y, TTF_OpenFont("src/fonts/arial.ttf", 24), { 0, 0, 0 });
}
void DrawManager::drawRect(SDL_Rect rect, SDL_Color color)
{
	// Set render color to blue ( rect will be rendered in this color )
	SDL_SetRenderDrawColor(this->mRenderer, color.r, color.g, color.b, color.a);

	// Render rect
	SDL_RenderFillRect(this->mRenderer, &rect);
}
//1er appel de Instance: on alloue le pointeur DrawManager::m_instance
//DrawManager& ptr1 = DrawManager::Instance();

