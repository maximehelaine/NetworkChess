#include "Piece.h"
#include "DrawManager.h"

Piece::Piece()
{
}
Piece::Piece(PieceChess type, SDL_Rect position, SDL_Surface* picture)
{
	this->mType = type;
	this->mPosition = position;
	this->mPicture = picture;
}

Piece::~Piece()
{
}


void Piece::drawPiece()
{
	DRAWMANAGER.drawTexture(this->mPicture, this->mPosition);
}
void Piece::setPosition(SDL_Rect position)
{
	this->mPosition = position;
}
void Piece::showRange(SDL_Color color, std::vector<Piece>)
{

}
bool Piece::isClicked(SDL_Rect mousePosition)
{
	return false;
}
void Piece::refreshRangePosition()
{

}