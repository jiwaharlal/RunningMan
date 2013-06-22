#pragma once

#include <string>

class Paths
{
public:
    static Paths&               getInstance();

    //boost::filesystem::path     getImagesPath();
    std::string                 getImagesPath();
    void                        setExePathName(const std::string& aExePathName);
    static std::string          append(const std::string& aPath, const std::string& aPathEntry);
    static std::string          appendDelimiter(const std::string& aPath);
    static std::string          subtractLastEntry(const std::string& aPath);
    static std::string          shortenPath(const std::string& aPath);
private:
    Paths();

    //static std::list<std::string>   splitPath(const std::string& aPath);
    //boost::filesystem::path     myProgramPath;
    std::string         myProgramPath;
};
