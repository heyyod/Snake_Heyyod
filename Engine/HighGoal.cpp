#include "HighGoal.h"

HighGoal::HighGoal(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	Respawn(rng, brd, snake);
}

void HighGoal::Respawn(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.GoalIsInTile(newLoc));

	loc = newLoc;
}

void HighGoal::Draw(Board & brd) const
{
	brd.DrawCellWithPadding(loc, c);
}

void HighGoal::UpdateColor()
{
	if (colorIncreasing)
	{
		if (c.GetB() >= 250)
		{
			colorIncreasing = false;
		}
		else
		{
			c = Color( c.GetR() + 1, c.GetG() + 2, c.GetB() + 6 );
		}
	}
	else
	{
		if (c.GetB() <= 10)
		{
			colorIncreasing = true;
		}
		else
		{
			c = Color( c.GetR() - 3, c.GetG() - 6, c.GetB() - 18 );
		}
	}
}

const Location & HighGoal::GetLocation() const
{
	return loc;
}
