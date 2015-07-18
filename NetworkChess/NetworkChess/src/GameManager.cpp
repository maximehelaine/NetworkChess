#include "GameManager.h"
#include "DrawManager.h"
using namespace std;

GameManager GameManager::m_instance = GameManager();

GameManager::GameManager()
{
	cout << "Creation GameManager" << endl;
}

GameManager::~GameManager()
{
	cout << "Destruction GameManager" << endl;
}

GameManager& GameManager::Instance()
{
	return m_instance;
}
void GameManager::initPositionPiece(int w, int h, int offsetX, int offsetY)
{
	for (int i = 0; i < 8; ++i)
	{
		this->addBlackPiece("PawnBlack" + std::to_string(i), Piece(PieceChess::Pawn, { (i * w) + offsetX, h + offsetY, w, h }, DRAWMANAGER.getSurface("PawnBlack"), ColorPiece::Black));
		this->addWhitePiece("PawnWhite" + std::to_string(i), Piece(PieceChess::Pawn, { (i * w) + offsetX, 6 * h + offsetY, w, h }, DRAWMANAGER.getSurface("PawnWhite"), ColorPiece::White));
		switch (i)
		{
		case 0:
			this->addBlackPiece("RookBlack0", Piece(PieceChess::Rook, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("RookBlack"), ColorPiece::Black));
			this->addWhitePiece("RookWhite0", Piece(PieceChess::Rook, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("RookWhite"), ColorPiece::White));
			break;
		case 1:
			this->addBlackPiece("KnightBlack0", Piece(PieceChess::Knight, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("KnightBlack"), ColorPiece::Black));
			this->addWhitePiece("KnightWhite0", Piece(PieceChess::Knight, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("KnightWhite"), ColorPiece::White));
			break;
		case 2:
			this->addBlackPiece("BishopBlack0", Piece(PieceChess::Bishop, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("BishopBlack"), ColorPiece::Black));
			this->addWhitePiece("BishopWhite0", Piece(PieceChess::Bishop, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("BishopWhite"), ColorPiece::White));
			break;
		case 3:
			this->addBlackPiece("KingBlack0", Piece(PieceChess::King, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("KingBlack"), ColorPiece::Black));
			this->addWhitePiece("KingWhite0", Piece(PieceChess::King, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("KingWhite"), ColorPiece::White));
			break;
		case 4:
			this->addBlackPiece("QueenBlack0", Piece(PieceChess::Queen, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("QueenBlack"), ColorPiece::Black));
			this->addWhitePiece("QueenWhite0", Piece(PieceChess::Queen, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("QueenWhite"), ColorPiece::White));
			break;
		case 5:
			this->addBlackPiece("BishopBlack1", Piece(PieceChess::Bishop, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("BishopBlack"), ColorPiece::Black));
			this->addWhitePiece("BishopWhite1", Piece(PieceChess::Bishop, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("BishopWhite"), ColorPiece::White));
			break;
		case 6:
			this->addBlackPiece("KnightBlack1", Piece(PieceChess::Knight, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("KnightBlack"), ColorPiece::Black));
			this->addWhitePiece("KnightWhite1", Piece(PieceChess::Knight, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("KnightWhite"), ColorPiece::White));
			break;
		case 7:
			this->addBlackPiece("RookBlack1", Piece(PieceChess::Rook, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("RookBlack"), ColorPiece::Black));
			this->addWhitePiece("RookWhite1", Piece(PieceChess::Rook, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("RookWhite"), ColorPiece::White));
			break;
		}
	}
	this->initRangePieces();
}
void GameManager::initRangePieces()
{
	for (std::map<string, Piece>::iterator it = this->mPieceWhiteList.begin(); it != this->mPieceWhiteList.end(); ++it)
	{
		(it->second).initRange();
	}
	for (std::map<string, Piece>::iterator it = this->mPieceBlackList.begin(); it != this->mPieceBlackList.end(); ++it)
	{
		(it->second).initRange();
	}
	
}

void GameManager::clear()
{
	this->mColor = ColorClient::None;
	this->mType = TypeClient::None;
	this->mTurn = false;
	this->mStart = false;
	this->mFinish = false;
	this->mPieceBlackList.clear();
	this->mPieceWhiteList.clear();
	this->mSelectedPiece = "";
}

void GameManager::switchTurn()
{
	this->mSelectedPiece = "";
	this->mTurn = !this->mTurn;
	GAMEMANAGER.setNeedUpdateDisplay(true);
}
void GameManager::setStart(bool value)
{
	this->mStart = value;
}
bool GameManager::isStart()
{
	return this->mStart;
}
void GameManager::setFinish(bool value)
{
	this->mFinish = value;
}
bool GameManager::isFinish()
{
	return this->mFinish;
}
void GameManager::setCheck(bool value)
{
	this->mCheck = value;
}
bool GameManager::isCheck()
{
	return this->mCheck;
}
bool GameManager::isMyTurn()
{
	return this->mTurn;
}
void GameManager::setColor(ColorClient color)
{
	this->mColor = color;
}
void GameManager::setType(TypeClient type)
{
	this->mType = type;
}
void GameManager::setDamierRect(SDL_Rect rect)
{
	this->mDamierRect = rect;
}
void GameManager::setRectRangeSelected(SDL_Rect rect)
{
	this->mRectRangeSelected = rect;
}
bool GameManager::setPositionByName(string name, ColorClient color, SDL_Rect rect)
{
	int windowsW = SDL_GetWindowSurface(DRAWMANAGER.getWindow())->w;
	int windowsH = SDL_GetWindowSurface(DRAWMANAGER.getWindow())->h;
	EchecMath test;
	if (color == ColorClient::White)
	{
		SDL_Rect old_rect = this->mPieceWhiteList[name].getPosition();
		this->mPieceWhiteList[name].setPosition(rect);
		this->mPieceWhiteList[name].setHasMoved(true);
		if (GAMEMANAGER.getTypeClient() == TypeClient::Spectator)
			return true;
		//ICI envoyé position et nom  au reste des clients
		for (std::map<string, Piece>::iterator it = this->mPieceBlackList.begin(); it != this->mPieceBlackList.end(); ++it)
		{
			if (SDL_HasIntersection(&(it->second.getPosition()), &rect))
			{
				Piece old_piece(it->second);
				string old_name = it->first;
				it = this->mPieceBlackList.erase(it);
				
				this->initRangePieces();
				test = GAMEMANAGER.isEchecMath(GAMEMANAGER.getColorClient());
				if (test != EchecMath::Echec)
				{
					this->mCheck = false;
					return true;
				}

				if (color == GAMEMANAGER.getColorClient()) //tester type client
				{
					this->mPieceWhiteList[name].setPosition(old_rect);
					this->addBlackPiece(old_name, old_piece);
					this->initRangePieces();

					return false;
				}
				else
				{
					this->mCheck = true;
				}
				return true;
			}
		}
		this->initRangePieces();
		test = GAMEMANAGER.isEchecMath(GAMEMANAGER.getColorClient());
		if (test != EchecMath::Echec)
		{
			this->mCheck = false;
			return true;
		}

		if (color == GAMEMANAGER.getColorClient()) //tester type client
		{
			this->mPieceWhiteList[name].setPosition(old_rect);
			this->initRangePieces();
			return false;
		}
		else
		{
			this->mCheck = true;
		}
	}	
	else if (color == ColorClient::Black)
	{
		SDL_Rect old_rect = this->mPieceBlackList[name].getPosition();
		this->mPieceBlackList[name].setPosition(rect);
		this->mPieceBlackList[name].setHasMoved(true);
		if (GAMEMANAGER.getTypeClient() == TypeClient::Spectator)
			return true;
		//ICI envoyé position et nom au reste des clients
		for (std::map<string, Piece>::iterator it = this->mPieceWhiteList.begin(); it != this->mPieceWhiteList.end(); ++it)
		{
			if (SDL_HasIntersection(&(it->second.getPosition()), &rect))
			{
				Piece old_piece(it->second);
				string old_name = it->first;
				it = this->mPieceWhiteList.erase(it);
				this->initRangePieces();
				test = GAMEMANAGER.isEchecMath(GAMEMANAGER.getColorClient());
				if (test != EchecMath::Echec)
				{
					this->mCheck = false;
					return true;
				}
					
				if (color == GAMEMANAGER.getColorClient()) //tester type client
				{
					this->mPieceBlackList[name].setPosition(old_rect);
					this->addWhitePiece(old_name, old_piece);
					this->initRangePieces();

					return false;
				}
				else
				{
					this->mCheck = true;
				}
				return true;
			}
		}
		this->initRangePieces();
		test = GAMEMANAGER.isEchecMath(GAMEMANAGER.getColorClient());
		if (test != EchecMath::Echec)
		{
			this->mCheck = false;
			return true;
		}

		if (color == GAMEMANAGER.getColorClient()) //tester type client
		{
			this->mPieceBlackList[name].setPosition(old_rect);
			this->initRangePieces();

			return false;
		}
		else
		{
			this->mCheck = true;
		}
	}

	return true;
}
map<std::string, Piece> GameManager::getPieceWhiteList()
{
	return this->mPieceWhiteList;
}
map<std::string, Piece> GameManager::getPieceBlackList()
{
	return this->mPieceBlackList;
}
SDL_Rect GameManager::getDamierRect()
{
	return this->mDamierRect;
}
Piece GameManager::getSelectedPiece()
{
	if (this->mColor == ColorClient::White)
		return this->mPieceWhiteList[mSelectedPiece];
	else if (this->mColor == ColorClient::Black)
		return this->mPieceBlackList[mSelectedPiece];
}
std::string GameManager::getSelectedPieceName()
{
	return this->mSelectedPiece;
}
ColorClient GameManager::getColorClient()
{
	return this->mColor;
}
TypeClient GameManager::getTypeClient()
{
	return this->mType;
}
SDL_Rect GameManager::getRectRangeSelected()
{
	return this->mRectRangeSelected;
}
void GameManager::addBlackPiece(string name, Piece piece)
{
	this->mPieceBlackList[name] = piece;
}
void GameManager::addWhitePiece(string name, Piece piece)
{
	this->mPieceWhiteList[name] = piece;
}
void GameManager::displayPieces()
{
	for (std::map<string, Piece>::iterator it = this->mPieceWhiteList.begin(); it != this->mPieceWhiteList.end(); ++it)
	{
		it->second.drawPiece();
	}
	for (std::map<string, Piece>::iterator it2 = this->mPieceBlackList.begin(); it2 != this->mPieceBlackList.end(); ++it2)
	{
		it2->second.drawPiece();
	}
}
bool GameManager::clickedpiece(SDL_Rect mousePosition)
{
	bool clicked = false;
	if (this->mColor == ColorClient::White)
	{
		for (std::map<string, Piece>::iterator it = this->mPieceWhiteList.begin(); it != this->mPieceWhiteList.end(); ++it)
		{
			clicked = it->second.isClicked(mousePosition);
			if (clicked)
			{
				this->mSelectedPiece = it->first;
				return clicked;
			}
		}
	}
	else if (this->mColor == ColorClient::Black)
	{
		for (std::map<string, Piece>::iterator it = this->mPieceBlackList.begin(); it != this->mPieceBlackList.end(); ++it)
		{
			clicked = it->second.isClicked(mousePosition);
			if (clicked)
			{
				this->mSelectedPiece = it->first;
				return clicked;
			}
		}
	}

	return clicked;
}
bool GameManager::needUpdateDipslay()
{
	return this->mNeedUpdateDisplay;
}
void GameManager::setNeedUpdateDisplay(bool value)
{
	this->mNeedUpdateDisplay = value;
}
EchecMath GameManager::isEchecMath(ColorClient color)
{
	if (color == ColorClient::Black)
	{
		for (std::map<string, Piece>::iterator it = this->mPieceWhiteList.begin(); it != this->mPieceWhiteList.end(); ++it)
		{
			if ((it->second.isIntersectRange(this->mPieceBlackList["KingBlack0"].getPosition())))
				return EchecMath::Echec;
		}
	}
	else if (color == ColorClient::White)
	{
		for (std::map<string, Piece>::iterator it = this->mPieceBlackList.begin(); it != this->mPieceBlackList.end(); ++it)
		{
			if ((it->second.isIntersectRange(this->mPieceWhiteList["KingWhite0"].getPosition())))
				return EchecMath::Echec;
		}
	}

}