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

void jumpOverBarrel(PlayerInfo* playerInfo, Score* score, Barrel* barrels);

void getTrophy(PlayerInfo* playerInfo, Score* score, Trophy* trophies);

void endTheStage(PlayerInfo* playerInfo, Score* score);

void addScore(PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies);

void deltaScore(PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies);

void jumpOverBarrel(PlayerInfo* playerInfo, Score* score, Barrel* barrels)
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
				score->deltaScore = barrels[i].barrelScore;
				barrels[i].barrelScore = ZERO;
				break;
			}
		}
		barrels[i].barrelScore = JUMP_OVER_BARREL_POINTS;
	}
}

void getTrophy(PlayerInfo* playerInfo, Score* score, Trophy* trophies)
{
	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		if (Mario.lowerCoordinates.y == trophies[i].lowerCoordinates.y + TROPHIES_DIFFERENCE_IN_Y &&
			Mario.lowerCoordinates.x >= trophies[i].lowerCoordinates.x - trophies[i].realSize[0] &&
			Mario.lowerCoordinates.x <= trophies[i].lowerCoordinates.x + trophies[i].realSize[0])
		{
			playerInfo->score += score->getTrophy;
			score->deltaScore = score->getTrophy;
			trophies[i].lowerCoordinates.x = FIVE_HUNDRED_EIGHTY_COLUMN + (i * TROPHIES_REAL_SIZE);
			trophies[i].lowerCoordinates.y = AUTHOR_INFO_ROW + THREE;
			return;
		}
	}
}

void endTheStage(PlayerInfo* playerInfo, Score* score)
{
	if (Mario.lowerCoordinates.y == PLATFORM_V_HEIGHT)
	{
		playerInfo->score += score->endTheStage;
		score->deltaScore = score->endTheStage;
		score->endTheStage = ZERO;
	}
}

void addScore(PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies)
{
	jumpOverBarrel(playerInfo, score, barrels);
	getTrophy(playerInfo, score, trophies);
	endTheStage(playerInfo, score);
}

void deltaScore(PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies)
{
	addScore(playerInfo, score, barrels, trophies);
	if (score->deltaScore > 0)
	{
		//tutaj printowanie aktualnego deltaScore
	}
	score->deltaScore = ZERO;
}