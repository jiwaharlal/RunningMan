#include "SpriteInfoProvider.h"

SpriteInfoProvider::SpriteInfoProvider()
{

}

SpriteInfo
SpriteInfoProvider::getSpriteInfo()
{
    SpriteInfo sand;
    sand.imgFileName = "ground.png";
    sand.rect = Rect(276, 644, 92, 92);
    sand.origin = Position(46, 46);

    return sand;
}
