#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "GeneralFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void displayScores(Stage* stage, SDLConst* SDL, Color* colors);

void sortScore(Stage* stage, SDLConst* SDL);

void readScoreKeys(Stage* stage, SDLConst* SDL);

void savePlayerScore(Stage* stage);

void loadPlayersScore(Stage* stage);


void displayScores(Stage* stage, SDLConst* SDL, Color* colors)
{
	int startRow = SCOREBOARD_PLAYERS_ROW;
	sortScore(stage, SDL);
	readScoreKeys(stage, SDL);
	sprintf(stage->menu.text, "SCOREBOARD");
	DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, SCOREBOARD_TITLE_ROW, stage->menu.text, SDL->charset);
	DrawRectangle(SDL->screen, SCOREBOARD_COLUMN, SCOREBOARD_ROW, SCOREBOARD_LENGTH, SCOREBOARD_HEIGHT, colors->white, colors->black);
	int page = stage->scoreboard->page;
	int startIndex = page * SCORES_PER_PAGE;
	int endIndex = startIndex + SCORES_PER_PAGE;
	if (endIndex > MAX_NUMBER_OF_PLAYERS)
		endIndex = MAX_NUMBER_OF_PLAYERS;

	for (int i = startIndex; i < endIndex; i++)
	{
		if (stage->scoreboard[i].score >= 0)
		{
			sprintf(stage->menu.text, "Player: %s | Score: %d | Lives: %d ", stage->scoreboard[i].name, stage->scoreboard[i].score, stage->scoreboard[i].lives);
			DrawString(SDL->screen, SCOREBOARD_PLAYERS_COLUMN, startRow + (i - startIndex) * TWENTY, stage->menu.text, SDL->charset);
		}
	}
}

void sortScore(Stage* stage, SDLConst* SDL)
{
	loadPlayersScore(stage);
	for (int j = 0; j < MAX_NUMBER_OF_PLAYERS; j++)
	{
		int max = stage->scoreboard[j].score;
		int index = j;
		for (int i = j + 1; i < MAX_NUMBER_OF_PLAYERS; i++)
		{
			if (max < stage->scoreboard[i].score)
			{
				max = stage->scoreboard[i].score;
				index = i;
			}
		}
		Scoreboard temp = stage->scoreboard[j];
		stage->scoreboard[j] = stage->scoreboard[index];
		stage->scoreboard[index] = temp;
	}
}

void readScoreKeys(Stage* stage, SDLConst* SDL)
{
	int keyPressed = SDL->event.key.keysym.sym;
	//bool decreaseStage = false;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_RIGHT)
		{
			if (stage->scoreboard->canChangePage == false)
			{
				stage->scoreboard->canChangePage = true;
				stage->scoreboard->page++;
			}
		}
		if (keyPressed == SDLK_LEFT)
		{
			stage->scoreboard->page--;
			if (stage->scoreboard->page < 0)
				stage->scoreboard->page = 0;
		}
		break;
	case SDL_KEYUP:
		stage->scoreboard->canChangePage = false;
		break;
	}
}

void savePlayerScore(Stage* stage)
{
	char filename[] = "Saves.txt";
	FILE* file = fopen(filename, "a");

	fprintf(file, "Player Name: %s\n", stage->player.name);
	fprintf(file, "Score: %d\n", stage->playerInfo.score);
	fprintf(file, "Lives: %d\n", stage->playerInfo.lives);

	fclose(file);
}

void loadPlayersScore(Stage* stage)
{
	char filename[] = "Saves.txt";
	FILE* file = fopen(filename, "r");

	if (file != NULL)
	{
		for (int i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
		{
			if (fscanf(file, "Player Name: %s\n", stage->scoreboard[i].name) != 1 ||
				fscanf(file, "Score: %d\n", &stage->scoreboard[i].score) != 1 ||
				fscanf(file, "Lives: %d\n", &stage->scoreboard[i].lives) < 1)
			{
				break;
			}
		}
		fclose(file);
	}
}