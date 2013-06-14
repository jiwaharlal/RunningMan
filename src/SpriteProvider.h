#pragma once

#include <boost/shared_ptr.hpp>

#include "Singleton.h"
#include "Surface.h"
#include "Sprite.h"

class Sprite;

class SpriteProvider: public Singleton<SpriteProvider>
{
public:
	boost::shared_ptr<Sprite>			getSpriteForSurface(SurfaceElement aSurface);
};