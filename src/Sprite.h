#pragma once

#include "BasicStructs.h"

class SdlBitmap;
class SDL_Surface;

class Sprite
{
public:
                        Sprite(
                            const std::string&      aImageName,
                            const Size&             aRectSize,
                            const Position&         aOrigin);
    virtual             ~Sprite();

    virtual void        renderTo(
                            SDL_Surface*            aSurface,
                            const Position&         aPosition);
protected:
    virtual Position    getRectPos() = 0;

    SharedPtr(SdlBitmap)    myBitmap;
    Size                    myRectSize;
    Position                myOrigin;
};
