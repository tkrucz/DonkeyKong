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

void noMainMenuFlag(Stage* stage);

void noStageFlags(Stage* stage);

void writeNameFlagsOne(Stage* stage);

void chooseStageFlags(Stage* stage);

void scoreboardFlag(Stage* stage);

void displayHittedByBarrelMenu(Stage* stage, SDLConst* SDL);

void readBarrelMenuKeys(Stage* stage, SDLConst* SDL);

void stopShowingBarrelMenu(Stage* stage);

void emptyName(Stage* stage, SDLConst* SDL);

void writeName(Stage* stage, SDLConst* SDL);

void deletingLetterFromName(Stage* stage);

void nameConfirmFlags(Stage* stage);

void noNewGameFlags(Stage* stage);

void noChooseStageFlag(Stage* stage);

void noScoreboardFlag(Stage* stage);

void addingLetterToName(Stage* stage, SDLConst* SDL);

void chooseStage(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void changeStageFlags(Stage* stage);

void noSuchStage(Stage* stage);

void finishGameMenu(Stage* stage, SDLConst* SDL, Score* score);

void readFinishGameMenuKeys(Stage* stage, SDLConst* SDL);

void writeNameFlagsTwo(Stage* stage);

void printMessage(Stage* stage, SDLConst* SDL);

void setMessage(Stage* stage, SDLConst* SDL);

void stageSpecifierKeyHandle(Stage* stage, SDLConst* SDL, Animator* animator, Score* score);

void quit(Stage* stage, SDLConst* SDL);

void initializePlayer(Stage* stage);


void displayMainMenu(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
{
	if (stage->menu.showMenu)
	{
		printMessage(stage, SDL);
		sprintf(stage->menu.text, "KING DONKEY");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_TITLE_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "START NEW GAME - N");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_START_KEY_ROW, stage->menu.text, SDL->charset);
		displayNamePart(stage, SDL);
		displayStagePart(stage, SDL);		
		sprintf(stage->menu.text, "CHECK THE BEST SCORES - P");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_SCORE_KEY_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "EXIT THE GAME - ESC");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_EXIT_KEY_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "%s", stage->menu.message);
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_MESSAGE_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->gameInfo.text, "Author: Tomasz Kruczalak 198049");
		DrawString(SDL->screen, ZERO_COLUMN, AUTHOR_INFO_ROW, stage->gameInfo.text, SDL->charset);
		if (stage->menu.scoreboard)
			displayScores(stage, SDL, colors);
		readMainMenuKeys(stage, SDL, colors, animator, score);
	}
}

void displayNamePart(Stage* stage, SDLConst* SDL)
{
	if (!stage->menu.nameConfirmed)
	{
		sprintf(stage->menu.text, "ENTER YOUR NAME - W");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_NAME_ROW, stage->menu.text, SDL->charset);
	}
	else
	{
		sprintf(stage->menu.text, "PLAYER NAME: %s", stage->player.name);
		DrawString(SDL->screen, NAME_COLUMN, MENU_NAME_ROW, stage->menu.text, SDL->charset);
	}
	if (stage->menu.nameEnter)
	{
		sprintf(stage->menu.text, "ENTERED NAME (press ENTER to confirm) : %s", stage->player.name);
		DrawString(SDL->screen, WRITING_NAME_COLUMN, MENU_WRITING_NAME_ROW, stage->menu.text, SDL->charset);
	}
}

void displayStagePart(Stage* stage, SDLConst* SDL)
{
	sprintf(stage->menu.text, "CHOOSE STAGE - L");
	DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_STAGE_ROW, stage->menu.text, SDL->charset);
	if (stage->stageSpecifier == STAGE1 || stage->stageSpecifier == STAGE2 || stage->stageSpecifier == STAGE3)
	{
		sprintf(stage->menu.text, "CHOOSEN STAGE: %d", stage->stageSpecifier + ONE);
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_STAGE_ROW, stage->menu.text, SDL->charset);
	}
	if (stage->menu.stageChoose)
	{
		sprintf(stage->menu.text, "CHOOSE STAGE FROM: 1, 2, 3");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, MENU_CHOOSE_STAGE_ROW, stage->menu.text, SDL->charset);
	}
}

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
						noMainMenuFlag(stage);
					else
					{
						noStageFlags(stage);
						break;
					}
				else if (keyPressed == SDLK_w)
					writeNameFlagsOne(stage);
				else if (keyPressed == SDLK_l)
					chooseStageFlags(stage);
				else if (keyPressed == SDLK_p)
					scoreboardFlag(stage);
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

void noMainMenuFlag(Stage* stage)
{
	stage->menu.showMenu = false;
}

void noStageFlags(Stage* stage)
{
	stage->menu.noneStage = true;
	stage->menu.defaultMessage = false;
}

void writeNameFlagsOne(Stage* stage)
{
	stage->menu.nameEnter = true;
	stage->menu.defaultMessage = true;
	stage->menu.scoreboard = false;
}

void chooseStageFlags(Stage* stage)
{
	stage->menu.stageChoose = true;
	stage->menu.defaultMessage = true;
	stage->menu.scoreboard = false;
}

void scoreboardFlag(Stage* stage)
{
	stage->menu.scoreboard = true;
}

void displayHittedByBarrelMenu(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.showBarrelMenu)
	{
		sprintf(stage->menu.text, "Player score : %.6d", stage->playerInfo.score);
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, BARREL_MENU_PLAYER_SCORE, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "You are hitted by barrel");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, BARREL_MENU_ALERT, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "You want to continue?");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, BARREL_MENU_CONTINUE, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "YES - Y , NO (quit the game) - Esc, NO (save score and then quit) - S");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, BARREL_MENU_KEYS, stage->menu.text, SDL->charset);
		readBarrelMenuKeys(stage, SDL);
	}
}

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
				stopShowingBarrelMenu(stage);
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

void stopShowingBarrelMenu(Stage* stage)
{
	stage->menu.showBarrelMenu = false;
}

void emptyName(Stage* stage, SDLConst* SDL)
{
	for (int i = 0; i < NAME_LENGTH; i++)
		stage->player.name[i] = ' ';
	stage->player.name[NAME_LENGTH] = '\0';
}

void writeName(Stage* stage, SDLConst* SDL)
{
	int keyPressed = SDL->event.key.keysym.sym;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_BACKSPACE)
			deletingLetterFromName(stage);	
		else if (keyPressed == SDLK_RETURN)
			nameConfirmFlags(stage);
		else if (keyPressed == SDLK_n)
		{
			noNewGameFlags(stage);
			addingLetterToName(stage, SDL);
		}
		else if (keyPressed == SDLK_w)
			addingLetterToName(stage, SDL);		
		else if (keyPressed == SDLK_l)
		{
			noChooseStageFlag(stage);
			addingLetterToName(stage, SDL);
		}
		else if (keyPressed == SDLK_p)
		{
			noScoreboardFlag(stage);
			addingLetterToName(stage, SDL);
		}
		else
			addingLetterToName(stage, SDL);
	case SDL_KEYUP:
		break;
	}
}

void deletingLetterFromName(Stage* stage)
{
	stage->player.name[stage->menu.index] = '\0';
	stage->menu.index--;
}

void nameConfirmFlags(Stage* stage)
{
	stage->menu.nameEnter = false;
	stage->menu.nameConfirmed = true;
}

void noNewGameFlags(Stage* stage)
{
	stage->menu.showMenu = true;
	stage->menu.noneStage = false;
}

void noChooseStageFlag(Stage* stage)
{
	stage->menu.stageChoose = false;
}

void noScoreboardFlag(Stage* stage)
{
	stage->menu.scoreboard = false;
}
void addingLetterToName(Stage* stage, SDLConst* SDL)
{
	int keyPressed = SDL->event.key.keysym.sym;
	stage->player.name[stage->menu.index] = (char)(keyPressed);
	stage->menu.index++;
}

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
			noSuchStage(stage);
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

void noSuchStage(Stage* stage)
{
	stage->menu.wrongStage = true;
	stage->menu.defaultMessage = false;
}

void finishGameMenu(Stage* stage, SDLConst* SDL, Score* score)
{
	if (stage->stageSpecifier == STAGE3 && score->endTheStage == 0)
	{
		initializePlayer(stage);
		stage->menu.showFinishMenu = true;
		sprintf(stage->menu.text, "YOU HAVE FINISHED THE GAME");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, FINISH_GAME_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "Player name (edit by pressing W, confirm by pressing ENTER) : %s", stage->player.name);
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, FINISH_NAME_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "Player score : %.6d", stage->playerInfo.score);
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, FINISH_SCORE_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "Game Time %.1lf s", stage->gameInfo.gameTime);
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, FINISH_TIME_ROW, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "ESC-quit, S- save the game result");
		DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->menu.text) * EIGHT / TWO, FINISH_KEYS_ROW, stage->menu.text, SDL->charset);
		readFinishGameMenuKeys(stage, SDL);
	}
}

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
				writeNameFlagsTwo(stage);
			break;
		case SDL_QUIT:
			quit(stage, SDL);
			break;
		}
		if (stage->menu.nameEnter)
			writeName(stage, SDL);	
	}
}

void writeNameFlagsTwo(Stage* stage)
{
	stage->menu.nameEnter = true;
	stage->menu.nameConfirmed = false;
}

void printMessage(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.defaultMessage)
	{
		for (int i = 0; i < DEFAULT_MESSAGE_LENGTH; i++)
		{
			stage->menu.message[i] = ' ';
		}
		stage->menu.message[DEFAULT_MESSAGE_LENGTH] = '\0';
	}
	else if (!stage->menu.defaultMessage)
		setMessage(stage, SDL);
}

void setMessage(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.wrongStage)
	{
		char message[] = "CHOOSE THE CORRECT STAGE";
		for (int i = 0; i < STAGE_MESSAGE_LENGTH; i++)
			stage->menu.message[i] = message[i];
	}
	else if (stage->menu.noneStage)
	{
		char message[] = "YOU CAN'T START A GAME WITHOUT STAGE";
		for (int i = 0; i < NEW_GAME_MESSAGE_LENGTH; i++)
			stage->menu.message[i] = message[i];
	}
}