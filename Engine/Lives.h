#pragma once

#include "Graphics.h"
#include "Snake.h"
#include "Location.h"
#include "Board.h"

class Lives
{
public:
	static void DrawRed(int x, int y, Graphics& gfx);
	static void DrawGrey(int x, int y, Graphics& gfx);
};