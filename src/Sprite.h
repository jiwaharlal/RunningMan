#pragma once

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include <string>
#include <boost/shared_ptr.hpp>

#include "BasicStructs.h"

class SdlBitmap;

class Sprite
{
public:
						Sprite(
							const std::string&			aImageName,
							const Rect&                 aImageRect,
							const Position&             aOrigin);
	void				renderTo(
							SDL_Surface*				aSurface,
							const Position&				aPosition);
private:
	boost::shared_ptr<SdlBitmap>		myBitmap;
};
