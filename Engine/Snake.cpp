#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

void Snake::Reset(const Location & loc)
{
	nSegments = 1;
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegmentsMax - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
		deltaloc[i] = delta_loc;
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody();
		++nSegments;
	}
}

void Snake::Draw(Board & brd)
{
	Color c;
	if (!finishedChangingColor)
	{
		c = bodyColor;
	}

	segments[0].Draw(brd, headColor);
	for (int i = nSegments - 1; i >= 1; --i)
	{
		segments[i].Draw(brd, c);

		if (c.GetR() < 250 && c.GetG() < 250)
		{
			c = Color(c.GetR() + 5, c.GetG() + 5, 0);
		}
		else
		{
			finishedChangingColor = true;
		}
	}
}


Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::HeadIsInsiteTile(const Location& headLoc) const
{
	for (int i = 0; i <= nSegments - 1; ++i)
	{
		if (segments[i].GetLocation() == headLoc)
		{
			return true;
		}
	}
	return false;
}

bool Snake::GoalIsInTile(const Location& goalLoc) const
{
	for (int i = 0; i <= nSegments; ++i)
	{
		if (segments[i].GetLocation() == goalLoc)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsMaxSize() const
{
	return nSegments == nSegmentsMax;
}

Color Snake::GetBodyColor() const
{
	return bodyColor;
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	c = bodyColor;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board & brd, Color in_c) const
{
	brd.DrawCellWithPadding(loc, in_c);
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

const Location & Snake::Segment::GetLocation() const
{
	return loc;
}

