#pragma once

#include "Location.h"
#include "Graphics.h"
#include <random>

class Board 
{
public:
	Board(Graphics& gfx);
	void DrawBorder();
	void DrawCellWithPadding( const Location& loc, Color c);
	bool IsInsideBoard( const Location& loc) const;
	int GetGridWidth() const;
	int GetGridHeight() const;
	int GetDimension() const;
	bool CheckForObstacle(const Location& loc) const;
	void SpawnObstacle( std::mt19937& rng, const class Snake& snake, const class Goal& goal);
	void DrawObstacles();
	void ResetObstacles();

private:
	Graphics& gfx;
	
	//BOARD DIMENSIONS
	static constexpr int dim = 18;
	static constexpr int width = 25;
	static constexpr int height = 25;
	static constexpr int x = 10;   // THE POINT WHERE THE BOARD STARTS
	static constexpr int y = 50;   // THE POINT WHERE THE BOARD STARTS

	//BORDER DIMENSIONS
	static constexpr Color borderColor = Colors::Blue;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;

	static constexpr Color obstacleColor = Colors::Gray;
	bool hasObstacle[width * height] = { false };
};