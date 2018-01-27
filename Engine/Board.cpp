#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx( gfx )
{}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dim;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dim;

	//top
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);
	//left
	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, borderColor);
	//bottom
	gfx.DrawRect(left, bottom - borderWidth, right, bottom, borderColor);
	//right
	gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, borderColor);
}

void Board::DrawCellWithPadding( const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x <= width);
	assert(loc.y >= 0);
	assert(loc.y <= height);

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;
	const int padding = 1;

	gfx.DrawRectDim(loc.x * dim + off_x + padding, loc.y * dim + off_y + padding, dim - 2 * padding, dim - 2 * padding, c);
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width
		&& loc.y >= 0 && loc.y < height;
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetDimension() const
{
	return dim;
}
