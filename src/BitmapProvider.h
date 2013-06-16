#pragma once

#include <map>
#include <string>

#include "SdlBitmap.h"
//class SdlBitmap;

class BitmapProvider
{
public:
    static BitmapProvider&  getInstance();

    SharedPtr(SdlBitmap)    getBitmap(const std::string& aFileName);
protected:
private:
    BitmapProvider();

    typedef std::map<std::string, SharedPtr(SdlBitmap)> BitmapsMap;
    BitmapsMap  myBitmaps;
};
