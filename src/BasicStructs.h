#pragma once

struct Point
{
	Point();
	Point(float aX, float aY);
	bool operator ==(const Point& rhs);
	float x;
	float y;
};

struct CellPosition
{
	CellPosition();
	CellPosition(int aRow, int aCol);
	bool operator ==(const CellPosition& rhs);
	int row;
	int col;
};