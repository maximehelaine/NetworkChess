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
		this->addBlackPiece(Piece(PieceChess::Pawn, { (i * w) + offsetX, h + offsetY, w, h }, DRAWMANAGER.getSurface("PawnBlack")));
		this->addWhitePiece(Piece(PieceChess::Pawn, { (i * w) + offsetX, 6 * h + offsetY, w, h }, DRAWMANAGER.getSurface("PawnWhite")));
		switch (i)
		{
		case 0:
			this->addBlackPiece(Piece(PieceChess::Rook, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("RookBlack")));
			this->addWhitePiece(Piece(PieceChess::Rook, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("RookWhite")));
			break;
		case 1:
			this->addBlackPiece(Piece(PieceChess::Knight, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("KnightBlack")));
			this->addWhitePiece(Piece(PieceChess::Knight, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("KnightWhite")));
			break;
		case 2:
			this->addBlackPiece(Piece(PieceChess::Bishop, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("BishopBlack")));
			this->addWhitePiece(Piece(PieceChess::Bishop, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("BishopWhite")));
			break;
		case 3:
			this->addBlackPiece(Piece(PieceChess::King, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("KingBlack")));
			this->addWhitePiece(Piece(PieceChess::King, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("KingWhite")));
			break;
		case 4:
			this->addBlackPiece(Piece(PieceChess::Queen, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("QueenBlack")));
			this->addWhitePiece(Piece(PieceChess::Queen, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("QueenWhite")));
			break;
		case 5:
			this->addBlackPiece(Piece(PieceChess::Bishop, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("BishopBlack")));
			this->addWhitePiece(Piece(PieceChess::Bishop, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("BishopWhite")));
			break;
		case 6:
			this->addBlackPiece(Piece(PieceChess::Knight, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("KnightBlack")));
			this->addWhitePiece(Piece(PieceChess::Knight, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("KnightWhite")));
			break;
		case 7:
			this->addBlackPiece(Piece(PieceChess::Rook, { (i * w) + offsetX, offsetY, w, h }, DRAWMANAGER.getSurface("RookBlack")));
			this->addWhitePiece(Piece(PieceChess::Rook, { (i * w) + offsetX, 7 * h + offsetY, w, h }, DRAWMANAGER.getSurface("RookWhite")));
			break;
		}
	}
}
void GameManager::switchTurn()
{
	this->mTurn = !this->mTurn;
}
void GameManager::setStart(bool value)
{
	this->mStart = value;
}
bool GameManager::isStart()
{
	return this->mStart;
}
void GameManager::setColor(ColorClient color)
{
	this->mColor = color;
}
void GameManager::setType(TypeClient type)
{
	this->mType = type;
}
void GameManager::addBlackPiece(Piece piece)
{
	this->mPieceBlackList.push_back(piece);
}
void GameManager::addWhitePiece(Piece piece)
{
	this->mPieceWhiteList.push_back(piece);
}
void GameManager::displayPieces()
{
	for (int i = 0; i < this->mPieceWhiteList.size(); ++i)
	{
		this->mPieceWhiteList[i].drawPiece();
		this->mPieceBlackList[i].drawPiece();
	}
}
