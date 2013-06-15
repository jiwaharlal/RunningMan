#pragma once

#define SharedPtr(X) boost::shared_ptr<X>

struct FloatPosition
{
	FloatPosition();
	FloatPosition(float aX, float aY);
	bool operator ==(const FloatPosition& rhs);

	float	x;
	float	y;
};

struct CellPosition
{
	CellPosition();
	CellPosition(int aRow, int aCol);
	bool operator ==(const CellPosition& rhs);

	int		row;
	int		col;
};

struct Position
{
	Position();
	Position(int aX, int aY);

	int		x;
	int		y;
};

struct Size
{
    Size();
    Size(int aWidth, int aHieght);
	int		height;
	int		width;
};

struct Rect
{
    Rect(const Position& aLeftBottom, const Size& aSize);
    Rect(int aLeft, int aBottom, int aWidht, int aHeight);
    Rect();
	Position	pos;
	Size		size;
};
