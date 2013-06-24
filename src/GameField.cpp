#include "GameField.h"

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <fstream>

#include "Paths.h"

using namespace std;

GameField::FieldCell::FieldCell()
{}

GameField::FieldCell::FieldCell(const std::string& aSurface, const std::string& aObject)
    : surface(aSurface)
    , object(aObject)
{}

GameField::GameField(int aWidth, int aHeight, float aCellDiagonal)
	: myWidth(aWidth)
	, myHeight(aHeight)
	, myCellDiagonal(aCellDiagonal)
{
}

GameField::GameField(const std::string& aMapFileName)
{
    std::string fullPath = Paths::getInstance().getMapsPath();
    fullPath = Paths::append(fullPath, aMapFileName);
    try {
        std::ifstream in(fullPath);
        if (!in.is_open()) {
            std::cerr << "Failed to open file: " << fullPath << std::endl;
            throw std::exception();
        }
        populateFromStream(in);
    } catch(...) {
        std::cerr << "Error reading from file :" << fullPath << std::endl;
        throw std::exception();
    }
}

GameField::GameField(std::istream& aIn)
{
    populateFromStream(aIn);
}

Size readSize(const std::string& str)
{
    try {
        Size result;
        boost::match_results<std::string::const_iterator> what;
        if (!boost::regex_search(str, what, boost::regex("height:\\s+(\\d+)"))) {
            throw std::exception();
        }
        result.height = boost::lexical_cast<int>(std::string(what[1].first, what[1].second));
        if (!boost::regex_search(str, what, boost::regex("width:\\s+(\\d+)"))) {
            throw std::exception();
        }
        result.width = boost::lexical_cast<int>(std::string(what[1].first, what[1].second));

        return result;
    } catch(...) {
        std::cerr << "Error parsing size string: " << str << std::endl;
        return Size(0, 0);
    }
}

GameField::FieldCell readCell(const std::string& str)
{
    GameField::FieldCell result;
    try {
         boost::match_results<std::string::const_iterator> what;
        if (!boost::regex_search(str, what, boost::regex("surface:\\s+(\\w+)"))) {
            throw std::exception();
        }
        result.surface = std::string(what[1].first, what[1].second);
        if (boost::regex_search(str, what, boost::regex("object:\\s+(\\w+)"))) {
            result.object = std::string(what[1].first, what[1].second);
        }

        std::cout << "surface: " << result.surface << "  object: " << result.object << std::endl;
    } catch(...) {
        std::cerr << "Error parsing cell string: " << str << std::endl;
    }
    return result;
}

void
GameField::populateFromStream(istream& in)
{
    char buffer[128];
    in.getline(buffer, 128);
    Size size = readSize(buffer);
    myHeight = size.height;
    myWidth = size.width;
    myCells.resize(myHeight);

    for ( auto cellsRow = myCells.begin(); cellsRow != myCells.end(); ) {
        cellsRow->clear();
        cellsRow->reserve(myWidth);
        for (int i = 0; i < myWidth; i++) {
            in.getline(buffer, 128);
            cellsRow->emplace_back(readCell(buffer));
        }
        ++cellsRow;
    }
}

const GameField::FieldCell&
GameField::getCell(const CellPosition& aPosition)
{
    return myCells[aPosition.row][aPosition.col];
}

FloatPosition GameField::cellPositionToCoord(const CellPosition& aPosition)
{
	FloatPosition p;
	p.x = (aPosition.col * 2 + aPosition.row % 2) / 2.0f * myCellDiagonal ;
	p.y = aPosition.row * myCellDiagonal / 2.0f;

	return p;
}

CellPosition GameField::cellCoordToPosition(const FloatPosition& aPosition)
{
	CellPosition pos;

	pos.row = static_cast<int>((aPosition.y * 2.0f) / myCellDiagonal);
	pos.col = static_cast<int>((aPosition.x / myCellDiagonal * 2.0f - pos.row % 2) / 2);

	return pos;
}

CellPosition
GameField::getNearestCell(const FloatPosition& aPosition)
{
	float rowInterpolation = (aPosition.y * 2.0f) / myCellDiagonal;
	float colInterpolation = (aPosition.x / myCellDiagonal * 2.0f - static_cast<int>(rowInterpolation + 0.5) % 2) / 2;

	CellPosition pos(static_cast<int>(rowInterpolation), static_cast<int>(colInterpolation));
	if (rowInterpolation - static_cast<float>(pos.row) > 0.5f) {
		pos.row += 1;
	}
	if (colInterpolation - static_cast<float>(pos.col) > 0.5f) {
		pos.col += 1;
	}

	return pos;
}

SurfaceElement
GameField::getCellSurface(const CellPosition& aPosition)
{
	return Surface_Sand;
}

int
GameField::height() const
{
    return myHeight;
}

int
GameField::width() const
{
    return myWidth;
}
