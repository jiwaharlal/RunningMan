#include "GameViewFrame.h"

#include <boost/shared_ptr.hpp>

#include "GameField.h"
#include "Sprite.h"
#include "SpriteProvider.h"

GameViewFrame::GameViewFrame(
	GameField&				aField,
	SDL_Surface*			aScreen,
	float					aPixelsPerMeter,
	const FloatPosition&	aLeftBottom)
	: myField(aField)
	, myScreen(aScreen)
	, myPixelsPerMeter(aPixelsPerMeter)
	, myLeftBottom(aLeftBottom)
{
}

void
GameViewFrame::setPosition(const FloatPosition& aLeftBottom)
{
	myLeftBottom = aLeftBottom;
}

void
GameViewFrame::render(SDL_Surface* aSurface)
{
	defineRenderRange();
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
	}
}

void
GameViewFrame::defineRenderRange()
{
	CellPosition leftBottomCell = myField.getNearestCell(myLeftBottom);
}

Position
GameViewFrame::fieldToScreen(const FloatPosition& aPosition)
{
}
