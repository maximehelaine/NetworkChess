#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <WinSock2.h>

#include "DrawManager.h"
#include "SoundManager.h"
#include "MessageManager.h"
#include "GameManager.h"


void drawBackGroundMenuPrincipal();
void drawInteractiveMenuPrincipal();
void drawLevel();
void drawDamier(int w, int h, int nbBoxX, int nbBoxY, int offsetX, int offsetY);
void principalLoop();
int menuLoop();
int gameLoop();

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
    }
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		fprintf(stdout,"SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
	/* Création de la fenêtre */
	
	DRAWMANAGER.initWindow("Chess", WINDOW_WIDTH, WINDOW_HEIGHT);
	DRAWMANAGER.initRenderer();
	SOUNDMANAGER.initFMOD();
	
	if (DRAWMANAGER.getWindow())
	{
		DRAWMANAGER.addImage("WallPaperPrincipal", "src/img/chessWallPaper.bmp");
		//DRAWMANAGER.addImage("EchecDamier", "src/img/EchecDamier.bmp");
		DRAWMANAGER.addImage("InputField", "src/img/inputField.bmp");

		DRAWMANAGER.addImage("PawnWhite", "src/img/PawnWhite.png");
		DRAWMANAGER.addImage("RookWhite", "src/img/RookWhite.png");
		DRAWMANAGER.addImage("KnightWhite", "src/img/KnightWhite.png");
		DRAWMANAGER.addImage("BishopWhite", "src/img/BishopWhite.png");
		DRAWMANAGER.addImage("QueenWhite", "src/img/QueenWhite.png");
		DRAWMANAGER.addImage("KingWhite", "src/img/KingWhite.png");

		DRAWMANAGER.addImage("PawnBlack", "src/img/PawnBlack.png");
		DRAWMANAGER.addImage("RookBlack", "src/img/RookBlack.png");
		DRAWMANAGER.addImage("KnightBlack", "src/img/KnightBlack.png");
		DRAWMANAGER.addImage("BishopBlack", "src/img/BishopBlack.png");
		DRAWMANAGER.addImage("QueenBlack", "src/img/QueenBlack.png");
		DRAWMANAGER.addImage("KingBlack", "src/img/KingBlack.png");

		DRAWMANAGER.addText("ClientButton", "Client v1.0", TTF_OpenFont("src/fonts/arial.ttf", 72), { 0, 0, 0 });
		DRAWMANAGER.addText("Connexion", "Connexion", TTF_OpenFont("src/fonts/arial.ttf", 72), { 0, 0, 0 });
		DRAWMANAGER.addText("AbandonButton", "Abandon", TTF_OpenFont("src/fonts/arial.ttf", 72), { 255, 255,255 });
		DRAWMANAGER.addText("TurnMessage", "Your Turn", TTF_OpenFont("src/fonts/arial.ttf", 72), { 255, 255, 255 });
		DRAWMANAGER.addText("CheckMessage", "Winter is Comming", TTF_OpenFont("src/fonts/arial.ttf", 72), { 255, 255, 255 });

		GAMEMANAGER.setDamierRect({ WINDOW_WIDTH / 2 - (WINDOW_HEIGHT * 80 / 100) / 2, WINDOW_HEIGHT / 2 - (WINDOW_HEIGHT * 80 / 100) / 2, 8 * WINDOW_HEIGHT / 10, 8 * WINDOW_HEIGHT / 10 });

		principalLoop();

		SDL_DestroyWindow(DRAWMANAGER.getWindow());
		DRAWMANAGER.freeImages();
		DRAWMANAGER.freeRenderer();
		SOUNDMANAGER.freeFMOD();
	}
	else
	{
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
	}
	MESSAGEMANAGER.close();
	TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
void drawBackGroundMenuPrincipal()
{
	//Dessin du menu principal
	int windowsW = SDL_GetWindowSurface(DRAWMANAGER.getWindow())->w;
	int windowsH = SDL_GetWindowSurface(DRAWMANAGER.getWindow())->h;
	DRAWMANAGER.drawTexture("WallPaperPrincipal", 0, 0, windowsW, windowsH);
	DRAWMANAGER.drawTexture("ClientButton", (windowsW / 5) - (DRAWMANAGER.getSurface("ClientButton")->w)/2, windowsH * 90/100, 100, 25);
	DRAWMANAGER.drawTexture("PseudoFieldPos", "InputField", (windowsW / 2) - 100, (windowsH / 9) * 5 - 25, 200, 50);
	DRAWMANAGER.drawTexture("IpFieldPos", "InputField", (windowsW / 2) - 100, DRAWMANAGER.getRect("PseudoFieldPos")->y + 60, 200, 50);
	DRAWMANAGER.drawTexture("PortFieldPos", "InputField", (windowsW / 2) - 100, DRAWMANAGER.getRect("IpFieldPos")->y + 60, 200, 50);
	DRAWMANAGER.drawTexture("ConnexionPos", "Connexion", (windowsW * 80 / 100) - 100, DRAWMANAGER.getRect("PseudoFieldPos")->y + 60, 200, 50);
}
void drawLevel()
{
	//Draw du Level
	int windowsW = SDL_GetWindowSurface(DRAWMANAGER.getWindow())->w;
	int windowsH = SDL_GetWindowSurface(DRAWMANAGER.getWindow())->h;

	//DrawDamier
	drawDamier(windowsH / 10, windowsH / 10, 7, 7, windowsW / 2 - (windowsH * 80 / 100) / 2, windowsH / 2 - (windowsH * 80 / 100) / 2);
	DRAWMANAGER.drawTexture("AbandonPos", "AbandonButton", (windowsW * 85 / 100) - 100, windowsH / 2 - 25, 200, 50);
	if (GAMEMANAGER.isMyTurn() && GAMEMANAGER.getTypeClient() != TypeClient::Spectator)
		DRAWMANAGER.drawTexture("TurnMessage", (windowsW * 15 / 100) - 100, windowsH / 2 - 25, 200, 50);
	if (GAMEMANAGER.isCheck())
		DRAWMANAGER.drawTexture("CheckMessage", (windowsW * 50 / 100) - 100, (windowsH * 5 / 100) - 25, 200, 50);
	//SDL_Surface* pSprite = DRAWMANAGER.getSurface("EchecDamier");
	//DRAWMANAGER.drawTexture("EchecDamier", windowsW / 2 - (windowsH * 80 / 100) / 2, windowsH / 2 - (windowsH * 80 / 100) / 2, (windowsH * 80 / 100), (windowsH * 80 / 100));
}
void drawDamier(int w, int h, int nbBoxX, int nbBoxY, int offsetX, int offsetY)
{
	for (int i = 0; i <= nbBoxY; i++)
	{
		for (int j = 0; j <= nbBoxX; j++)
		{
			SDL_Rect rec = { (j * w) + offsetX, (i * h) + offsetY, w, h };
			if ((i+j) == 0 || (i + j) % 2 == 0)
			{
				DRAWMANAGER.drawRect(rec, { 0, 0, 0 });
			}
			else
			{
				DRAWMANAGER.drawRect(rec, { 255, 255, 255 });
			}
		}
	}
}
void principalLoop()
{
	int response = 0;
	while (response!=-1)
	{
		response = menuLoop();
		if (response != -1)
			response = gameLoop();
	}
}
int menuLoop()
{
	
	drawBackGroundMenuPrincipal();
	DRAWMANAGER.render();

	string pseudoText;
	string ipText;
	string portText;
	string textureNameClicked = "";
	int continuer = 1;
	SDL_Event event;
	string surfaceNameClicked;
	SDL_Rect mousePosition;
	bool isconnected = false;
	while (continuer && (!GAMEMANAGER.isStart()))
	{
		while (SDL_PollEvent(&event)) // Nous traitons les événements de la queue
		{
			switch (event.type)
			{
				case SDL_MOUSEBUTTONUP:
					mousePosition = { event.button.x, event.button.y, 1, 1 };
					surfaceNameClicked = DRAWMANAGER.getNameTextureClicked(mousePosition);
					if (surfaceNameClicked == "ConnexionPos" && !isconnected)
					{
						
						if (pseudoText.size() == 0 || ipText.size() == 0 || portText.size() == 0)
							break;

						cout << "Run Client" << endl;
						MESSAGEMANAGER.connect(pseudoText, ipText, stoi(portText));
						
						if (MESSAGEMANAGER.isConnected())
						{

							cout << "Connected" << endl;
							isconnected = MESSAGEMANAGER.isConnected();
						}
						else
						{
							cout << "Probleme Connexion" << endl;
						}
							
					}
					
					/*fprintf(stdout, "Un appuie sur un bouton de la souris :\n");
					fprintf(stdout, "\tfenêtre : %d\n", event.button.windowID);
					fprintf(stdout, "\tsouris : %d\n", event.button.which);
					fprintf(stdout, "\tbouton : %d\n", event.button.button);
					#if SDL_VERSION_ATLEAST(2,0,2)
					fprintf(stdout, "\tclics : %d\n", event.button.clicks);
					#endif
					fprintf(stdout, "\tposition : %d;%d\n", event.button.x, event.button.y);*/
					break;
					
				case SDL_KEYUP:
					if (event.key.keysym.scancode == 42)
					{
						if (surfaceNameClicked == "PseudoFieldPos" && pseudoText.size() != 0)
						{
							pseudoText.pop_back();
							DRAWMANAGER.drawInputText(pseudoText, "InputField", "PseudoFieldPos", TTF_OpenFont("src/fonts/arial.ttf", 24), { 0, 0, 0 });
						}
						else if (surfaceNameClicked == "IpFieldPos" && ipText.size() != 0)
						{
							ipText.pop_back();
							DRAWMANAGER.drawInputText(ipText, "InputField", "IpFieldPos", TTF_OpenFont("src/fonts/arial.ttf", 24), { 0, 0, 0 });
						}
						else if (surfaceNameClicked == "PortFieldPos" && portText.size() != 0)
						{
							portText.pop_back();
							DRAWMANAGER.drawInputText(portText, "InputField", "PortFieldPos", TTF_OpenFont("src/fonts/arial.ttf", 24), { 0, 0, 0 });
						}
						DRAWMANAGER.render();
					}
					break;
				case SDL_TEXTINPUT:
					/* Add new text onto the end of our text */
					if (surfaceNameClicked == "PseudoFieldPos")
					{
						pseudoText += event.text.text;
						DRAWMANAGER.drawInputText(pseudoText, "InputField", "PseudoFieldPos", TTF_OpenFont("src/fonts/arial.ttf", 24), { 0, 0, 0 });
					}
					else if (surfaceNameClicked == "IpFieldPos")
					{
						ipText += event.text.text;
						DRAWMANAGER.drawInputText(ipText, "InputField", "IpFieldPos", TTF_OpenFont("src/fonts/arial.ttf", 24), { 0, 0, 0 });
					}
					else if (surfaceNameClicked == "PortFieldPos")
					{
						portText += event.text.text;
						DRAWMANAGER.drawInputText(portText, "InputField", "PortFieldPos", TTF_OpenFont("src/fonts/arial.ttf", 24), { 0, 0, 0 });
					}
					DRAWMANAGER.render();
					break;
				case SDL_QUIT:
					continuer = 0;
					return -1;
			}
		}
		
	}
	return 0;
}

int gameLoop()
{
	int windowsW = SDL_GetWindowSurface(DRAWMANAGER.getWindow())->w;
	int windowsH = SDL_GetWindowSurface(DRAWMANAGER.getWindow())->h;
	DRAWMANAGER.clear({ 0, 0, 0, 255 });
	drawLevel();
	GAMEMANAGER.displayPieces();
	DRAWMANAGER.render();
	int continuer = 1;
	SDL_Event event;
	SDL_Rect mousePosition;
	bool isShowRange = false;
	string surfaceNameClicked;
	while (continuer && MESSAGEMANAGER.isConnected())
	{
		while (SDL_PollEvent(&event)) // Nous traitons les événements de la queue
		{
			switch (event.type)
			{
			case SDL_MOUSEBUTTONUP:
				if (GAMEMANAGER.getTypeClient() != TypeClient::Player)
					break;
				mousePosition = { event.button.x, event.button.y, 1, 1 };
				surfaceNameClicked = DRAWMANAGER.getNameTextureClicked(mousePosition);
				if (surfaceNameClicked == "AbandonPos")
				{
					GAMEMANAGER.setFinish(true);
					MESSAGEMANAGER.send("Finish");
					break;
				}
				if (!GAMEMANAGER.isMyTurn())
					break;
				DRAWMANAGER.clear({ 0, 0, 0, 255 });
				drawLevel();
				if (GAMEMANAGER.clickedpiece(mousePosition))
				{
					GAMEMANAGER.getSelectedPiece().drawRange({ 0, 255, 0, 127 });
					isShowRange = true;
				}
				else if (isShowRange && GAMEMANAGER.getSelectedPiece().isClickedRange(mousePosition))
				{
					if (GAMEMANAGER.setPositionByName(GAMEMANAGER.getSelectedPieceName(), GAMEMANAGER.getColorClient(), GAMEMANAGER.getRectRangeSelected()))
					{
						MESSAGEMANAGER.send("Move " + GAMEMANAGER.getSelectedPieceName() + " " + std::to_string(static_cast<int>(GAMEMANAGER.getColorClient())) + " " + std::to_string(GAMEMANAGER.getRectRangeSelected().x) + " " + std::to_string(GAMEMANAGER.getRectRangeSelected().y) + " " + std::to_string(GAMEMANAGER.getRectRangeSelected().w) + " " + std::to_string(GAMEMANAGER.getRectRangeSelected().h) + " SwitchTurn");
						GAMEMANAGER.switchTurn();
					}
						
					isShowRange = false;
				}
				else
				{
					isShowRange = false;
				}
				GAMEMANAGER.displayPieces();
				DRAWMANAGER.render();
				break;
			case SDL_QUIT:
				GAMEMANAGER.clear();
				MESSAGEMANAGER.send("Finish");
				MESSAGEMANAGER.close();
				return -1;
			}
		}
		if (GAMEMANAGER.needUpdateDipslay())
		{
			DRAWMANAGER.clear({ 0, 0, 0, 255 });
			drawLevel();
			GAMEMANAGER.displayPieces();
			DRAWMANAGER.render();
			GAMEMANAGER.setNeedUpdateDisplay(false);
		}
		if (GAMEMANAGER.isFinish())
		{
			GAMEMANAGER.clear();
			MESSAGEMANAGER.close();
			DRAWMANAGER.clear({ 0, 0, 0, 255 });
			return 0;
		}
	} 
	return 0;
}

