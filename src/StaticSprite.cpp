#include "StaticSprite.h"

#include "BitmapProvider.h"

StaticSprite::StaticSprite(
    const std::string&			aImageName,
    const Rect&                 aImageRect,
    const Position&             aOrigin)
    : Sprite(aImageName, aImageRect.size, aOrigin)
    , myRectPos(aImageRect.pos)
{
}

StaticSprite::~StaticSprite()
{

}

Position
StaticSprite::getRectPos()
{
    return myRectPos;
}
