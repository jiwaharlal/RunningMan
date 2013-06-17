#pragma once

#include "ImageLoader.h"

class LodePngImageLoader: public ImageLoader
{
public:
	SDL_Surface*	loadImage(const std::string& aFilePathName);
private:
};