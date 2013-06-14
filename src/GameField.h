#pragma once

#include <vector>

#include "BasicStructs.h"
#include "Surface.h"

class GameField
{
public:
					GameField(int aWidth, int aHeight, float aCellDiagonal);
	//SurfaceElement	getSurfaceAt(int aCellX, int aCellY);
	//void			getSurfaceCellsInRect(const Rect& aTargetRect, std::vector<SurfaceElement> aCells);
	
	FloatPosition	cellPositionToCoord(const CellPosition& aPosition);
	CellPosition	cellCoordToPosition(const FloatPosition& aPosition);
	CellPosition	getNearestCell(const FloatPosition& aPosition);
	SurfaceElement	getCellSurface(const CellPosition& aPosition);

private:
	int											myWidth;
	int											myHeight;
	float										myCellDiagonal;
	std::vector<std::vector<SurfaceElement> >	mySurface;
};
