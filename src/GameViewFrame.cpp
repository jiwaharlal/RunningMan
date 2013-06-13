#include "GameVeiwFrame.h"

GameViewFrame::GameViewFrame(
	GameField&				aField, 
	SDL_Surface*			aScreen, 
	float					aPixelsPerMeter, 
	const Point&			aLeftBottom)
	: myField(aField)
	, myScreen(aScreen)
	, myPixelsPerMeter(aPixelsPerMeter)
	, myLeftBottom(aLeftBottom)
{
}

void
GameViewFrame::setPosition(const Point& aLeftBottom)
{
	myLeftBottom = aLeftBottom;
}

void
GameViewFrame::render()
{
	defineRenderRange();
	for (int row = myRenderRange.topRow; row >= myRenderRance.bottomRow; --row)
	{
		for (int col = myRenderRange.leftColumn; col <= myRenderRange.rightColumn; ++col)
		{
			CellPosition pos(row, col);
			SurfaceElement surface = myField.getCellSurface(pos);
			Point p = myField.cellPositionToCoord(pos);
			Sprite& sprite = SpriteProvider::getInstance().getSpriteForSurface(sufrace);
			ScreenPoint screenPos = fieldToScreen(p);
			sprite->renderAt(screenPos);
		}
	}
}

void
GameViewFrame::defineRenderRange()
{
	CellPosition leftBottomCell = myField.getNearestCell(myLeftBottom);

}

ScreenPoint
GameViewFrame::fieldToScreen(const Point& aPoint)
{
}