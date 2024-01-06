#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "define.h"
#include "structures.h"
#include "GameStructure.h"
#include "GeneralFunctions.h"
#include "PlayerFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void jumpOverBarrel(PlayerInfo* playerInfo, Score* score, Barrel* barrels, ShowText* showText);

void getTrophy(PlayerInfo* playerInfo, Score* score, Trophy* trophies, ShowText* showText);

void endTheStage(SDLConst* SDL, PlayerInfo* playerInfo, Score* score);

void addScore(SDLConst* SDL, PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies, ShowText* showText);

void deltaScore(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies, ShowText* showText);

void jumpOverBarrel(PlayerInfo* playerInfo, Score* score, Barrel* barrels, ShowText* showText)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (Mario.isJumping || Mario.fallDown)
		{
			if (Mario.lowerCoordinates.y <= barrels[i].lowerRightCoordinates.y - BARRELS_DIFFERENCE_IN_Y &&
				barrels[i].lowerRightCoordinates.x >= Mario.lowerCoordinates.x &&
				barrels[i].lowerRightCoordinates.x + BARRELS_HITBOX_SIZE <= Mario.lowerCoordinates.x + Mario.realSize[0])
			{
				playerInfo->score += barrels[i].barrelScore;
				if (barrels[i].barrelScore > 0)
				{
					score->deltaScore = barrels[i].barrelScore;
					showText->actualShowingTime = ZERO;
					showText->isVisible = true;
				}
				barrels[i].barrelScore = ZERO;
				break;
			}
		}
		barrels[i].barrelScore = JUMP_OVER_BARREL_POINTS;
	}
}

void getTrophy(PlayerInfo* playerInfo, Score* score, Trophy* trophies, ShowText* showText)
{
	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		if (Mario.lowerCoordinates.y == trophies[i].lowerCoordinates.y + TROPHIES_DIFFERENCE_IN_Y &&
			Mario.lowerCoordinates.x >= trophies[i].lowerCoordinates.x - trophies[i].realSize[0] &&
			Mario.lowerCoordinates.x <= trophies[i].lowerCoordinates.x + trophies[i].realSize[0])
		{
			playerInfo->score += score->getTrophy;
			score->deltaScore = score->getTrophy;
			showText->actualShowingTime = ZERO;
			showText->isVisible = true;
			trophies[i].lowerCoordinates.x = FIVE_HUNDRED_EIGHTY_COLUMN + (i * TROPHIES_REAL_SIZE);
			trophies[i].lowerCoordinates.y = AUTHOR_INFO_ROW + THREE;
			return;
		}
	}
}

void endTheStage(SDLConst* SDL, PlayerInfo* playerInfo, Score* score)
{
	if (Mario.lowerCoordinates.y == PLATFORM_V_HEIGHT)
	{
		sprintf(Mario.text, "You have finished the stage. Press 1,2,3 to change the levels.");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(Mario.text) * 8 / 2, Mario.lowerCoordinates.y - Mario.realSize[1] - FIFTEEN , Mario.text, SDL->charset);
		playerInfo->score += score->endTheStage;
		score->deltaScore = score->endTheStage;
		score->endTheStage = ZERO;
	}
}

void addScore(SDLConst* SDL, PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies, ShowText* showText)
{
	jumpOverBarrel(playerInfo, score, barrels,showText);
	getTrophy(playerInfo, score, trophies,showText);
	endTheStage(SDL, playerInfo, score);
}

void deltaScore(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies, ShowText* showText)
{
	addScore(SDL, playerInfo, score, barrels, trophies,showText);
	if (score->deltaScore > 0)
	{
		if( showText->actualShowingTime <= showText->showingTime)
		{
			sprintf(Mario.text, "%d", score->deltaScore);
			DrawString(SDL->screen, Mario.lowerCoordinates.x, Mario.lowerCoordinates.y - Mario.realSize[1] - FIFTEEN, Mario.text, SDL->charset);
			showText->actualShowingTime += gameInfo->deltaTime;
		}
		else
			showText->isVisible = false;
	}
}