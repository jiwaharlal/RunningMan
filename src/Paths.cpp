#include "Paths.h"

namespace fs = boost::filesystem;

Paths::Paths()
{

}

Paths&
Paths::getInstance()
{
    static Paths instance;

    return instance;
}

void
Paths::setProgramPath(const std::string& aProgramPath)
{
    myProgramPath = fs::absolute(fs::system_complete(fs::path(aProgramPath))).remove_filename();
}

fs::path
Paths::getImagesPath()
{
    fs::path result(myProgramPath);
    result /= "data";
    result /= "img";

    return result;
}
