#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "SDL/SDL.h"

enum class PieceChess { Pawn, Rook, Knight, Bishop, Queen, King };

class Piece
{
public:
	Piece();
	Piece(PieceChess type, SDL_Rect position, SDL_Surface* picture);
	~Piece();
	void drawPiece();
	void setPosition(SDL_Rect position);
	void showRange(SDL_Color color, std::vector<Piece>);
	bool isClicked(SDL_Rect mousePosition);


private:
	void refreshRangePosition();

	PieceChess mType;
	SDL_Rect mPosition;
	SDL_Surface* mPicture;
	std::vector<SDL_Rect*> mRange;
};

