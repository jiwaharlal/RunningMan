#pragma once

#include <string>
#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "BasicStructs.h"

class SdlBitmap
{
public:
					SdlBitmap(
						const std::string&		aFileName);
	void			drawTo(
						SDL_Surface*			aTargetSurface);
	void			drawTo(
						SDL_Surface*			aTargetSurface,
						const Position&			aScreenPos,
						const Rect&				aBitmapRect);
    SDL_Surface&    surface();
private:
    class SdlFrame
    {
    public:
                            SdlFrame(SDL_Surface* aSurface, const Rect& aBorders);
        uint32_t&           pixel(int x, int y);
        const uint32_t&     pixel(int x, int y) const;
    private:
        SDL_Surface*    mySurface;
        int             myLeft;
        int             myTop;
        int             myHeight;
        int             myWidth;
    };
	SDL_Surface*		mySurface;
};
