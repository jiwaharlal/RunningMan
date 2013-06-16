#include "SdlBitmap.h"

#include <SDL/SDL_image.h>
#include <exception>
#include <iostream>

SdlBitmap::SdlBitmap(
    const std::string&		aFileName)
{
    mySurface = IMG_Load(aFileName.c_str());
    if ( !mySurface )
    {
        throw ErrorLoadingImage();
    }
    std::cout << "Image loaded SdlBitmap::SdlBitmap" << std::endl;
}

SdlBitmap::~SdlBitmap()
{
    std::cout << "In bitmap destructor" << std::endl;
    SDL_FreeSurface(mySurface);
}

void
SdlBitmap::drawTo(
	SDL_Surface*			aTargetSurface)
{
}

void
SdlBitmap::drawTo(
    SDL_Surface*			aTargetSurface,
    const Position&			aScreenPos,
    const Rect&				aBitmapRect)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = aBitmapRect.pos.x;
    srcRect.y = aBitmapRect.pos.y;
    srcRect.h = aBitmapRect.size.height;
    srcRect.w = aBitmapRect.size.width;
    destRect.x = aScreenPos.x;
    destRect.y = aScreenPos.y;
    SDL_BlitSurface(mySurface, &srcRect, aTargetSurface, &destRect);

    /*SdlFrame srcFrame(mySurface, aBitmapRect);
    SdlFrame destFrame(aTargetSurface, Rect(aScreenPos, aBitmapRect.size));

    for (int row = 0; row < aBitmapRect.size.height; ++row)
    {
        for (int col = 0; col < aBitmapRect.size.width; ++col)
        {
            destFrame.pixel(col, row) = srcFrame.pixel(col, row);
        }
    }*/
    /*
    SDL_Surface* src = mySurface, *dest = aTargetSurface;
    int32_t rowLimit = srcRow + aBitmapRect.size.height;
    int32_t destRow = aScreenPos.y;
    for (int32_t srcRow = aBitmapRect.pos.y; srcRow < rowLimit; ++srcRow)
    {
        uint32_t* rowBegin = src->pixels + srcRow * src->pitch / 4 + aBitmapRect.pos.x;
        uint32_t* rowEnd = rowBegin + aBitmapRect.size.width;
        for (uint32_t* srcPixel = rowBegin; srcPixel != rowEnd; ++srcPixel)
        {

        }


    }
    for uint32_t srcPixel =
    */
}

SDL_Surface&
SdlBitmap::surface()
{
    return *mySurface;
}

SdlBitmap::SdlFrame::SdlFrame(SDL_Surface* aSurface, const Rect& aBorders)
    : mySurface(aSurface)
    , myLeft(aBorders.pos.x)
    , myTop(aBorders.pos.y)
    , myWidth(aBorders.size.width)
    , myHeight(aBorders.size.height)
{

}

uint32_t&
SdlBitmap::SdlFrame::pixel(int x, int y)
{
    return *(static_cast<uint32_t*>(mySurface->pixels) + (myTop + y) * mySurface->w + myLeft + x);
}

const uint32_t&
SdlBitmap::SdlFrame::pixel(int x, int y) const
{
    return *(static_cast<uint32_t*>(mySurface->pixels) + (myTop + y) * mySurface->w + myLeft + x);
}
