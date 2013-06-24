#include "SpriteProvider.h"

#include "SpriteInfoProvider.h"
#include "StaticSprite.h"

SpriteProvider::SpriteProvider()
    : myInfoProvider(new SpriteInfoProvider())
{
    //readSpriteConfigurations();
    //createSpriteCreatorsMap();
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

SharedPtr(StaticSprite)
SpriteProvider::getStaticSprite(const std::string& aSpriteId)
{
    auto it = myStaticSpriteMap.find(aSpriteId);
    if (it != myStaticSpriteMap.end()) {
        return it->second;
    }

    StaticSpriteInfo info = myInfoProvider->getInfoForStaticSprite(aSpriteId);


}

SharedPtr(MovableSprite)
SpriteProvider::getMovableSprite(const std::string& aSpriteId)
{
}

/*SpriteProvider::getSprite(
    const std::string&          spriteId
    SharedPtr(Sprite)&          aOutSprite)
{
    mySpriteMap
}*/
