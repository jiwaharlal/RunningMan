#pragma once

#include "BasicStructs.h"
#include <vector>

enum SurfaceElement 
{
	Surface_Emptyness = 0,
	Surface_Grass = 1,
	Surface_Soil = 2,
	Surface_Sand = 3
};

class GameField
{
public:
					GameField(int aWidth, int aHeight, float aCellDiagonal);
	//SurfaceElement	getSurfaceAt(int aCellX, int aCellY);
	//void			getSurfaceCellsInRect(const Rect& aTargetRect, std::vector<SurfaceElement> aCells);
	
	Point			cellPositionToCoord(const CellPosition aPosition);
	CellPosition	cellCoordToPosition(const Point& aPoint);
	CellPosition	getNearestCell(const Point& aPoint);

private:
	int											myWidth;
	int											myHeight;
	float										myCellDiagonal;
	std::vector<std::vector<SurfaceElement> >	mySurface;
};
