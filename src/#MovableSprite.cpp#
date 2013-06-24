#include "MovableSprite.h"

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

MovableSprite::MovableSprite(
    const std::string&      aImageName,
    const Position&         aMatrixLeftTop,
    const Size&             aRectSize,
    const Position&         aOrigin,
    int                     aDirectionStep,
    int                     aFirstLineDirection,
    int                     aFramesCount,
    float                   aFrameDuration,
    int                     aDirection /*= 0*/)
    : Sprite(aImageName, aRectSize, aOrigin)
    , myMatrixLeftTop(aMatrixLeftTop)
    , myDirectionStep(aDirectionStep)
    , myFirstLineDirection(aFirstLineDirection)
    , myFramesCount(aFramesCount)
    , myFrameDuration(aFrameDuration)
    , myIsMoving(false)
    , myRow(0)
{

}

MovableSprite::~MovableSprite()
{

}

void
MovableSprite::setMoving(
    bool                    aIsMoving)
{
    if (aIsMoving)
    {
        if (myIsMoving)
        {
            return;
        }
        myIsMoving = true;
        myAnimationStartTime = static_cast<double>(SDL_GetTicks()) / 1000.0;

        return;
    }

    myIsMoving = false;
}

bool
MovableSprite::isMoving()
{
    return myIsMoving;
}

Position
MovableSprite::getRectPos()
{
    int col = getColumn();
    return Position(myMatrixLeftTop.x + col * myRectSize.width,
                    myMatrixLeftTop.y + myRow * myRectSize.height);
}

void
MovableSprite::setDirection(
    int                     aDirection)
{
    myRow = ((aDirection + 360 + (myDirectionStep / 2) - myFirstLineDirection) % 360) / myDirectionStep;
}

int
MovableSprite::getColumn()
{
    if (!myIsMoving)
    {
        return 0;
    }
    double curTime = static_cast<double>(SDL_GetTicks()) / 1000.0;
    float timeDiff = static_cast<float>(curTime - myAnimationStartTime);
    int frameIndex = static_cast<int>(timeDiff / myFrameDuration) % myFramesCount;
    return frameIndex + 1;
}
