#pragma once

#include <string>
#ifdef __linux__
#include <SDL/SDL_image.h>
#else
#include <SDL_image.h>
#endif

#include "BasicStructs.h"

class SdlBitmap;

class ImageLoader
{
public:
	static ImageLoader&		getInstance();

	virtual SDL_Surface*	loadImage(const std::string& aFilePathName);
private:
							ImageLoader();
};