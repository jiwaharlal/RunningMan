#include "BasicStructs.h"

Point::Point()
{}

Point::Point(float aX, float aY)
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

bool Point::operator ==(const Point& rhs)
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
