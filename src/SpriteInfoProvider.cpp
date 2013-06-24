#include "SpriteInfoProvider.h"

#include <yaml-cpp/yaml.h>

#include "Paths.h"

using namespace std;

SpriteInfoProvider::SpriteInfoProvider()
{
    readSpriteConfig();
}

SpriteInfo
SpriteInfoProvider::getSpriteInfo()
{
    SpriteInfo sand;
    sand.imgFileName = "ground.png";
    sand.rect = Rect(276, 644, 92, 92);
    sand.origin = Position(46, 46);

    return sand;
}

StaticSpriteInfo    SpriteInfoProvider::getStaticSpriteInfo(
                        const std::string&      aSpriteId)
{
}

MovableSpriteInfo   SpriteInfoProvider::getMovableSpriteInfo(
                        const std::string&      aSpriteId)
{
}

void SpriteInfoProvider::readSpriteConfig()
{
    std::string spriteConfigFilePath = Paths::getInstance().getDataRootPath();
    spriteConfigFilePath = Paths::append(spriteConfigFilePath, "sprites.yaml");
    YAML::Node root = YAML::LoadFile(spriteConfigFilePath);

    for (int i = 0; i < root.size(); ++i)
    {
        if (!root[i]["type"]) {
            std::cerr << "No sprite type specified" << std::endl;
            continue;
        }
        std::string spriteType = root[i]["type"].as<string>();
        std::string name = root[i]["type"].as<string>();
        if (spriteType == "static") {
            myStaticConfigs.push_back(std::make_pair(name, readStaticSpriteInfo(root[i]));
            continue;
        }
        if (spriteType == "movable") {
            myMovableConfigs.push_back(readMovableSpriteInfo(root[i]);
            continue;
        }
        std::cerr << "Unknown sprite type: " << spriteType << std::endl;
    }
}

SharedPtr(StaticSpriteInfo)
SpriteInfoProvider::readStaticSpriteInfo(const YAML::Node& aNode)
{
    return SharedPtr(StaticSpriteInfo);
}

SharedPtr(StaticSpriteInfo)
SpriteInfoProvider::readMovableSpriteInfo(const YAML::Node& aNode)
{
    return SharedPtr(MovableSpriteInfo);
}
