#pragma once

#include <boost/filesystem.hpp>

class Paths
{
public:
    static Paths&               getInstance();

    boost::filesystem::path     getImagesPath();
    void                        setProgramPath(const std::string& aExePath);
private:
    Paths();

    boost::filesystem::path     myProgramPath;
};
