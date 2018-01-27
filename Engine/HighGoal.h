#pragma once

#include <random>
#include "Location.h"
#include "Board.h"
#include "Snake.h"

class HighGoal
{
public:
	HighGoal(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Draw(Board& brd) const;
	void UpdateColor();
	const Location& GetLocation() const;

private:
	Color c = { 0,0,0 };
	bool colorIncreasing = true;
	Location loc;
};