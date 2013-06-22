#include "Sprite.h"

#include "BitmapProvider.h"

Sprite::Sprite(
    const std::string&  aImageName,
    const Size&         aRectSize,
    const Position&     aOrigin)
    : myRectSize(aRectSize)
    , myOrigin(aOrigin)
{
    myBitmap = BitmapProvider::getInstance().getBitmap(aImageName);
}

Sprite::~Sprite()
{

}

void Sprite::renderTo(
    SDL_Surface*				aSurface,
    const Position&				aPosition)
{
    Position drawPosition(aPosition);
    drawPosition.x -= myOrigin.x;
    drawPosition.y -= myOrigin.y;

    myBitmap->drawTo(aSurface, drawPosition, Rect(getRectPos(), myRectSize));
}
