#pragma once

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include <string>
#include <boost/shared_ptr.hpp>

#include "BasicStructs.h"
#include "Sprite.h"

class SdlBitmap;

class StaticSprite: public Sprite
{
public:
                StaticSprite(
                    const std::string&			aImageName,
                    const Rect&                 aImageRect,
                    const Position&             aOrigin);
    virtual     ~StaticSprite() override;
protected:
    Position    getRectPos() override;
private:
	Position    myRectPos;
};
