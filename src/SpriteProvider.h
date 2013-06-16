#pragma once

#include <boost/shared_ptr.hpp>

//#include "Singleton.h"
#include "Surface.h"
#include "Sprite.h"

class SpriteInfoProvider;

class Sprite;

class SpriteProvider
{
public:
    static SpriteProvider&      getInstance();

	SharedPtr(Sprite)			getSpriteForSurface(SurfaceElement aSurface);
private:
                                SpriteProvider();
    SharedPtr(SpriteInfoProvider)   myInfoProvider;
};
