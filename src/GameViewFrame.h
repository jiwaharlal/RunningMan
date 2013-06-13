#pragma once

#include <SDL.h>

#include "BasicStructs.h"

class GameViewFrame
{
public:
						GameViewFrame(GameField& aField, SDL_Surface* aScreen, float aPixelsPerMeter, const Point& aLeftBottom);
	void				setPosition(const Point& aLeftBottom);
	void				render();
private:
	void				defineRenderRange();

	struct RenderRange
	{
		int bottmRow;
		int topRow;
		int leftColumn;
		int rightColumn;
	};

	GameField&			myField;
	SDL_Surface*		myScreen;
	Point				myLeftBottom;
	float				myPixelsPerMeter;
	RenderRange			myRenderRange;
};