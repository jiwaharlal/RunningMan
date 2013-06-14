#include "..\src\GameField.h"
#include "gtest\gtest.h"
#include <string>

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

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
