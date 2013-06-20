#include "BitmapProvider.h"

#include <iostream>

#include "Paths.h"

BitmapProvider::BitmapProvider()
{
    //ctor
}

BitmapProvider&
BitmapProvider::getInstance()
{
    static BitmapProvider instance;

    return instance;
}

SharedPtr(SdlBitmap)
BitmapProvider::getBitmap(const std::string& aFileName)
{
    BitmapsMap::iterator iter = myBitmaps.find(aFileName);
    if (iter != myBitmaps.end())
    {
        return iter->second;
    }
    std::string fullPath = Paths::getInstance().getImagesPath();
    fullPath = Paths::append(fullPath, aFileName);
    SharedPtr(SdlBitmap) newBitmap(new SdlBitmap(fullPath));
    myBitmaps.insert(myBitmaps.begin(), std::make_pair(aFileName, newBitmap));

    return newBitmap;
}
