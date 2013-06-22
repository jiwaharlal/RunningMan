#pragma once

#include "Sprite.h"

class SdlBitmap;

class MovableSprite: public Sprite
{
public:
                    MovableSprite(
                        const std::string&      aImageName,
                        const Position&         aMatrixLeftTop,
                        const Size&             aRectSize,
                        const Position&         aOrigin,
                        int                     aDirectionStep,
                        int                     aFirstLineDirection,
                        int                     aFramesCount,
                        float                   aFrameDuration,
                        int                     aDirection = 0);

    virtual         ~MovableSprite() override;

    void            setMoving(
                        bool                    aIsMoving);
    bool            isMoving();

    void            setDirection(
                        int                     aDirection);
protected:
    Position        getRectPos() override;
private:
    int             getColumn();

	Position                myMatrixLeftTop;
	int                     myRow;
	int                     myDirectionStep;
	int                     myFirstLineDirection;
	float                   myFrameDuration;
	int                     myFramesCount;
	bool                    myIsMoving;
	double                  myAnimationStartTime;
};

