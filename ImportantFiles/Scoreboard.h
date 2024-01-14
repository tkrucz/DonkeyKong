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

void checkSavesFileRowsNumber(Stage* stage);

void displayScores(Stage* stage, SDLConst* SDL, Color* colors)
{
	int startRow = SCOREBOARD_PLAYERS_ROW;
	sortScore(stage, SDL);
	readScoreKeys(stage, SDL);
	sprintf(stage->menu.text, "SCOREBOARD");
	DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, SCOREBOARD_TITLE_ROW, stage->menu.text, SDL->charset);
	DrawRectangle(SDL->screen, SCOREBOARD_COLUMN, SCOREBOARD_ROW, SCOREBOARD_LENGTH, SCOREBOARD_HEIGHT, colors->white, colors->black);
	int page = stage->page;
	int startIndex = page * SCORES_PER_PAGE;
	int endIndex = startIndex + SCORES_PER_PAGE;
	if (endIndex > stage->numberOfPlayersInFile)
		endIndex = stage->numberOfPlayersInFile;

	for (int i = startIndex; i < endIndex; i++)
	{
		if (stage->scoreboard[i].score >= NULL_POINTS)
		{
			sprintf(stage->menu.text, "Player: %s | Score: %d | Lives: %d ", stage->scoreboard[i].name, stage->scoreboard[i].score, stage->scoreboard[i].lives);
			DrawString(SDL->screen, SCOREBOARD_PLAYERS_COLUMN, startRow + (i - startIndex) * TWENTY, stage->menu.text, SDL->charset);
		}
	}
}

void sortScore(Stage* stage, SDLConst* SDL)
{
	checkSavesFileRowsNumber(stage);
	loadPlayersScore(stage);
	for (int j = 0; j < stage->numberOfPlayersInFile; j++)
	{
		int max = stage->scoreboard[j].score;
		int index = j;
		for (int i = j + 1; i < stage->numberOfPlayersInFile; i++)
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
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_RIGHT)
		{
			if (stage->canChangePage == false)
			{
				stage->canChangePage = true;
				stage->page++;
			}
		}
		else if (keyPressed == SDLK_LEFT)
		{
			stage->page--;
			if (stage->page < NULL)
				stage->page = NULL;
		}
		break;
	case SDL_KEYUP:
		stage->canChangePage = false;
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
	checkSavesFileRowsNumber(stage);
	char filename[] = "Saves.txt";
	FILE* file = fopen(filename, "r");

	if (file != NULL)
	{
		for (int i = 0; i < stage->numberOfPlayersInFile; i++)
		{
			if (fscanf(file, "Player Name: %s\n", stage->scoreboard[i].name) != ONE ||
				fscanf(file, "Score: %d\n", &stage->scoreboard[i].score) != ONE ||
				fscanf(file, "Lives: %d\n", &stage->scoreboard[i].lives) < ONE)
			{
				break;
			}
		}
		fclose(file);
	}
}

void checkSavesFileRowsNumber(Stage* stage)
{
	int rowsNumber=0;
	int character;
	char filename[] = "Saves.txt";
	FILE* file = fopen(filename, "r");

	while ((character = fgetc(file)) != EOF) {
		if (character == '\n') {
			rowsNumber++;
		}
	}
	stage->numberOfPlayersInFile = rowsNumber / THREE;
	stage->scoreboard = new Scoreboard[rowsNumber / THREE];
	fclose(file);
	delete[]stage->scoreboard;
}