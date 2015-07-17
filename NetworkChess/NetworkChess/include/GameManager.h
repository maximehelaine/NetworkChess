#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#include <iostream>
#include <string>
#include <vector>

#include "SDL/SDL.h"
#include "Piece.h"

using namespace std;

enum class TypeClient { Player, Spectator };
enum class ColorClient { None, White, Black };

class GameManager
{
public:
	static GameManager& Instance();
	void initPositionPiece(int w, int h, int offsetX, int offsetY);
	void switchTurn();
	void setStart(bool value);
	bool isStart();
	void setColor(ColorClient color);
	void setType(TypeClient type);
	void addBlackPiece(Piece piece);
	void addWhitePiece(Piece piece);
	void displayPieces();
	
private:
	GameManager& operator= (const GameManager&){}
	GameManager(const GameManager&){}

	static GameManager m_instance;
	GameManager();
	~GameManager();

	vector<Piece> mPieceWhiteList;
	vector<Piece> mPieceBlackList;
	bool mTurn = false;
	bool mStart = false;
	TypeClient mType = TypeClient::Player;
	ColorClient mColor = ColorClient::None;

};

static GameManager& GAMEMANAGER = GameManager::Instance();
#endif