#include "Board.h"
#include <assert.h>
#include "Snake.h"
#include "Goal.h"

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

bool Board::CheckForObstacle(const Location& loc) const
{
	return hasObstacle[loc.y * width + loc.x];
}

void Board::SpawnObstacle(std::mt19937& rng, const Snake & snake, const Goal & goal)
{
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || CheckForObstacle(newLoc) || goal.GetLocation() == newLoc);

	hasObstacle[newLoc.y * width + newLoc.x] = true;
}

void Board::DespawnObstacle(const Location & loc)
{
	hasObstacle[loc.y * width + loc.x] = false;
}

void Board::DrawObstacles()
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (CheckForObstacle({ x,y }))
				DrawCellWithPadding({ x,y }, obstacleColor);
		}
	}
}

void Board::ResetObstacles()
{
	for (int i = 0; i < (width*height); ++i)
	{
		hasObstacle[i] = false;
	}
}
