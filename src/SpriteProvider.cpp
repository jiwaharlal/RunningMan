#include "SpriteProvider.h"

#include "SpriteInfoProvider.h"
#include "StaticSprite.h"

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
    SharedPtr(Sprite) sprite(new StaticSprite(info.imgFileName, info.rect, info.origin));

    return sprite;
}

