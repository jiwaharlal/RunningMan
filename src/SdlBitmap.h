#pragma once

#include <string>
#include <SDL.h>

#include "BasicStructs.h"

class SdlBitmap
{
public:
					SdlBitmap(
						const std::string&		aFileName);
	void			drawTo(
						SDL_Surface&			aTargetSurface);
	void			drawTo(
						SDL_Surface&			aTargetSurface,
						const Position&			aScreenPos,
						const Rect&				aBitmapRect);
private:
	SDL_Surface*		mySurface;
};