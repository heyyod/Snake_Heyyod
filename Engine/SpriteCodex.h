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
};