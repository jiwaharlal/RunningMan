#include "Sprite.h"

#include "BitmapProvider.h"

Sprite::Sprite(
    const std::string&			aImageName,
    const Rect&                 aImageRect,
    const Position&             aOrigin)
    : myImageRect(aImageRect)
    , myOrigin(aOrigin)
{
    myBitmap = BitmapProvider::getInstance().getBitmap(aImageName);
}

void Sprite::renderTo(
    SDL_Surface*				aSurface,
    const Position&				aPosition)
{
    Position drawPosition(aPosition);
    drawPosition.x -= myOrigin.x;
    drawPosition.y -= myOrigin.y;
    myBitmap->drawTo(aSurface, drawPosition, myImageRect);
}
