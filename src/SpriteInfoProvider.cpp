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

StaticSpriteInfo
SpriteInfoProvider::getStaticSpriteInfo(
    const std::string&      aSpriteId)
{
    auto it = myStaticConfigs.find(aSpriteId);
    if (it == myStaticConfigs.end())
    {
        cerr << "Sprite not found: " << aSpriteId << std::endl;
        return StaticSpriteInfo();
    }
    return it->second;
}

MovableSpriteInfo
SpriteInfoProvider::getMovableSpriteInfo(
    const std::string&      aSpriteId)
{
    auto it = myMovableConfigs.find(aSpriteId);
    if (it == myMovableConfigs.end()) {
        cerr << "Sprite not found: " << aSpriteId << std::endl;
        return MovableSpriteInfo();
    }
    return it->second;
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
        std::string name = root[i]["name"].as<string>();
        if (spriteType == "static") {
            myStaticConfigs.push_back(std::make_pair(name, readStaticSpriteInfo(root[i])));
            continue;
        }
        if (spriteType == "movable") {
            myMovableConfigs.push_back(std::make_pair(name, readMovableSpriteInfo(root[i])));
            continue;
        }
        std::cerr << "Unknown sprite type: " << spriteType << std::endl;
    }
}

StaticSpriteInfo
SpriteInfoProvider::readStaticSpriteInfo(const YAML::Node& aNode)
{
    StaticSpriteInfo config;

    config.imgFileName = aNode["image_file"].as<string>();
    const YAML::Node& origin = aNode["origin"];
    config.origin.x = origin["x"].as<int>();
    config.origin.y = origin["y"].as<int>();
    const YAML::Node& rectangle = aNode["rectangle"];
    config.rect.pos.x = rectangle["left"].as<int>();
    config.rect.pos.y = rectangle["top"].as<int>();
    config.rect.size.width = rectangle["width"].as<int>();
    config.rect.size.height = rectangle["height"].as<int>();

    return config;
}

MovableSpriteInfo
SpriteInfoProvider::readMovableSpriteInfo(const YAML::Node& aNode)
{
    MovableSpriteInfo config;

    config.imgFileName = aNode["image_file"].as<string>();
    const YAML::Node& origin = aNode["origin"];
    config.origin.x = origin["x"].as<int>();
    config.origin.y = origin["y"].as<int>();
    const YAML::Node& rectSize = aNode["rect_size"];
    config.rectSize.width = rectSize["width"].as<int>();
    config.rectSize.height = rectSize["height"].as<int>();
    config.frameDuration = aNode["frame_duration"].as<float>();
    config.frameCount = aNode["frame_count"].as<int>();
    config.directionStep = aNode["direction_step"].as<int>();
    config.directionStart = aNode["direction_start"].as<int>();

    return config;
}
