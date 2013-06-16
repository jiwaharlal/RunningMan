#pragma once

#include "BasicStructs.h"

struct SpriteInfo
{
    std::string     imgFileName;
    Rect            rect;
    Position        origin;
};

class SpriteInfoProvider
{
public:
                SpriteInfoProvider();

    SpriteInfo  getSpriteInfo();
private:

};
