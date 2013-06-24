#pragma once

#include <vector>
#include <exception>
#include <istream>

#include "BasicStructs.h"
#include "Surface.h"

class GameField
{
public:
    struct  FieldCell {
        FieldCell();
        FieldCell(const std::string& aSurface, const std::string& aObject);

        std::string     surface;
        std::string     object;
    };

                        GameField(int aWidth, int aHeight, float aCellDiagonal);
                        GameField(const std::string& aMapFileName);
                        GameField(std::istream& aIn);
	//SurfaceElement	getSurfaceAt(int aCellX, int aCellY);
	//void			getSurfaceCellsInRect(const Rect& aTargetRect, std::vector<SurfaceElement> aCells);

	FloatPosition	    cellPositionToCoord(const CellPosition& aPosition);
	CellPosition	    cellCoordToPosition(const FloatPosition& aPosition);
	CellPosition	    getNearestCell(const FloatPosition& aPosition);
	SurfaceElement	    getCellSurface(const CellPosition& aPosition);
	const FieldCell&    getCell(const CellPosition& aPosition);
	int                 height() const;
	int                 width() const;

	//SharedPtr(GameField)    readFromFile(const std::string& fileName);

private:
    void                populateFromStream(std::istream& in);

	int											myWidth;
	int											myHeight;
	float										myCellDiagonal;
	std::vector<std::vector<SurfaceElement> >	mySurface;
	std::vector<std::vector<FieldCell> >        myCells;

#ifdef __TEST__
    friend class GameFieldTester;
#endif
};

#ifdef __TEST__
    Size readSize(const std::string& str);
    GameField::FieldCell readCell(const std::string& str);
#endif
