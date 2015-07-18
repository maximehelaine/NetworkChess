#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "SDL/SDL.h"
#include "Piece.h"

using namespace std;

enum class TypeClient { None, Player, Spectator };
enum class ColorClient { None, White, Black };
enum class EchecMath { None, Echec, Math };

class GameManager
{
public:
	static GameManager& Instance();
	void initPositionPiece(int w, int h, int offsetX, int offsetY);
	void initRangePieces();
	void clear();
	void switchTurn();
	void setStart(bool value);
	bool isStart();
	void setFinish(bool value);
	bool isFinish();
	bool isMyTurn();
	bool isCheck();
	void setCheck(bool value);
	bool needUpdateDipslay();
	void setNeedUpdateDisplay(bool value);
	void setColor(ColorClient color);
	void setType(TypeClient type);
	void setDamierRect(SDL_Rect rect);
	void setRectRangeSelected(SDL_Rect rect);
	bool setPositionByName(string name, ColorClient color, SDL_Rect rect);

	map<std::string, Piece> getPieceWhiteList();
	map<std::string, Piece> getPieceBlackList();
	SDL_Rect getDamierRect();
	Piece getSelectedPiece();
	std::string getSelectedPieceName();
	SDL_Rect getRectRangeSelected();
	ColorClient getColorClient();
	TypeClient getTypeClient();
	void addBlackPiece(string name, Piece piece);
	void addWhitePiece(string name, Piece piece);
	void displayPieces();
	bool clickedpiece(SDL_Rect mousePosition);
	EchecMath isEchecMath(ColorClient color);
	
private:
	GameManager& operator= (const GameManager&){}
	GameManager(const GameManager&){}

	static GameManager m_instance;
	GameManager();
	~GameManager();

	map<std::string, Piece> mPieceWhiteList;
	map<std::string, Piece> mPieceBlackList;
	bool mTurn = false;
	bool mStart = false;
	bool mFinish = false;
	bool mCheck = false;
	bool mNeedUpdateDisplay = false;
	TypeClient mType = TypeClient::None;
	ColorClient mColor = ColorClient::None;
	std::string mSelectedPiece;
	SDL_Rect mRectRangeSelected;
	SDL_Rect mDamierRect;

};

static GameManager& GAMEMANAGER = GameManager::Instance();
#endif