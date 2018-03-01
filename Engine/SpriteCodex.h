#pragma once

#include "Graphics.h"

class SpriteCodex
{
public:
	static void DrawGameOver( int x,int y,Graphics& gfx );
	static void DrawTitle( int x,int y,Graphics& gfx );
	static void DrawPause(int x, int y, Graphics& gfx);
	static void DrawYouWin(int x, int y, Graphics& gfx);
	static void DrawPressC(int x, int y, Graphics& gfx);
	static void DrawPressR(int x, int y, Graphics& gfx);

	static void DrawChooseMode (int x_center, int y_center, Graphics& gfx); // 271 x 18
	static void DrawNormalMode (int x_center, int y_center, Graphics& gfx); // 92 x 18
	static void DrawNormalModeSelected (int x_center, int y_center, Graphics& gfx);
	static void DrawObstacleMode(int x_center, int y_center, Graphics& gfx); // 124 x 18
	static void DrawObstacleModeSelected(int x_center, int y_center, Graphics& gfx);
	static void DrawPoisonMode(int x_center, int y_center, Graphics& gfx); // 94 x 18
	static void DrawPoisonModeSelected(int x_center, int y_center, Graphics& gfx);
};