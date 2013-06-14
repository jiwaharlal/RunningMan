#include "BasicStructs.h"

FloatPosition::FloatPosition()
{}

FloatPosition::FloatPosition(float aX, float aY)
	: x(aX), y(aY)
{
}

namespace basic_structs
{
	bool floatEqual(float lhs, float rhs)
	{
		float epsilon = 0.0001f;
		return lhs + epsilon > rhs && lhs - epsilon < rhs;
	}
}

bool FloatPosition::operator ==(const FloatPosition& rhs)
{
	return basic_structs::floatEqual(x, rhs.x) && basic_structs::floatEqual(y, rhs.y);
}

CellPosition::CellPosition()
{}

CellPosition::CellPosition(int aRow, int aCol)
	: row(aRow), col(aCol)
{
}

bool CellPosition::operator ==(const CellPosition& rhs)
{
	return row == rhs.row && col == rhs.col;
}

Position::Position(int aX, int aY)
	: x(aX), y(aY)
{
}

Position::Position()
{
}