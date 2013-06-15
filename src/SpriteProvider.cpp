#include "SpriteProvider.h"

SpriteProvider&
SpriteProvider::getInstance()
{
    static SpriteProvider instance;

    return instance;
}

SharedPtr(Sprite)
SpriteProvider::getSpriteForSurface(SurfaceElement aSurface)
{
    SharedPtr(Sprite) sprite(new Sprite("image.bmp", Rect(), Position()));

    return sprite;
}

