#pragma once

#include "Graphics.h"

class Score
{
public:
	void Reset();
	void IncreaseScore();
	int GetDigit(int digit);
	void DrawScorePanel(Graphics& gfx);
	int GetScore() const;

	//DRAWING CODE
	static void DrawScore(int x, int y, Graphics& gfx);
	static void DrawNumber0(int x, int y, Graphics& gfx);
	static void DrawNumber1(int x, int y, Graphics& gfx);
	static void DrawNumber2(int x, int y, Graphics& gfx);
	static void DrawNumber3(int x, int y, Graphics& gfx);
	static void DrawNumber4(int x, int y, Graphics& gfx);
	static void DrawNumber5(int x, int y, Graphics& gfx);
	static void DrawNumber6(int x, int y, Graphics& gfx);
	static void DrawNumber7(int x, int y, Graphics& gfx);
	static void DrawNumber8(int x, int y, Graphics& gfx);
	static void DrawNumber9(int x, int y, Graphics& gfx);

private:
	static constexpr int scoreWidth = 114;
	static constexpr int scoreX = 10;
	static constexpr int digitWidth = 25;
	static constexpr int digitX = 140;
	static constexpr int scoreAndDigitY = 13;
	int score = 0;
};