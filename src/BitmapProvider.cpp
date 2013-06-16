#include "BitmapProvider.h"

#include <boost/filesystem.hpp>
#include <iostream>

#include "Paths.h"

namespace fs = boost::filesystem;

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
    fs::path fullPath = Paths::getInstance().getImagesPath();
    fullPath /= aFileName;
    SharedPtr(SdlBitmap) newBitmap(new SdlBitmap(fullPath.string()));
    myBitmaps.insert(myBitmaps.begin(), std::make_pair(aFileName, newBitmap));

    return newBitmap;
}
