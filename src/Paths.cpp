#include "Paths.h"

#include <algorithm>

using namespace std;

#ifdef __linux__
    const std::string delimiters("/");
    const std::string delimiter("/");
#else
    const std::string delimiters("\\/");
    const std::string delimiter("\\");
#endif // __linux__

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
Paths::setExePathName(const std::string& aExePathName)
{
    myProgramPath = subtractLastEntry(aExePathName);
}

std::string
Paths::append(const std::string& aPath, const std::string& aPathEntry)
{
    return appendDelimiter(aPath) + aPathEntry;
}

std::string
Paths::appendDelimiter(const std::string& aPath)
{
    bool hasDelimiter = delimiters.find(aPath.at(aPath.length() - 1)) != string::npos;
    if (hasDelimiter) {
        return aPath;
    }
    return aPath + delimiter;
}

std::string
Paths::subtractLastEntry(const std::string& aPath)
{
    size_t found = std::string(aPath.begin(), aPath.end() - 1).find_last_of("/\\");
    return aPath.substr(0, found);
}

std::string
Paths::getImagesPath()
{
    std::string result(myProgramPath);
#ifndef __linux__
	result = append(result, "..");
#endif
    result = append(result, "data");
    result = append(result, "img");

    return result;
}
