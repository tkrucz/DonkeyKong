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

void displayMenu(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void readMenuKeys(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void emptyName(Stage* stage, SDLConst* SDL);

void writeName(Stage* stage, SDLConst* SDL);

void chooseStage(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void stageSpecifierKeyHandle(Stage* stage, SDLConst* SDL, Animator* animator, Score* score);

void defaultMessage(Stage* stage, SDLConst* SDL);

void setMessage(Stage* stage, SDLConst* SDL);

void quit(Stage* stage, SDLConst* SDL);


void displayMenu(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
{
	emptyName(stage, SDL);
	if (stage->menu.showMenu)
	{
		defaultMessage(stage, SDL);
		sprintf(stage->menu.text, "KING DONKEY");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 50, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "START NEW GAME - N");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 100, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "ENTER YOUR NAME - W");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 120, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "CHOOSE STAGE - S");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 140, stage->menu.text, SDL->charset);
		if (stage->stageSpecifier == STAGE1 || stage->stageSpecifier == STAGE2 || stage->stageSpecifier == STAGE3)
		{
			sprintf(stage->menu.text, "CHOOSEN STAGE: %d", stage->stageSpecifier + 1);
			DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 140, stage->menu.text, SDL->charset);
		}
		sprintf(stage->menu.text, "CHECK PLAYER SCORE");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 160, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "EXIT THE GAME - ESC");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 180, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "%s", stage->menu.message);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 260, stage->menu.text, SDL->charset);
		if (stage->menu.nameEnter)
		{
			sprintf(stage->menu.text, "ENTERED NAME: %s", stage->menu.name);
			DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 220, stage->menu.text, SDL->charset);
		}
		if (stage->menu.stageChoose)
		{
			sprintf(stage->menu.text, "CHOOSE STAGE FROM: 1, 2, 3");
			DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 240, stage->menu.text, SDL->charset);
		}
		readMenuKeys(stage, SDL, colors, animator, score);
	}
}

void readMenuKeys(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
{
	if (stage->menu.showMenu)
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
					stage->menu.showMenu = false;
				else if (keyPressed == SDLK_w)
					stage->menu.nameEnter = true;
				else if (keyPressed == SDLK_s)
					stage->menu.stageChoose = true;
				//	else if (keyPressed == SDLK_p)
						//checkPlayersScore();
				break;
			case SDL_QUIT: //X button in right up corner
				quit(stage, SDL);
				break;
			}
			if (stage->menu.nameEnter)
				writeName(stage, SDL);
			else if (stage->menu.stageChoose)
				chooseStage(stage, SDL, colors, animator, score);
		}
	}
}

void emptyName(Stage* stage, SDLConst* SDL)
{
	for (int i = 0; i < 15; i++)
		stage->menu.name[i] = ' ';
	stage->menu.name[15] = '\0';
}

void writeName(Stage* stage, SDLConst* SDL)
{
	int keyPressed = SDL->event.key.keysym.sym;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_BACKSPACE)
		{
			stage->menu.name[stage->menu.index] = '\0';
			stage->menu.index--;
		}
		else if (keyPressed == SDLK_c)
			stage->menu.nameEnter = false;
		else
		{
			stage->menu.name[stage->menu.index] = (char)(keyPressed);
			stage->menu.index++;
		}
	case SDL_KEYUP:
		break;
	}
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
			stage->menu.stageChoose = false;
			stage->menu.wrongStage = false;
			stage->menu.defaultMessage = true;
		}
		else if (keyPressed == SDLK_2)
		{
			stageSpecifierKeyHandle(stage, SDL, animator, score);
			stage->menu.stageChoose = false;
			stage->menu.wrongStage = false;
			stage->menu.defaultMessage = true;
		}
		else if (keyPressed == SDLK_3)
		{
			stageSpecifierKeyHandle(stage, SDL, animator, score);
			stage->menu.stageChoose = false;
			stage->menu.wrongStage = false;
			stage->menu.defaultMessage = true;
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

void defaultMessage(Stage* stage, SDLConst* SDL)
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

void setMessage(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.wrongStage)
	{
		char message[] = "CHOOSE THE CORRECT ROW";
		for (int i = 0; i < 24; i++)
			stage->menu.message[i] = message[i];
	}
}