#pragma once

#include "BasicStructs.h"

struct StaticSpriteInfo
{
    std::string     imgFileName;
    Rect            rect;
    Position        origin;
};

struct MovableSpriteInfo
{
    std::string     imgFileName;
    Size            rectSize;
    Position        origin;
    float           frameDuration;
    int             frameCount;
    int             directionStep;
    int             directionStart;
};

class SpriteInfoProvider
{
public:
                        SpriteInfoProvider();

    SpriteInfo          getSpriteInfo();
    StaticSpriteInfo    getStaticSpriteInfo(
                            const std::string&      aSpriteId);
    MovableSpriteInfo   getMovableSpriteInfo(
                            const std::string&      aSpriteId);
private:
    void                readSpriteConfig();

    std::map<std::string, StaticSpriteInfo>     myStaticConfigs;
    std::map<std::string, MovableSpriteInfo>    myMovableConfigs;
};
