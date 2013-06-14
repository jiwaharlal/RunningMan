#pragma once

#include <SDL.h>

#include "BasicStructs.h"

class SdlBitmap;

class Sprite
{
public:
						Sprite(
							const std::string&			aImageName, 
							const Position&				aLeftBottom,
							int							aImgHeight,
							int							aImgWidth,
							int							aImgOriginX,
							int							aImgOriginY);
	void				renderTo(
							SDL_Surface*				aSurface,
							const Position&				aPosition);
private:
	boost::shared_ptr<SdlBitmap>		myBitmap;
};