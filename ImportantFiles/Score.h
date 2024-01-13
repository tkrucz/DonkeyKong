#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "GeneralFunctions.h"
#include "PlayerFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void jumpOverBarrel(Stage* stage, Score* score, ShowText* showText);

void getTrophy(Stage* stage, Score* score, ShowText* showText);

void endTheStage(Stage* stage, SDLConst* SDL, Score* score);

void addScore(Stage* stage, SDLConst* SDL, Score* score, ShowText* showText);

void deltaScore(Stage* stage, SDLConst* SDL, Score* score, ShowText* showText);


void jumpOverBarrel(Stage* stage, Score* score, ShowText* showText)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (stage->player.isJumping || stage->player.fallDown)
		{
			if (stage->player.lowerCoordinates.y <= stage->barrels[i].lowerRightCoordinates.y + BARRELS_DIFFERENCE_IN_Y &&
				stage->player.lowerCoordinates.y >= stage->barrels[i].lowerRightCoordinates.y - MAX_DIFFERNECE_DISTANCE &&
				stage->barrels[i].lowerRightCoordinates.x <= stage->player.lowerCoordinates.x + stage->player.realSize[0] &&
				stage->barrels[i].lowerRightCoordinates.x - BARRELS_HITBOX_SIZE >= stage->player.lowerCoordinates.x)
			{
				stage->playerInfo.score += stage->barrels[i].barrelScore;
				if (stage->barrels[i].barrelScore > NULL_POINTS)
				{
					score->deltaScore = stage->barrels[i].barrelScore;
					showText->time.actualShowingTime = 0;
					showText->isVisible = true;
				}
				stage->barrels[i].barrelScore = NULL_POINTS;
				break;
			}
		}
		stage->barrels[i].barrelScore = JUMP_OVER_BARREL_POINTS;
	}
}

void getTrophy(Stage* stage, Score* score, ShowText* showText)
{
	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		if (stage->player.lowerCoordinates.y == stage->trophies[i].lowerCoordinates.y + TROPHIES_DIFFERENCE_IN_Y &&
			stage->player.lowerCoordinates.x >= stage->trophies[i].lowerCoordinates.x - stage->trophies[i].realSize[0] &&
			stage->player.lowerCoordinates.x <= stage->trophies[i].lowerCoordinates.x + stage->trophies[i].realSize[0])
		{
			stage->playerInfo.score += score->getTrophy;
			score->deltaScore = score->getTrophy;
			showText->time.actualShowingTime = 0;
			showText->isVisible = true;
			stage->trophies[i].lowerCoordinates.x = FIVE_HUNDRED_EIGHTY_COLUMN + (i * TROPHIES_REAL_SIZE);
			stage->trophies[i].lowerCoordinates.y = AUTHOR_INFO_ROW + THREE;
			return;
		}
	}
}

void endTheStage(Stage* stage, SDLConst* SDL, Score* score)
{
	if (stage->player.lowerCoordinates.y == PLATFORM_V_HEIGHT && stage->stageSpecifier != STAGE3)
	{
		sprintf(stage->player.text, "You have finished the stage. Press 1,2,3 to change the levels.");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->player.text) * EIGHT / TWO, stage->player.lowerCoordinates.y - stage->player.realSize[1] - FIFTEEN , stage->player.text, SDL->charset);
		stage->playerInfo.score += score->endTheStage;
		score->deltaScore = score->endTheStage;
		score->endTheStage = NULL_POINTS;
	}
	else if (stage->player.lowerCoordinates.y == PLATFORM_V_HEIGHT && stage->stageSpecifier == STAGE3)
	{
		stage->playerInfo.score += score->endTheStage;
		score->deltaScore = score->endTheStage;
		score->endTheStage = NULL_POINTS;
		finishGameMenu(stage, SDL, score);
	}
}

void addScore(Stage* stage, SDLConst* SDL, Score* score, ShowText* showText)
{
	jumpOverBarrel(stage, score, showText);
	getTrophy(stage, score, showText);
	endTheStage(stage, SDL, score);
}

void deltaScore(Stage* stage, SDLConst* SDL, Score* score, ShowText* showText)
{
	addScore(stage, SDL, score, showText);
	if (score->deltaScore > NULL_POINTS)
	{
		if( showText->time.actualShowingTime <= showText->time.showingTime)
		{
			sprintf(stage->player.text, "%d", score->deltaScore);
			DrawString(SDL->screen, stage->player.lowerCoordinates.x, stage->player.lowerCoordinates.y - stage->player.realSize[1] - FIFTEEN, stage->player.text, SDL->charset);
			showText->time.actualShowingTime += stage->gameInfo.deltaTime;
		}
		else
		{
			showText->isVisible = false;
			score->deltaScore = NULL_POINTS;
		}
	}
}