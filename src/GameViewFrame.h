#pragma once

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "BasicStructs.h"

class GameField;

class GameViewFrame
{
public:
						GameViewFrame(GameField& aField, SDL_Surface* aScreen, float aPixelsPerMeter, const Position& aLeftBottom);
	void				setPosition(const Position& aLeftBottom);
	void				render();
private:
	void				defineRenderRange();

	struct RenderRange
	{
		int bottomRow;
		int topRow;
		int leftColumn;
		int rightColumn;
	};

	GameField&			myField;
	SDL_Surface*		myScreen;
	Position				myLeftBottom;
	float				myPixelsPerMeter;
	RenderRange			myRenderRange;
};
