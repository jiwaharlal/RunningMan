#include "GameField.h"

GameField::GameField(int aWidth, int aHeight, float aCellDiagonal)
	: myWidth(aWidth)
	, myHeight(aHeight)
	, myCellDiagonal(aCellDiagonal)
{
}

Point GameField::cellPositionToCoord(const CellPosition& aPosition)
{
	Point p;
	p.x = (aPosition.col * 2 + aPosition.row % 2) / 2.0f * myCellDiagonal ;
	p.y = aPosition.row * myCellDiagonal / 2.0f;

	return p;
}
	
CellPosition GameField::cellCoordToPosition(const Point& aPoint)
{
	CellPosition pos;
	
	pos.row = (aPoint.y * 2.0f) / myCellDiagonal;
	pos.col = (aPoint.x / myCellDiagonal * 2.0f - pos.row % 2) / 2;

	return pos;
}

CellPosition GameField::getNearestCell(const Point& aPoint)
{
	float rowInterpolation = (aPoint.y * 2.0f) / myCellDiagonal;
	float colInterpolation = (aPoint.x / myCellDiagonal * 2.0f - static_cast<int>(floor(rowInterpolation + 0.5)) % 2) / 2;

	CellPosition pos(static_cast<int>(rowInterpolation), static_cast<int>(colInterpolation));
	if (rowInterpolation - static_cast<float>(pos.row) > 0.5f) {
		pos.row += 1;
	}
	if (colInterpolation - static_cast<float>(pos.col) > 0.5f) {
		pos.col += 1;
	}
	
	return pos;
}

SurfaceElement	GameField::getCellSurface(const CellPosition& aPosition)
{
	return Surface_Sand;
}
