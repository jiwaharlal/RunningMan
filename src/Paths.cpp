#include "Paths.h"

#include <algorithm>
#include <list>
#include <iostream>

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

std::string
Paths::shortenPath(const std::string& aPath)
{
    std::list<std::string> pathElements;
    size_t eltBegin = 0;
    size_t delimiterPos = aPath.find_first_of(delimiters);
    while (delimiterPos != std::string::npos)
    {
        pathElements.emplace_back(aPath.begin() + eltBegin, aPath.begin() + delimiterPos);
        eltBegin = delimiterPos + 1;
        delimiterPos = aPath.find_first_of(delimiters, eltBegin);
    }
    for (auto it = pathElements.begin(); it != pathElements.end(); )
    {
        if (*it == ".")
        {
            it = pathElements.erase(it);
            continue;
        }
        if (*it == "..")
        {
            if (it != pathElements.begin())
            {
                auto prev = it;
                --prev;
                pathElements.erase(prev);
                it = pathElements.erase(it);
                continue;
            }
        }
        ++it;
    }
    string result;
    for (list<string>::iterator it = pathElements.begin(); it != pathElements.end(); ++it)
    {
        result += *it;
        result += delimiter;
    }
    return result;
}

