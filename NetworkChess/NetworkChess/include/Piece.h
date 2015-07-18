#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "SDL/SDL.h"

enum class PieceChess { Pawn, Rook, Knight, Bishop, Queen, King };
enum class RangeStatue { Out, InPiece, Correct, InEnnmyPiece };
enum class ColorPiece { None, White, Black };

class Piece
{
public:
	Piece();
	Piece(PieceChess type, SDL_Rect position, SDL_Surface* picture, ColorPiece color);
	~Piece();
	
	void drawPiece();
	void setPosition(SDL_Rect position);
	void setHasMoved(bool value);
	bool hasMoved();
	SDL_Rect getPosition();
	void drawRange(SDL_Color color);
	bool isClicked(SDL_Rect mousePosition);
	bool isClickedRange(SDL_Rect mousePosition);
	bool isIntersectRange(SDL_Rect rect);
	void initRange();


private:
	void refreshRangePosition(SDL_Rect translation);
	RangeStatue addRangeRect(SDL_Rect rangeRect, bool force);
	PieceChess mType;
	SDL_Rect mPosition;
	SDL_Surface* mPicture;
	ColorPiece mColor;
	int mWidth;
	int mHeight;
	bool mHasMoved = false;
	std::vector<SDL_Rect> mRange;
	std::vector<SDL_Rect> mRangeVisible;
};

