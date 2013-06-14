#include "GameViewFrame.h"

#include "GameField.h"
#include "Sprite.h"
#include "SpriteProvider.h"

GameViewFrame::GameViewFrame(
	GameField&				aField, 
	SDL_Surface*			aScreen, 
	float					aPixelsPerMeter, 
	const Position&			aLeftBottom)
	: myField(aField)
	, myScreen(aScreen)
	, myPixelsPerMeter(aPixelsPerMeter)
	, myLeftBottom(aLeftBottom)
{
}

void
GameViewFrame::setPosition(const Position& aLeftBottom)
{
	myLeftBottom = aLeftBottom;
}

void
GameViewFrame::render()
{
	defineRenderRange();
	for (int row = myRenderRange.topRow; row >= myRenderRange.bottomRow; --row)
	{
		for (int col = myRenderRange.leftColumn; col <= myRenderRange.rightColumn; ++col)
		{
			CellPosition pos(row, col);
			SurfaceElement surface = myField.getCellSurface(pos);
			Position p = myField.cellPositionToCoord(pos);
			Sprite& sprite = SpriteProvider::getInstance().getSpriteForSurface(sufrace);
			Position screenPos = fieldToScreen(p);
			sprite->renderAt(screenPos);
		}
	}
}

void
GameViewFrame::defineRenderRange()
{
	CellPosition leftBottomCell = myField.getNearestCell(myLeftBottom);
	myScreen.h
}

Position
GameViewFrame::fieldToScreen(const Position& aPosition)
{
}