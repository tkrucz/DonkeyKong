#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "GeneralFunctions.h"
#include "Scoreboard.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void displayMainMenu(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void displayNamePart(Stage* stage, SDLConst* SDL);

void displayStagePart(Stage* stage, SDLConst* SDL);

void readMainMenuKeys(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void displayHittedByBarrelMenu(Stage* stage, SDLConst* SDL);

void readBarrelMenuKeys(Stage* stage, SDLConst* SDL);

void emptyName(Stage* stage, SDLConst* SDL);

void writeName(Stage* stage, SDLConst* SDL);

void addingLetterToName(Stage* stage, SDLConst* SDL);

void chooseStage(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void changeStageFlags(Stage* stage);

void finishGameMenu(Stage* stage, SDLConst* SDL, Score* score);

void readFinishGameMenuKeys(Stage* stage, SDLConst* SDL);

void printMessage(Stage* stage, SDLConst* SDL);

void setMessage(Stage* stage, SDLConst* SDL);

void stageSpecifierKeyHandle(Stage* stage, SDLConst* SDL, Animator* animator, Score* score);

void quit(Stage* stage, SDLConst* SDL);

void initializePlayer(Stage* stage);


//TODO magic numbers
void displayMainMenu(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
{
	if (stage->menu.showMenu)
	{
		printMessage(stage, SDL);
		sprintf(stage->menu.text, "KING DONKEY");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 50, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "START NEW GAME - N");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 100, stage->menu.text, SDL->charset);
		displayNamePart(stage, SDL);
		displayStagePart(stage, SDL);		
		sprintf(stage->menu.text, "CHECK THE BEST SCORES - P");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 160, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "EXIT THE GAME - ESC");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 180, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "%s", stage->menu.message);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 260, stage->menu.text, SDL->charset);
		sprintf(stage->gameInfo.text, "Author: Tomasz Kruczalak 198049");
		DrawString(SDL->screen, ZERO_COLUMN, AUTHOR_INFO_ROW, stage->gameInfo.text, SDL->charset);
		if (stage->menu.scoreboard)
			displayScores(stage, SDL, colors);
		readMainMenuKeys(stage, SDL, colors, animator, score);
	}
}

//TODO magic numbers
void displayNamePart(Stage* stage, SDLConst* SDL)
{
	if (!stage->menu.nameConfirmed)
	{
		sprintf(stage->menu.text, "ENTER YOUR NAME - W");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 120, stage->menu.text, SDL->charset);
	}
	else
	{
		sprintf(stage->menu.text, "PLAYER NAME: %s", stage->player.name);
		DrawString(SDL->screen, NAME_COLUMN, 120, stage->menu.text, SDL->charset);
	}
	if (stage->menu.nameEnter)
	{
		sprintf(stage->menu.text, "ENTERED NAME (press ENTER to confirm) : %s", stage->player.name);
		DrawString(SDL->screen, WRITING_NAME_COLUMN, 220, stage->menu.text, SDL->charset);
	}
}

//TODO magic numbers
void displayStagePart(Stage* stage, SDLConst* SDL)
{
	sprintf(stage->menu.text, "CHOOSE STAGE - L");
	DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 140, stage->menu.text, SDL->charset);
	if (stage->stageSpecifier == STAGE1 || stage->stageSpecifier == STAGE2 || stage->stageSpecifier == STAGE3)
	{
		sprintf(stage->menu.text, "CHOOSEN STAGE: %d", stage->stageSpecifier + 1);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 140, stage->menu.text, SDL->charset);
	}
	if (stage->menu.stageChoose)
	{
		sprintf(stage->menu.text, "CHOOSE STAGE FROM: 1, 2, 3");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 240, stage->menu.text, SDL->charset);
	}
}


// TODO: the same, one function in every key statement like here
// if (keyPressed == SDLK_ESCAPE)
// quit(stage, SDL);
void readMainMenuKeys(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
{
		while (SDL_PollEvent(&SDL->event))
		{
			int keyPressed = SDL->event.key.keysym.sym;
			switch (SDL->event.type)
			{
			case SDL_KEYDOWN:
				if (keyPressed == SDLK_ESCAPE)
					quit(stage, SDL);
				else if (keyPressed == SDLK_n)
					if (stage->stageSpecifier == STAGE1 || stage->stageSpecifier == STAGE2 || stage->stageSpecifier == STAGE3)
						stage->menu.showMenu = false;
					else
					{
						stage->menu.noneStage = true;
						stage->menu.defaultMessage = false;
						break;
					}
				else if (keyPressed == SDLK_w)
				{
					stage->menu.nameEnter = true;
					stage->menu.defaultMessage = true;
					stage->menu.scoreboard = false;
				}
				else if (keyPressed == SDLK_l)
				{
					stage->menu.stageChoose = true;
					stage->menu.defaultMessage = true; 
					stage->menu.scoreboard = false;
				}
				else if (keyPressed == SDLK_p)
					stage->menu.scoreboard = true;
				break;
			case SDL_QUIT:
				quit(stage, SDL);
				break;
			}
			if (stage->menu.nameEnter)
				writeName(stage, SDL);
			else if (stage->menu.stageChoose)
				chooseStage(stage, SDL, colors, animator, score);
			else if (stage->menu.scoreboard)
				displayScores(stage, SDL, colors);
		}
}

//TODO magic numbers 
void displayHittedByBarrelMenu(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.showBarrelMenu)
	{
		sprintf(stage->menu.text, "Player score : %.6d", stage->playerInfo.score);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 200, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "You are hitted by barrel");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 220, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "You want to continue?");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 240, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "YES - Y , NO (quit the game) - Esc, NO (save score and then quit) - S");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 250, stage->menu.text, SDL->charset);
		readBarrelMenuKeys(stage, SDL);
	}
}

//TODO to fucntion -> stage->menu.showBarrelMenu = false; 
void readBarrelMenuKeys(Stage* stage, SDLConst* SDL)
{
	while (SDL_PollEvent(&SDL->event))
	{
		int keyPressed = SDL->event.key.keysym.sym;
		switch (SDL->event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				quit(stage, SDL);
			else if (keyPressed == SDLK_y)
				stage->menu.showBarrelMenu = false; 
			else if (keyPressed == SDLK_s)
			{
				savePlayerScore(stage);
				quit(stage, SDL);
			}
			break;
		case SDL_QUIT:
			quit(stage, SDL);
			break;
		}		
	}
}

//TODO magic numbers
void emptyName(Stage* stage, SDLConst* SDL)
{
	for (int i = 0; i < 15; i++)
		stage->player.name[i] = ' ';
	stage->player.name[15] = '\0';
}

// TODO: the same, one function in every key statement like here
// if (keyPressed == SDLK_ESCAPE)
// quit(stage, SDL);
void writeName(Stage* stage, SDLConst* SDL)
{
	int keyPressed = SDL->event.key.keysym.sym;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_BACKSPACE)
		{
			stage->player.name[stage->menu.index] = '\0';
			stage->menu.index--;
		}
		else if (keyPressed == SDLK_RETURN)
		{
			stage->menu.nameEnter = false;
			stage->menu.nameConfirmed = true;
		}
		else if (keyPressed == SDLK_n)
		{
			stage->menu.showMenu = true;
			stage->menu.noneStage = false;
			addingLetterToName(stage, SDL);
		}
		else if (keyPressed == SDLK_w)
			addingLetterToName(stage, SDL);		
		else if (keyPressed == SDLK_l)
		{
			stage->menu.stageChoose = false;
			addingLetterToName(stage, SDL);
		}
		else if (keyPressed == SDLK_p)
		{
			stage->menu.scoreboard = false;
			addingLetterToName(stage, SDL);
		}
		else
			addingLetterToName(stage, SDL);
	case SDL_KEYUP:
		break;
	}
}

void addingLetterToName(Stage* stage, SDLConst* SDL)
{
	int keyPressed = SDL->event.key.keysym.sym;
	stage->player.name[stage->menu.index] = (char)(keyPressed);
	stage->menu.index++;
}

// TODO: the same, one function in every key statement like here
// if (keyPressed == SDLK_ESCAPE)
// quit(stage, SDL);
void chooseStage(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
{
	int keyPressed = SDL->event.key.keysym.sym;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_1)
		{
			stageSpecifierKeyHandle(stage, SDL, animator, score);
			changeStageFlags(stage);
		}
		else if (keyPressed == SDLK_2)
		{
			stageSpecifierKeyHandle(stage, SDL, animator, score);
			changeStageFlags(stage);
		}
		else if (keyPressed == SDLK_3)
		{
			stageSpecifierKeyHandle(stage, SDL, animator, score);
			changeStageFlags(stage);
		}
		else if (keyPressed != SDLK_1 && keyPressed != SDLK_2 && keyPressed != SDLK_3)
		{
			stage->menu.wrongStage = true;
			stage->menu.defaultMessage = false;
		}
		break;	
	case SDL_KEYUP:
		break;
	}
}

void changeStageFlags(Stage* stage)
{
	stage->menu.stageChoose = false;
	stage->menu.wrongStage = false;
	stage->menu.defaultMessage = true;
}


void finishGameMenu(Stage* stage, SDLConst* SDL, Score* score)
{
	if (stage->stageSpecifier == STAGE3 && score->endTheStage == 0)
	{
		initializePlayer(stage);
		stage->menu.showFinishMenu = true;
		sprintf(stage->menu.text, "YOU HAVE FINISHED THE GAME");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, FINISH_GAME_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "Player name (edit by pressing W, confirm by pressing ENTER) : %s", stage->player.name);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, FINISH_NAME_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "Player score : %.6d", stage->playerInfo.score);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, FINISH_SCORE_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "Game Time %.1lf s", stage->gameInfo.gameTime);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, FINISH_TIME_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "ESC-quit, S- save the game result");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, FINISH_KEYS_ROW, stage->menu.text, SDL->charset);
		readFinishGameMenuKeys(stage, SDL);
	}
}

//TODO jak chcesz
void readFinishGameMenuKeys(Stage* stage, SDLConst* SDL)
{
	while (SDL_PollEvent(&SDL->event))
	{
		int keyPressed = SDL->event.key.keysym.sym;
		switch (SDL->event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				quit(stage, SDL);
			else if (keyPressed == SDLK_s)
				savePlayerScore(stage);
			else if (keyPressed == SDLK_w)
			{
				stage->menu.nameEnter = true;
				stage->menu.nameConfirmed = false;
			}
			break;
		case SDL_QUIT:
			quit(stage, SDL);
			break;
		}
		if (stage->menu.nameEnter)
			writeName(stage, SDL);	
	}
}

//TODO ale magia
void printMessage(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.defaultMessage)
	{
		for (int i = 0; i < 39; i++)
		{
			stage->menu.message[i] = ' ';
		}
		stage->menu.message[39] = '\0';
	}
	else if (!stage->menu.defaultMessage)
		setMessage(stage, SDL);
}

//TODO znowu magia
void setMessage(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.wrongStage)
	{
		char message[] = "CHOOSE THE CORRECT STAGE";
		for (int i = 0; i < 25; i++)
			stage->menu.message[i] = message[i];
	}
	else if (stage->menu.noneStage)
	{
		char message[] = "YOU CAN'T START A GAME WITHOUT STAGE";
		for (int i = 0; i < 37; i++)
			stage->menu.message[i] = message[i];
	}
}