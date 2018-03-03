/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Location.h"
#include "Snake.h"
#include "Goal.h"
#include "Score.h"
#include "HighGoal.h"
#include "Lives.h"
#include <random>
#include "FrameTimer.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	void GameAdjustments();
	void BaseGoalBehaniour();
	void HighGoalBehaviour();
	void AskToPlayAgain();
	void ResetForNewRound();
	void ResetForNewGame();
	void ChooseMode(const Mouse& mouse);

	// MODES
	void NormalMode();
	void ObstacleMode();
	void PoisonMode();

private:
	MainWindow& wnd;
	Graphics gfx;
	Board brd;
	Location delta_loc = { 1,0 };
	Location old_delta_loc = { 1,0 };
	Snake snek;
	std::mt19937 rng;
	Goal goal;
	Score score;
	HighGoal highgoal;
	int snekPeriod = 30;
	int snekMoveCounter = 0;
	bool gameIsOver = false;
	bool gameIsWon = false;
	bool gameIsStarted = false;
	bool gameIsPaused = false;
	bool inhibitPause = false;
	bool inhibitResume = true;
	bool playAgain = false;
	int lostLives = 0;

	int chosenMode = 0; // 0: Show modes to choose, 1: normal, 2: obstacle, 3: poison.

	//HIGH GOAL VARIABLES
	int highGoalSpawnPeriod = 60;
	int highGoalStayPeriod = 30;
	int countToSpawnHighGoal = 0;
	int countToDespawnHighGoal = 0;
	bool highGoalSpawned = false;

	// STARTING SCREEN UI
	static constexpr int ModesPosX = 240;
	static constexpr int chooseModePosY = 260 - 100;
	static constexpr int normalModePosY = 260 - 50;
	static constexpr int obstacleModePosY = 260 - 20;
	static constexpr int poisonModePosY = 260 + 10;

	FrameTimer ft;
};