#include "Piece.h"
#include "DrawManager.h"
#include "GameManager.h"

Piece::Piece()
{
}
Piece::Piece(PieceChess type, SDL_Rect position, SDL_Surface* picture, ColorPiece color)
{
	this->mType = type;
	this->mPosition = position;
	this->mPicture = picture;
	this->mColor = color;
	this->mWidth = position.w;
	this->mHeight = position.h;
}

Piece::~Piece()
{
}

void Piece::initRange()
{
	this->mRange.clear();
	if (this->mType == PieceChess::Pawn)
	{
		RangeStatue statue;
		bool stopRange = false;
		if (this->mColor == ColorPiece::White)
		{
			if ((this->addRangeRect({ this->mPosition.x, this->mPosition.y - this->mHeight, this->mWidth, this->mHeight }, true)) == (RangeStatue::InEnnmyPiece))
			{
				this->mRange.pop_back();
				stopRange = true;
			}
			if (!this->hasMoved() && !stopRange)
				if ((this->addRangeRect({ this->mPosition.x, this->mPosition.y - 2 * this->mHeight, this->mWidth, this->mHeight }, true)) == (RangeStatue::InEnnmyPiece))
					this->mRange.pop_back();

			statue = this->addRangeRect({ this->mPosition.x - this->mWidth, this->mPosition.y - this->mHeight, this->mWidth, this->mHeight }, true);
			if ((statue) != (RangeStatue::InEnnmyPiece) && (statue) != (RangeStatue::Out))
				this->mRange.pop_back();
			statue = this->addRangeRect({ this->mPosition.x + this->mWidth, this->mPosition.y - this->mHeight, this->mWidth, this->mHeight }, true);
			if ((statue) != (RangeStatue::InEnnmyPiece) && (statue) != (RangeStatue::Out))
				this->mRange.pop_back();
		}
		else if (this->mColor == ColorPiece::Black)
		{
			if ((this->addRangeRect({ this->mPosition.x, this->mPosition.y + this->mHeight, this->mWidth, this->mHeight }, true)) == (RangeStatue::InEnnmyPiece))
			{
				this->mRange.pop_back();
				stopRange = true;
			}
			if (!this->hasMoved() && !stopRange)
				if ((this->addRangeRect({ this->mPosition.x, this->mPosition.y + 2 * this->mHeight, this->mWidth, this->mHeight }, true)) == (RangeStatue::InEnnmyPiece))
					this->mRange.pop_back();
			if ((this->addRangeRect({ this->mPosition.x - this->mWidth, this->mPosition.y + this->mHeight, this->mWidth, this->mHeight }, true)) != (RangeStatue::InEnnmyPiece))
				this->mRange.pop_back();
			if ((this->addRangeRect({ this->mPosition.x + this->mWidth, this->mPosition.y + this->mHeight, this->mWidth, this->mHeight }, true)) != (RangeStatue::InEnnmyPiece))
				this->mRange.pop_back();
		}
		
	}
	else if (this->mType == PieceChess::Rook)
	{
		std::vector<bool> stopRange(4, false);
		for (int i = 1; i < 8; ++i)
		{
			if (!stopRange[0])
				if ((this->addRangeRect({ this->mPosition.x, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[0] = true;

			if (!stopRange[1])
				if ((this->addRangeRect({ this->mPosition.x, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[1] = true;
			
			if (!stopRange[2])
				if ((this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[2] = true;
			
			if (!stopRange[3])
				if ((this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[3] = true;
		}
	}
	else if (this->mType == PieceChess::Knight)
	{
		this->addRangeRect({ this->mPosition.x - this->mWidth, this->mPosition.y + 2 * this->mHeight, this->mWidth, this->mHeight }, false);
		this->addRangeRect({ this->mPosition.x + this->mWidth, this->mPosition.y + 2 * this->mHeight, this->mWidth, this->mHeight }, false);
		this->addRangeRect({ this->mPosition.x - this->mWidth, this->mPosition.y - 2 * this->mHeight, this->mWidth, this->mHeight }, false);
		this->addRangeRect({ this->mPosition.x + this->mWidth, this->mPosition.y - 2 * this->mHeight, this->mWidth, this->mHeight }, false);

		this->addRangeRect({ this->mPosition.x + 2 * this->mWidth, this->mPosition.y - this->mHeight, this->mWidth, this->mHeight }, false);
		this->addRangeRect({ this->mPosition.x + 2 * this->mWidth, this->mPosition.y + this->mHeight, this->mWidth, this->mHeight }, false);
		this->addRangeRect({ this->mPosition.x - 2 * this->mWidth, this->mPosition.y - this->mHeight, this->mWidth, this->mHeight }, false);
		this->addRangeRect({ this->mPosition.x - 2 * this->mWidth, this->mPosition.y + this->mHeight, this->mWidth, this->mHeight }, false);
		
	}
	else if (this->mType == PieceChess::Bishop)
	{
		std::vector<bool> stopRange(4, false);
		for (int i = 1; i < 8; ++i)
		{
			if (!stopRange[0])
				if ((this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[0] = true;

			if (!stopRange[1])
				if ((this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[1] = true;

			if (!stopRange[2])
				if ((this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[2] = true;

			if (!stopRange[3])
				if ((this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[3] = true;
		}
	}
	else if (this->mType == PieceChess::Queen)
	{
		std::vector<bool> stopRange(8, false);
		for (int i = 1; i < 8; ++i)
		{
			if (!stopRange[0])
				if ((this->addRangeRect({ this->mPosition.x, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[0] = true;

			if (!stopRange[1])
				if ((this->addRangeRect({ this->mPosition.x, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[1] = true;

			if (!stopRange[2])
				if ((this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[2] = true;

			if (!stopRange[3])
				if ((this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[3] = true;


			if (!stopRange[4])
				if ((this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[4] = true;

			if (!stopRange[5])
				if ((this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[5] = true;

			if (!stopRange[6])
				if ((this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[6] = true;

			if (!stopRange[7])
				if ((this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false)) == (RangeStatue::InPiece))
					stopRange[7] = true;
		}
	}
	else if (this->mType == PieceChess::King)
	{
		for (int i = 1; i < 2; ++i)
		{
			this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false);
			this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false);
			this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false);
			this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false);

			this->addRangeRect({ this->mPosition.x, this->mPosition.y + i * this->mHeight, this->mWidth, this->mHeight }, false);
			this->addRangeRect({ this->mPosition.x, this->mPosition.y - i * this->mHeight, this->mWidth, this->mHeight }, false);
			this->addRangeRect({ this->mPosition.x + i * this->mWidth, this->mPosition.y, this->mWidth, this->mHeight }, false);
			this->addRangeRect({ this->mPosition.x - i * this->mWidth, this->mPosition.y, this->mWidth, this->mHeight }, false);
		}
	}
}
RangeStatue Piece::addRangeRect(SDL_Rect rangeRect, bool force)
{
	map<std::string, Piece> whiteList = GAMEMANAGER.getPieceWhiteList();
	map<std::string, Piece> blackList = GAMEMANAGER.getPieceBlackList();
	SDL_Rect damierRect = GAMEMANAGER.getDamierRect();

	if (!SDL_HasIntersection(&damierRect, &rangeRect))
		return RangeStatue::Out;

	for (std::map<string, Piece>::iterator it = whiteList.begin(); it != whiteList.end(); ++it)
	{
		if (SDL_HasIntersection(&(it->second.mPosition), &rangeRect))
		{
			if (this->mColor == ColorPiece::White)
				return RangeStatue::InPiece;

			this->mRange.push_back(rangeRect);
			return (force) ? RangeStatue::InEnnmyPiece : RangeStatue::InPiece;
		}
			
	}
	for (std::map<string, Piece>::iterator it2 = blackList.begin(); it2 != blackList.end(); ++it2)
	{
		if (SDL_HasIntersection(&(it2->second.mPosition), &rangeRect))
		{
			if (this->mColor == ColorPiece::Black)
				return RangeStatue::InPiece;

			this->mRange.push_back(rangeRect);
			return (force) ? RangeStatue::InEnnmyPiece : RangeStatue::InPiece;
		}
	}

	this->mRange.push_back(rangeRect);
	return RangeStatue::Correct;
}
void Piece::drawPiece()
{
	DRAWMANAGER.drawTexture(this->mPicture, this->mPosition);
}
void Piece::setPosition(SDL_Rect position)
{
	this->mPosition.x = position.x;
	this->mPosition.y = position.y;
}
SDL_Rect Piece::getPosition()
{
	return this->mPosition;
}
void Piece::setHasMoved(bool value)
{
	this->mHasMoved = value;
}
bool Piece::hasMoved()
{
	return this->mHasMoved;
}
void Piece::drawRange(SDL_Color color)
{
	for (int i = 0; i < this->mRange.size(); ++i)
	{
		DRAWMANAGER.drawRect(this->mRange[i], color);
	}
}
bool Piece::isClicked(SDL_Rect mousePosition)
{
	return SDL_HasIntersection(&mousePosition, &(this->mPosition));
}
bool Piece::isClickedRange(SDL_Rect mousePosition)
{
	for (int i = 0; i < this->mRange.size(); ++i)
	{
		if (SDL_HasIntersection(&mousePosition, &mRange[i]))
		{
			GAMEMANAGER.setRectRangeSelected(mRange[i]);
			return true;
		}
			
	}
	return false ;
}
bool Piece::isIntersectRange(SDL_Rect rect)
{
	for (int i = 0; i < this->mRange.size(); ++i)
	{
		if (SDL_HasIntersection(&rect, &mRange[i]))
		{
			return true;
		}

	}
	return false;
}
void Piece::refreshRangePosition(SDL_Rect translation)
{
	for (int i = 0; i < this->mRange.size(); ++i)
	{
		this->mRange[i].x += translation.x;
		this->mRange[i].y += translation.y;
	}
}