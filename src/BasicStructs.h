#pragma once

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
	int		height;
	int		width;
};

struct Rect
{
	Position	pos;
	Size		size;
};