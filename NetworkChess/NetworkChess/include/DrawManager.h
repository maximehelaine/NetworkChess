#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "SDL/SDL.h"

using namespace std;

class DrawManager
{
public:
	static DrawManager& Instance();
	void initWindow(string name, int w, int h);
	void initRenderer();
	void freeRenderer();
	//void freeImages();
	//void freeImage(string name);
	/*setter*/
	/*getter*/
	SDL_Window* getWindow();
	/*Add*/
	void addImage(string name, string imagePath);

	void render();
	void drawTexture(string path, int x, int y, int w, int h);
	void drawTexture(string path, int x, int y);

private:
	DrawManager& operator= (const DrawManager&){}
	DrawManager(const DrawManager&){}

	static DrawManager m_instance;
	DrawManager();
	~DrawManager();

	SDL_Window* mWindow = NULL;
	SDL_Renderer *mRenderer = NULL;

	map <string, SDL_Surface*> mImageList;
};
#endif
