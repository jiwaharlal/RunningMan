#include "SpriteProvider.h"

#include "SpriteInfoProvider.h"

SpriteProvider::SpriteProvider()
    : myInfoProvider(new SpriteInfoProvider())
{
}

SpriteProvider&
SpriteProvider::getInstance()
{
    static SpriteProvider instance;

    return instance;
}

SharedPtr(Sprite)
SpriteProvider::getSpriteForSurface(SurfaceElement aSurface)
{
    SpriteInfo info = myInfoProvider->getSpriteInfo();
    SharedPtr(Sprite) sprite(new Sprite(info.imgFileName, info.rect, info.origin));

    return sprite;
}

