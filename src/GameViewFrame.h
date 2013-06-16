#pragma once

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include <boost/numeric/ublas/matrix.hpp>

#include "BasicStructs.h"

class GameField;

class GameViewFrame
{
public:
						GameViewFrame(
                            GameField&              aField,
                            SDL_Surface*            aScreen,
                            float                   aPixelsPerMeter,
                            const FloatPosition&    aLeftTop);
	void				setPosition(
                            const FloatPosition&    aLeftTop);
	void				render(
                            SDL_Surface*            aSurface);
	Position            fieldToScreen(
                            const FloatPosition&    aPosition);
private:
	void				defineRenderRange();
	void                createTransformationMatrixes();

	struct RenderRange
	{
		int bottomRow;
		int topRow;
		int leftColumn;
		int rightColumn;
	};

	GameField&			myField;
	SDL_Surface*		myScreen;
	FloatPosition		myLeftTop;
	float				myPixelsPerMeter;
	RenderRange			myRenderRange;
	boost::numeric::ublas::matrix<float>    myFieldToScreenMatrix;
	boost::numeric::ublas::matrix<float>    myScreenToFieldMatrix;
};
