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
						GameViewFrame(
                            GameField&              aField,
                            SDL_Surface*            aScreen,
                            float                   aPixelsPerMeter,
                            const FloatPosition&    aLeftBottom);
	void				setPosition(
                            const FloatPosition&    aLeftBottom);
	void				render(
                            SDL_Surface*            aSurface);
	Position            fieldToScreen(
                            const FloatPosition&    aPosition);
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
	FloatPosition		myLeftBottom;
	float				myPixelsPerMeter;
	RenderRange			myRenderRange;
};
