#include "GameViewFrame.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

#include "GameField.h"
#include "Sprite.h"
#include "SpriteProvider.h"

namespace ublas = boost::numeric::ublas;

GameViewFrame::GameViewFrame(
	GameField&				aField,
	SDL_Surface*			aScreen,
	float					aPixelsPerMeter,
	const FloatPosition&	aLeftTop)
	: myField(aField)
	, myScreen(aScreen)
	, myPixelsPerMeter(aPixelsPerMeter)
	, myLeftTop(aLeftTop)
{
    createTransformationMatrixes();
}

void
GameViewFrame::setPosition(const FloatPosition& aLeftTop)
{
	myLeftTop = aLeftTop;
    createTransformationMatrixes();
}

void
GameViewFrame::render(SDL_Surface* aSurface)
{
	//defineRenderRange();
	CellPosition leftTopCell = myField.getNearestCell(myLeftTop);
	Position screenPos;
    CellPosition cellPos;
	cellPos.row = leftTopCell.row;
	do
	{
	    cellPos.col = leftTopCell.col;
	    do
	    {
	        FloatPosition fieldPos = myField.cellPositionToCoord(cellPos);
	        SurfaceElement surface = myField.getCellSurface(cellPos);
			SharedPtr(Sprite) sprite = SpriteProvider::getInstance().getSpriteForSurface(surface);
			screenPos = fieldToScreen(fieldPos);
			sprite->renderTo(myScreen, screenPos);

			cellPos.col++;
	    }
	    while (screenPos.x < myScreen->w && cellPos.col < myField.width());

	    cellPos.row++;
	}
	while (screenPos.y < myScreen->h && cellPos.row < myField.height());
    /*
	for (int row = myRenderRange.topRow; row >= myRenderRange.bottomRow; --row)
	{
		for (int col = myRenderRange.leftColumn; col <= myRenderRange.rightColumn; ++col)
		{
			CellPosition pos(row, col);
			SurfaceElement surface = myField.getCellSurface(pos);
			FloatPosition p = myField.cellPositionToCoord(pos);
			SharedPtr(Sprite) sprite = SpriteProvider::getInstance().getSpriteForSurface(surface);
			Position screenPos = fieldToScreen(p);
			sprite->renderTo(aSurface, screenPos);
		}
	}*/
}

void
GameViewFrame::defineRenderRange()
{
	CellPosition leftTopCell = myField.getNearestCell(myLeftTop);

}

Position
GameViewFrame::fieldToScreen(const FloatPosition& aPosition)
{
    ublas::vector<float> pos(3);
    pos(0) = aPosition.x;
    pos(1) = aPosition.y;
    pos(2) = 1;

    ublas::vector<float> screenPos = ublas::prod(myFieldToScreenMatrix, pos);

    return Position(static_cast<int>(screenPos(0)), static_cast<int>(screenPos(1)));
}

void
GameViewFrame::createTransformationMatrixes()
{
    ublas::matrix<float> translation = ublas::identity_matrix<float>(3);
    translation(0, 2) = -myLeftTop.x;
    translation(1, 2) = -myLeftTop.y;
	std::cout << "translation:\n" << translation << std::endl;
    ublas::matrix<float> scale = ublas::identity_matrix<float>(3);
    scale(0, 0) = myPixelsPerMeter;
    scale(1, 1) = myPixelsPerMeter / 2;
	std::cout << "scale:\n" << scale << std::endl;

    myFieldToScreenMatrix = ublas::prod(scale, translation);
}
