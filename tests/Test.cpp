#include "gtest/gtest.h"
#include <string>

#include "../src/GameField.h"
#include "../src/Paths.h"

bool floatEqual(float lhs, float rhs)
{
	float epsilon = 0.0001f;
	return lhs + epsilon > rhs && lhs - epsilon < rhs;
}

class RMTest : public ::testing::Test
{
};

TEST_F(RMTest, CheckGameFieldCellPositionToCoord)
{
	GameField gf(10, 10, 3.0f);
	CellPosition pos(1, 1);
	FloatPosition p = gf.cellPositionToCoord(pos);
	ASSERT_TRUE(floatEqual(p.x, 4.5f) && floatEqual(p.y, 1.5f));
}

TEST_F(RMTest, CheckGameFieldNearestCell)
{
	GameField gf(10, 10, 3.0f);
	ASSERT_TRUE(gf.getNearestCell(FloatPosition(2, 2)) == CellPosition(1, 0));
	ASSERT_TRUE(gf.getNearestCell(FloatPosition(2.5, 2.5)) == CellPosition(2, 1));
	ASSERT_TRUE(gf.getNearestCell(FloatPosition(2.5, 3.5)) == CellPosition(2, 1));
	ASSERT_TRUE(gf.getNearestCell(FloatPosition(5, 4)) == CellPosition(3, 1));
	ASSERT_TRUE(gf.getNearestCell(FloatPosition(5.5, 3.5)) == CellPosition(2, 2));
	ASSERT_TRUE(gf.getNearestCell(FloatPosition(6.5, 3.5)) == CellPosition(2, 2));
	ASSERT_TRUE(gf.getNearestCell(FloatPosition(7, 4)) == CellPosition(3, 2));
}

TEST_F(RMTest, CheckPaths)
{
    std::string path = Paths::append("root", "subdir1");
	path = Paths::append(path, "subdir2");
#ifdef __linux__
	const std::string delimiter("/");
	const std::string appRoot("/tmp/usr/rm/");
	const std::string binaryPath(appRoot + "rm");
	const std::string imagesPath(appRoot + "data/../data/./img/");
#else
	const std::string delimiter("\\");
	const std::string appRoot("d:\\games\\RunningMan\\");
	const std::string binaryPath(appRoot + "bin\\RunningMan.exe");
	const std::string imagesPath(appRoot + "data\\..\\data\\.\\img\\");
#endif
	Paths::getInstance().setExePathName(binaryPath);
	ASSERT_TRUE(Paths::shortenPath(Paths::appendDelimiter(Paths::getInstance().getImagesPath())) == Paths::shortenPath(imagesPath));
	ASSERT_TRUE(path == std::string("root") + delimiter + "subdir1" + delimiter + "subdir2");
}

TEST_F(RMTest, CheckGameField)
{
    Size size = readSize("height: 8 width: 67");
    ASSERT_TRUE(size.height == 8 && size.width == 67);
    GameField::FieldCell cell = readCell("surface: sand object: green_tree");
    ASSERT_TRUE(cell.surface == "sand" && cell.object == "green_tree");
    cell = readCell("surface: sand42 object: green_tree_24");
    ASSERT_TRUE(cell.surface == "sand42" && cell.object == "green_tree_24");

    std::string map("height: 2 width: 2\nsurface: sand\nsurface: grass\nsurface: sand\nsurface: sand object: tree");
    std::stringstream mapStream(map);
    GameField field(mapStream);
    const GameField::FieldCell& cellRef = field.getCell(CellPosition(1, 1));
    ASSERT_TRUE(cellRef.surface == "sand" && cellRef.object == "tree");
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
