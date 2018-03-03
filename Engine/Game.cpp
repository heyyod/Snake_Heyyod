/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	snek( {12,12} ),
	rng( std::random_device()() ),
	goal(rng, brd, snek),
	highgoal(rng, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = ft.Mark();
	startingDelay += dt;

	if (wnd.kbd.KeyIsPressed(VK_RETURN) && gameIsPaused)
	{
		gameIsPaused = false;
	}
	
	if (gameIsStarted && !gameIsPaused)
	{
		if (!gameIsOver && !gameIsWon && startingDelay > 4.0f )
		{
			if (!touchedAnObstacle)
			{
				//MOVE THE SNAKE
				if (wnd.kbd.KeyIsPressed(VK_UP) && old_delta_loc.y != 1)
				{
					delta_loc = { 0,-1 };
				}
				if (wnd.kbd.KeyIsPressed(VK_DOWN) && old_delta_loc.y != -1)
				{
					delta_loc = { 0,1 };
				}
				if (wnd.kbd.KeyIsPressed(VK_LEFT) && old_delta_loc.x != 1)
				{
					delta_loc = { -1,0 };
				}
				if (wnd.kbd.KeyIsPressed(VK_RIGHT) && old_delta_loc.x != -1)
				{
					delta_loc = { 1,0 };
				}

				TimingAdjustments();
				++snekMoveCounter;

				if (snekMoveCounter >= snekPeriod)
				{
					snekMoveCounter = 0;
					Location nextHeadLoc = snek.GetNextHeadLocation(delta_loc);
					old_delta_loc = delta_loc;

					if (chosenMode == 2 && brd.CheckForObstacle(nextHeadLoc))
					{
						snekSizeBeforeCol = snek.GetCurrentSize();

						++lostLives;
						touchedAnObstacle = true;
						brd.DespawnObstacle(nextHeadLoc);
					}

					if (!touchedAnObstacle)
					{
						if (!brd.IsInsideBoard(nextHeadLoc) ||
							snek.HeadIsInsiteTile(nextHeadLoc))
						{
							++lostLives;
							gameIsOver = true;
						}
						else
						{
							if (nextHeadLoc == goal.GetLocation())
							{
								score.IncreaseScore();
								snek.Grow();
								goal.Respawn(rng, brd, snek);

								if (chosenMode == 2)
								{
									brd.SpawnObstacle(rng, snek, goal);
								}
							}
							snek.MoveBy(delta_loc);

							HighGoalBehaviour();
						}
					}
				}
			}
			else
			{
				snakeSizeDecreaseTimer += dt;

				if (snek.GetCurrentSize() >= (snekSizeBeforeCol / 2 + 2) )
				{
					if (snakeSizeDecreaseTimer >= 0.3f)
					{
						snek.DecreaseSize();
						snakeSizeDecreaseTimer = 0.0f;
					}
				}
				else
				{
					touchedAnObstacle = false;
				}
			}

			if (snek.IsMaxSize())
			{
				gameIsWon = true;
			}

			//PAUSE AND UNPAUSE GAME
			if (wnd.kbd.KeyIsPressed(VK_PAUSE) && !gameIsPaused)
			{
				gameIsPaused = true;
			}
		}
		else
		{
			AskToPlayAgain();
		}
	}
	else
	{
		AskToChooseMode(wnd.mouse);
	}
}

// APPLIES TO NORMAL AND OBSTACLE MODE ONLY
void Game::TimingAdjustments()
{
	//CHANGE SPEED AND HIGH GOAL SPAWN TIME
	{
		if (score.GetScore() >= 50)
		{
			snekPeriod = 25;
		}
		if (score.GetScore() >= 100)
		{
			snekPeriod = 20;
			highGoalSpawnPeriod = 100;
			highGoalStayPeriod = 40;
		}
		if (score.GetScore() >= 200)
		{
			snekPeriod = 15;
			highGoalSpawnPeriod = 200;
			highGoalStayPeriod = 50;
		}
		if (score.GetScore() >= 500)
		{
			snekPeriod = 10;
		}
		if (score.GetScore() >= 1000)
		{
			snekPeriod = 8;
		}
		if (score.GetScore() >= 2000)
		{
			snekPeriod = 5;
		}
	}
}

void Game::HighGoalBehaviour()
{
	if (highGoalSpawned)
	{
		countToDespawnHighGoal++;

		const bool eatingHighGoal = snek.IsInTile(highgoal.GetLocation());
		if (eatingHighGoal)
		{
			for (int i = 0; i < 2; ++i)
			{
				snek.Grow();
			}
			for (int i = 0; i < 5; ++i)
			{
				score.IncreaseScore();
			}

			countToDespawnHighGoal = 0;
			highGoalSpawned = false;
		}
		else if (countToDespawnHighGoal == highGoalStayPeriod)
		{
			countToDespawnHighGoal = 0;
			highGoalSpawned = false;
		}
	}
	else
	{
		countToSpawnHighGoal++;
		if (countToSpawnHighGoal == highGoalSpawnPeriod)
		{
			highgoal.Respawn(rng, brd, snek);
			highGoalSpawned = true;
			countToSpawnHighGoal = 0;
		}
	}
}

void Game::AskToPlayAgain()
{
	if (wnd.kbd.KeyIsPressed('C') && !gameIsWon && lostLives < 3) //CAN'T CONTINUE IF GAME IS WON OR IF I HAVE NO MORE LIVES
	{
		ResetForNewRound();
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		ResetForNewGame();
	}
}

void Game::ResetForNewRound()
{
	startingDelay = 0.0f;
	gameIsOver = false;
	gameIsWon = false;

	snek.Reset({ 12, 12 });
	delta_loc = { 1,0 };

	goal.Respawn(rng, brd, snek);

	countToSpawnHighGoal = 0;
	countToSpawnHighGoal = 0;
	highGoalSpawned = false;
}

void Game::ResetForNewGame()
{
	startingDelay = 0.0f;
	gameIsStarted = false;
	gameIsOver = false;
	gameIsWon = false;

	snek.Reset({ 12, 12 });
	snekPeriod = 30;
	delta_loc = { 1,0 };

	brd.ResetObstacles();

	goal.Respawn(rng, brd, snek);

	countToSpawnHighGoal = 0;
	countToSpawnHighGoal = 0;
	highGoalSpawned = false;

	lostLives = 0;
	score.Reset();
}

void Game::AskToChooseMode(const Mouse & mouse)
{
	const int mouseX = wnd.mouse.GetPosX();
	const int mouseY = wnd.mouse.GetPosY();

	if ((mouseX >= (ModesPosX - 150)) && (mouseX <= (ModesPosX + 150)))
	{
		if ((mouseY >= (normalModePosY - 9)) && (mouseY <= (normalModePosY + 9)))
		{
			chosenMode = 1;
		}
		else if ((mouseY >= (obstacleModePosY - 9)) && (mouseY <= (obstacleModePosY + 9)))
		{
			chosenMode = 2;
		}
		else if ((mouseY >= (poisonModePosY - 9)) && (mouseY <= (poisonModePosY + 9)))
		{
			chosenMode = 3;
		}
		else
			chosenMode = 0;
	}
	else
		chosenMode = 0;

	if (wnd.mouse.LeftIsPressed() && chosenMode != 0)
	{
		gameIsStarted = true;
		startingDelay = 0.0f;
	}
	else
	{
		gameIsStarted = false;
	}
}

void Game::ComposeFrame()
{
	if (!gameIsStarted)
	{
		SpriteCodex::DrawChooseMode(ModesPosX, chooseModePosY, gfx);

		if (chosenMode == 1)
			SpriteCodex::DrawNormalModeSelected(ModesPosX, normalModePosY, gfx);
		else
			SpriteCodex::DrawNormalMode(ModesPosX, normalModePosY, gfx);

		if (chosenMode == 2)
			SpriteCodex::DrawObstacleModeSelected(ModesPosX, obstacleModePosY, gfx);
		else
			SpriteCodex::DrawObstacleMode(ModesPosX, obstacleModePosY, gfx);

		if (chosenMode == 3) 
			SpriteCodex::DrawPoisonModeSelected(ModesPosX, poisonModePosY, gfx);
		else
			SpriteCodex::DrawPoisonMode(ModesPosX, poisonModePosY, gfx);

	}
	else
	{
		score.DrawScorePanel(gfx);
		for (int i = 0; i < 3 - lostLives; ++i)
		{
			Lives::DrawRed(355 + i * 40, 13, gfx);
		}
		brd.DrawBorder();

		if (gameIsStarted)
		{
			if (startingDelay > 4)
			{
				brd.DrawObstacles();
				
				goal.Draw(brd);
				if (highGoalSpawned)
				{
					highgoal.UpdateColor();
					highgoal.Draw(brd);
				}
				
				snek.Draw(brd);

				if (gameIsPaused)
				{
					SpriteCodex::DrawPause(157, 230, gfx);
				}
			}
			else
			{
				if (startingDelay <= 1)
					SpriteCodex::DrawNumber3(240, 260, gfx);
				else if (startingDelay <= 2)
					SpriteCodex::DrawNumber2(240, 260, gfx);
				else if (startingDelay <= 3)
					SpriteCodex::DrawNumber1(240, 260, gfx);
				else if (startingDelay <= 4)
					SpriteCodex::DrawGO(240, 260, gfx);
			}
		}

		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(198, 230, gfx);
			if (lostLives < 3)
			{
				SpriteCodex::DrawPressC(165, 465, gfx);
			}
			SpriteCodex::DrawPressR(167, 470, gfx);
		}
		if (gameIsWon)
		{
			SpriteCodex::DrawYouWin(146, 210, gfx);
			SpriteCodex::DrawPressR(167, 470, gfx);
		}
	}
}