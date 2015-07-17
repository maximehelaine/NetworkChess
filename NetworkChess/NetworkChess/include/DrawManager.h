#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
using namespace std;

class DrawManager
{
public:
	static DrawManager& Instance();
	void initWindow(string name, int w, int h);
	void initRenderer();
	void freeRenderer();
	void freeImages();
	void freeImage(string name);
	/*setter*/
	/*getter*/
	SDL_Window* getWindow();
	SDL_Surface* getSurface(string name);
	SDL_Rect* DrawManager::getRect(string name);
	string getNameTextureClicked(const SDL_Rect);
	/*Add*/
	void addImage(string name, string imagePath);
	void addText(string name, string text, TTF_Font* font, SDL_Color color);

	void render();
	void clear();
	void drawTexture(string nameImage, int x, int y, int w, int h);
	void drawTexture(string nameImage, int x, int y);
	void drawTexture(string nameObject, string nameImage, int x, int y, int w, int h);
	void drawTexture(string nameObject, string nameImage, int x, int y);
	void drawTexture(SDL_Surface* picture, SDL_Rect position);
	void drawText(string input, int x, int y, TTF_Font* font, SDL_Color color);
	void drawInputText(string text, string fieldTexture, string fieldPos, TTF_Font* font, SDL_Color color);
	void drawRect(SDL_Rect rect, SDL_Color color);

private:
	DrawManager& operator= (const DrawManager&){}
	DrawManager(const DrawManager&){}

	static DrawManager m_instance;
	DrawManager();
	~DrawManager();

	SDL_Window* mWindow = NULL;
	SDL_Renderer *mRenderer = NULL;

	map <string, SDL_Surface*> mImageList;
	map <string, SDL_Rect*> mRectList;
};

static DrawManager& DRAWMANAGER = DrawManager::Instance();

#endif
