#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "structures.h"
#include "define.h"
#include "SDLFunctions.h"
#include "ObjectsFunctions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

void createWindow(GameInfo* gameInfo);

void drawInfo(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors);

void drawScene(Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void displayWindow(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void refreshWindow();

void printGameInfo(GameInfo* gameInfo, Color* colors);

void printPlayerInfo(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors);

void drawGround(Color* colors);

void defaultSettings(GameInfo* gameInfo, PlayerInfo* playerInfo); //set up the game at the beginning

void newGameSettings(GameInfo* gameInfo, PlayerInfo* playerInfo, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies); //set up settings after pressing "n"

void loadStageSettings(GameInfo* gameInfo, PlayerInfo* playerInfo); //NOT USED


void initializePlayer();

void playerWalk(GameInfo* gameInfo); //move player in X axis by the current speedX

void playerClimb(GameInfo* gameInfo); //move player in Y axis by the current speedY

void approximateOnGround(GameInfo* gameInfo); //check if player is near the ground

void approximateOnPlatform(Platform* platforms); //check if player is near the platform, while falling down

void hitBottomOfThePlatform(Platform* platforms, GameInfo* gameInfo); //check if player hit the bottom of platform

void hitSidesOfThePlatform(Platform* platforms); //check if player hit the sides of platform

//check if player is jumping||falling down change his position by the current speedY, check if there is collision or if player should get points 
void gravityApply(GameInfo* gameInfo, PlayerInfo* playerInfo, Score* score, Platform* platforms, Barrel* barrels, Trophy* trophies);

void playerJump(); //give the speedY value -JumpingSpeed

void checkIfPlayerIsJumping();

void playerMovement(GameInfo* gameInfo);

void jumpOverBarrel(PlayerInfo* playerInfo, Score* score, Barrel* barrels);

void getTrophy(PlayerInfo* playerInfo, Score* score, Trophy* trophies);

void endTheStage(PlayerInfo* playerInfo, Score* score);

void addScore(PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies); 

void loseLive(GameInfo* gameInfo, PlayerInfo* playerInfo);


void timeCounting(GameInfo* gameInfo); //counting the game time


void playerOnLadderBeg();

void playerNotOnLadderBeg();

void playerOnLadderEnd();

void playerNotOnLadderEnd();

void playerOnLadder();

void playerNotOnLadder();

void playerOnPlatform();

void playerNotOnPlatform();

void playerFallingDown();

void playerNotFallingDown();

void playerJumping();

void playerNotJumping();

void playerOnGround();


void isPlayerOutsideTheBorders(); //check if player isn't outside of the screen borders

void isPlayerOnLadder(Ladder* ladders);

void isPlayerOnPlatform(Platform* platforms);

void isPlayerOnGround();

void whereIsPLayer(Platform* platforms, Ladder* ladders);


void whereAreObjects(Platform* platforms, Ladder* ladders, Barrel* barrels);

void collision(GameInfo* gameInfo, PlayerInfo* playerInfo, Barrel* barrels); 

void moveObjects(GameInfo* gameInfo, PlayerInfo* playerInfo, Barrel* barrels);


void readKeys(GameInfo* gameInfo, PlayerInfo* playerInfo, Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies); //read key input

void SDLSpace(); //freeing all surfaces

void quit(GameInfo* gameInfo);

/*Functions definitions
===================================================================
*/

void createWindow(GameInfo* gameInfo) // Create a window with specified size. Also create renderer for this window, renderer meaning a thing actually showing/drawing/rendering stuff
{
	gameInfo->err = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&SDL.window, &SDL.renderer);
	if (gameInfo->err != 0)
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(SDL.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(SDL.renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(SDL.window, "Tomasz Kruczalak 198049");

	SDL.screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL.scrtex = SDL_CreateTexture(SDL.renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);
}

void drawInfo(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors)
{
	printGameInfo(gameInfo,colors);
	printPlayerInfo(gameInfo, playerInfo, colors);
}

void drawScene(Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels,Trophy* trophies)
{
	drawGround(colors);
	drawPlatforms(colors, platforms);
	drawLadders(colors, ladders);
	drawTrophies(trophies);
	drawBarrels(barrels);
} 

void displayWindow(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	SDL_FillRect(SDL.screen, ZERO, colors->black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
	drawScene(colors, platforms, ladders, barrels,trophies);
	drawInfo(gameInfo, playerInfo,colors);
	DrawSurface(SDL.screen, SDL.player, Mario.lowerXCorner + PLAYER_DIFFERENCE_IN_X, Mario.lowerYCorner + PLAYER_DIFFERENCE_IN_Y, &Mario.animation); //draws the player
}

void refreshWindow()
{
	SDL_UpdateTexture(SDL.scrtex, ZERO, SDL.screen->pixels, SDL.screen->pitch);
	SDL_RenderCopy(SDL.renderer, SDL.scrtex, ZERO, ZERO);
	SDL_RenderPresent(SDL.renderer);
}

void printGameInfo(GameInfo* gameInfo, Color* colors)
{
	DrawRectangle(SDL.screen, ZERO_COLUMN, FIRST_ROW, SCREEN_WIDTH, 70, colors->white, colors->black);
	sprintf(gameInfo->text, "King Donkey");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo->text) * 8 / 2, 8, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Time from beginning: %.1lf s", gameInfo->gameTime);
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo->text) * 8 / 2, 25, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Esc - quit, n - new game ");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo->text) * 8 / 2, 40, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "\30 - move up, \31 - move down, \32 - move left, \33 - move right");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo->text) * 8 / 2, 55, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Author: Tomasz Kruczalak 198049");
	DrawString(SDL.screen, ZERO_COLUMN, AUTHOR_INFO_ROW, gameInfo->text, SDL.charset);
}

void printPlayerInfo(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors)
{
	DrawRectangle(SDL.screen, ZERO_COLUMN, 70, 120, 35, colors->white, colors->black);
	sprintf(gameInfo->text, "Score: %.6d", playerInfo->score);
	DrawString(SDL.screen, TEN_ROW, 75, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Lives: %d", playerInfo->lives);
	DrawString(SDL.screen, TEN_ROW, 90, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Trophies:");
	DrawString(SDL.screen, 500, AUTHOR_INFO_ROW, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "LeftLowerXCorner: %.0f", Mario.lowerXCorner);
	DrawString(SDL.screen, TEN_ROW, 150, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "LeftLowerYCorner: %.0f", Mario.lowerYCorner);
	DrawString(SDL.screen, TEN_ROW, 170, gameInfo->text, SDL.charset);
}


void drawGround(Color* colors)
{
	DrawLine(SDL.screen, ZERO_COLUMN, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, colors->white);
} 

void defaultSettings(GameInfo* gameInfo, PlayerInfo* playerInfo)
{
	gameInfo->quit = false;
	gameInfo->gameTime = ZERO;
	playerInfo->score = PLAYER_DEFAULT_POINTS;
	playerInfo->lives = PLAYER_DEFAULT_LIVES;
	initializePlayer();
}

void newGameSettings(GameInfo* gameInfo, PlayerInfo* playerInfo, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	defaultSettings(gameInfo, playerInfo);
	initializeGameObjects(platforms, ladders, barrels, trophies);
}

void loadStageSettings(GameInfo* gameInfo, PlayerInfo* playerInfo)
{
	gameInfo->quit = false;
	playerInfo->score = playerInfo->score;
	playerInfo->lives = playerInfo->lives;
	initializePlayer();
}

void initializePlayer()
{
	Mario.lowerXCorner = PLAYER_SPAWN_POINT_X;
	Mario.lowerYCorner = PLAYER_SPAWN_POINT_Y;
	//TODO comments
	Mario.animation = { DEAFULT_PLAYER_SPRITE_I + MARIO_BMP_DISTANCE, DEAFULT_PLAYER_SPRITE_II ,Mario.realSize[0],Mario.realSize[1] };
	Mario.speedX = NULL_SPEED;
	Mario.speedY = NULL_SPEED;
	playerOnPlatform();
}

void playerWalk(GameInfo* gameInfo)
{
	Mario.lowerXCorner += (Mario.speedX * gameInfo->deltaTime);
}

void playerClimb(GameInfo* gameInfo)
{
	if (Mario.begLadder && Mario.speedY >= 0)
		Mario.speedY = NULL_SPEED;
	if (Mario.endLadder && Mario.speedY <= 0)
		Mario.speedY = NULL_SPEED;
	Mario.lowerYCorner += (Mario.speedY * gameInfo->deltaTime);
}

void approximateOnGround(GameInfo* gameInfo)
{
	if (Mario.lowerYCorner + Mario.speedY + (GRAVITY_SPEED*gameInfo->deltaTime) >= GROUND_HEIGHT)
	{
		Mario.lowerYCorner = GROUND_HEIGHT;
		playerNotFallingDown();
		playerNotJumping();
	}
}

void approximateOnPlatform(Platform* platforms)
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (Mario.speedY > 0 && Mario.lowerYCorner > platforms[i].upperYCorner &&
			Mario.lowerYCorner < platforms[i].upperYCorner + platforms[i].width &&
			Mario.lowerXCorner<platforms[i].upperXCorner + platforms[i].length &&
			Mario.lowerXCorner + Mario.realSize[0]>platforms[i].upperXCorner)
		{
			Mario.lowerYCorner = platforms[i].upperYCorner;
			Mario.speedY = NULL_SPEED;
			playerNotFallingDown();
			playerNotJumping();
		}
	}
}

void hitBottomOfThePlatform(Platform* platforms, GameInfo* gameInfo) //check if player doesn't hit the bottom of the platform
{
	double upperYCorner = Mario.lowerYCorner - Mario.realSize[1]; //"-" beacuse y increases in down direction
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (upperYCorner <= platforms[i].upperYCorner + platforms[i].width &&
			upperYCorner > platforms[i].upperYCorner)
			if (platforms[i].upperXCorner <= Mario.lowerXCorner + Mario.realSize[0] && 
				Mario.lowerXCorner <= platforms[i].upperXCorner + platforms[i].length)
			{
				double elasticColision = gameInfo->deltaTime * ELASTIC_COLISION_CONST * (Mario.speedY + GRAVITY_SPEED * gameInfo->deltaTime);
				Mario.speedY = elasticColision; //dodać elastic colision do sturktury skok kiedyś?
			}
	}
}

void hitSidesOfThePlatform(Platform* platforms)
{
	double upperYCorner = Mario.lowerYCorner - Mario.realSize[1];
	double LeftCorner = Mario.lowerXCorner;
	double RightCorner = Mario.lowerXCorner + Mario.realSize[0];
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (LeftCorner <= platforms[i].upperXCorner + platforms[i].length && LeftCorner >= platforms[i].upperXCorner + platforms[i].length - ONE)
			if (upperYCorner <= platforms[i].upperYCorner + platforms[i].width && upperYCorner > platforms[i].upperYCorner)
			{
				Mario.lowerXCorner = platforms[i].upperXCorner + platforms[i].length;
				return;
			}
		if (RightCorner >= platforms[i].upperXCorner && RightCorner <= platforms[i].upperXCorner + ONE)
			if (upperYCorner <= platforms[i].upperYCorner + platforms[i].width && upperYCorner > platforms[i].upperYCorner)
				Mario.lowerXCorner = platforms[i].upperXCorner - Mario.realSize[0];
	}
}

//TODO KONIECZNIE WSZYSTKIE STRUKTURY/ZMIENNE NIE MOGA BYC GLOBALNE !!!!!! ////////////////////////////////////////////////////////////////
// collision, addScore?
void gravityApply(GameInfo* gameInfo, PlayerInfo* playerInfo, Score* score, Platform* platforms, Barrel* barrels, Trophy* trophies)
{
	addScore(playerInfo, score, barrels, trophies);
	if (Mario.isJumping || Mario.fallDown)
	{
		Mario.speedY += (GRAVITY_SPEED * gameInfo->deltaTime);
		Mario.lowerYCorner += Mario.speedY;
		approximateOnGround(gameInfo);
		hitBottomOfThePlatform(platforms, gameInfo);
		hitSidesOfThePlatform(platforms);
		approximateOnPlatform(platforms);

	}	
}

// TODO playerJumping to readKeys?
void playerJump()
{
	playerJumping();
	Mario.speedY = -JUMPING_SPEED;
}

void checkIfPlayerIsJumping() //no "double" jump or inifinity jump
{
	if (Mario.isJumping == true)
		return;
	else
		playerJump();
}

void playerMovement(GameInfo* gameInfo)
{
	if (Mario.onPlatform || Mario.isJumping || Mario.fallDown)
		playerWalk(gameInfo);
	if (Mario.onLadder)
		playerClimb(gameInfo);
	if (Mario.begLadder || Mario.endLadder)
	{
		playerWalk(gameInfo);
		playerClimb(gameInfo);
	}		
}

void jumpOverBarrel(PlayerInfo* playerInfo, Score* score, Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (Mario.isJumping || Mario.fallDown)
		{
			if (Mario.lowerYCorner <= barrels[i].lowerYCorner - BARRELS_DIFFERENCE_IN_Y  &&				
				barrels[i].lowerXCorner >= Mario.lowerXCorner  &&
				barrels[i].lowerXCorner + BARRELS_HITBOX_SIZE <= Mario.lowerXCorner + Mario.realSize[0])
			{
				playerInfo->score += barrels[i].barrelScore;
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
		if (Mario.lowerYCorner == trophies[i].lowerYCorner + TROPHIES_DIFFERENCE_IN_Y &&
			Mario.lowerXCorner >= trophies[i].lowerXCorner - trophies[i].realSize[0] &&
			Mario.lowerXCorner <= trophies[i].lowerXCorner + trophies[i].realSize[0])
		{
			playerInfo->score += score->getTrophy;
			trophies[i].lowerXCorner = 590 + (i * 20);
			trophies[i].lowerYCorner = AUTHOR_INFO_ROW + 4;
			return;			
		}
	}
}

void endTheStage(PlayerInfo* playerInfo, Score* score)
{
	if (Mario.lowerYCorner == PLATFORM_V_HEIGHT)
	{
		playerInfo->score += score->endTheStage;
		score->endTheStage = ZERO;
	}
}

void addScore(PlayerInfo* playerInfo, Score* score, Barrel* barrels, Trophy* trophies)
{
	jumpOverBarrel(playerInfo, score, barrels);
	getTrophy(playerInfo, score, trophies);
	endTheStage(playerInfo, score);
}

void loseLive(GameInfo* gameInfo, PlayerInfo* playerInfo)
{
	playerInfo->lives -= 1;
	if (playerInfo->lives == ZERO)
		quit(gameInfo);
}

void timeCounting(GameInfo* gameInfo)
{
	gameInfo->deltaTime = (gameInfo->t2 - gameInfo->t1) * 0.001;
	gameInfo->t1 = gameInfo->t2;
	gameInfo->gameTime += gameInfo->deltaTime;
}

void playerOnLadderBeg()
{
	Mario.begLadder = true;
}

void playerNotOnLadderBeg()
{
	Mario.begLadder = false;
}

void playerOnLadderEnd()
{
	Mario.endLadder = true;
}

void playerNotOnLadderEnd()
{
	Mario.endLadder = false;
}

void playerOnLadder()
{
	Mario.onLadder = true;
}

void playerNotOnLadder()
{
	Mario.onLadder = false;
}

void playerOnPlatform()
{
	Mario.onPlatform = true;
}

void playerNotOnPlatform()
{
	Mario.onPlatform = false;
}

void playerFallingDown()
{
	Mario.fallDown = true;
}

void playerNotFallingDown()
{
	Mario.fallDown = false;
}

void playerJumping()
{
	Mario.isJumping = true;
}

void playerNotJumping()
{
	Mario.isJumping = false;
}

void playerOnGround()
{
	Mario.onPlatform = true;
}

void isPlayerOutsideTheBorders()
{
	if (Mario.lowerXCorner <= ZERO)
		Mario.lowerXCorner = ZERO;
	if (Mario.lowerXCorner + Mario.realSize[0] >= SCREEN_WIDTH)
		Mario.lowerXCorner = SCREEN_WIDTH - Mario.realSize[0];
}

void isPlayerOnLadder(Ladder* ladders)
{
	int leftLowerCorner[2] = { Mario.lowerXCorner, Mario.lowerYCorner };
	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		if (ladders[i].upperXCorner <= Mario.lowerXCorner && Mario.lowerXCorner <= ladders[i].upperXCorner + ladders[i].width) //x increses in right direciton
		{
			//is Mario at the beginning of ladder?
			if (leftLowerCorner[1] == ladders[i].upperYCorner + ladders[i].height) //y increases in down direction
			{
				playerOnLadderBeg();
				playerNotOnLadderEnd();
				playerOnLadder();
				return;
			}
			//is Mario at the end of ladder?
			else if (leftLowerCorner[1] == ladders[i].upperYCorner)
			{
				playerOnLadderEnd();
				playerNotOnLadderBeg();
				playerOnLadder();
				return;
			}
			//is Mario in the "middle" of ladder?
			else if (ladders[i].upperYCorner < leftLowerCorner[1] && leftLowerCorner[1] < ladders[i].upperYCorner + ladders[i].height) 
			{
				playerOnLadder();
				playerNotOnLadderEnd();
				playerNotOnLadderBeg();
				return;
			}
		}
	}
	playerNotOnLadderEnd();
	playerNotOnLadderBeg();
	playerNotOnLadder();
}

void isPlayerOnPlatform(Platform* platforms)
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		// is Mario on platform height?
		if (Mario.lowerYCorner == platforms[i].upperYCorner)
			// how far from edges?
			if (platforms[i].upperXCorner <= Mario.lowerXCorner + Mario.realSize[0] && Mario.lowerXCorner <= platforms[i].upperXCorner + platforms[i].length)
			{
				playerOnPlatform();
				return;
			}
	}
	playerNotOnPlatform();
}

void isPlayerOnGround()
{
	if (!Mario.onPlatform && !Mario.onLadder && Mario.lowerYCorner != GROUND_HEIGHT)
		playerFallingDown();
	if (Mario.lowerYCorner == GROUND_HEIGHT)
	{
		playerOnGround();
		playerNotFallingDown();
	}
}

void whereIsPLayer(Platform* platforms, Ladder* ladders)
{
	isPlayerOutsideTheBorders();
	isPlayerOnLadder(ladders);
	isPlayerOnPlatform(platforms);
	isPlayerOnGround();	
}

void whereAreObjects(Platform* platforms, Ladder* ladders,Barrel* barrels)
{
	whereIsPLayer(platforms, ladders);
	whereAreBarrels(platforms, barrels);
}

void collision(GameInfo* gameInfo, PlayerInfo* playerInfo, Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (barrels[i].lowerYCorner + BARRELS_DIFFERENCE_IN_Y >= Mario.lowerYCorner - Mario.realSize[1] &&
			barrels[i].lowerYCorner - BARRELS_HITBOX_SIZE <= Mario.lowerYCorner &&
			barrels[i].lowerXCorner <= Mario.lowerXCorner + Mario.realSize[0] &&
			barrels[i].lowerXCorner + BARRELS_HITBOX_SIZE >= Mario.lowerXCorner)
		{
			loseLive(gameInfo, playerInfo);
			barrels[i].lowerYCorner = BARRELS_SPAWN_POINT_Y;
			break;
		}
	}
}

void moveObjects(GameInfo* gameInfo, PlayerInfo* playerInfo, Barrel* barrels)
{
	collision(gameInfo, playerInfo, barrels);
	playerMovement(gameInfo);
	barrelMovement(barrels, gameInfo);
}

// TODO przejrzystosc kodu, pamietaj o tym, ze 
void readKeys(GameInfo* gameInfo, PlayerInfo* playerInfo, Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	while (SDL_PollEvent(&SDL.event))
	{
		int keyPressed = SDL.event.key.keysym.sym;
		switch (SDL.event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				quit(gameInfo);
			else if (keyPressed == SDLK_n)
				newGameSettings(gameInfo, playerInfo, platforms, ladders, barrels, trophies);
			else if (keyPressed == SDLK_RIGHT)
				Mario.speedX = WALKING_SPEED;
			else if (keyPressed == SDLK_LEFT)
				Mario.speedX = -WALKING_SPEED;
			else if ( keyPressed == SDLK_DOWN)
				Mario.speedY = CLIMBING_SPEED;
			else if (keyPressed == SDLK_UP)
				Mario.speedY = -CLIMBING_SPEED;
			else if (keyPressed == SDLK_SPACE)
				checkIfPlayerIsJumping(); 
			break;
		case SDL_KEYUP:
			Mario.speedX = 0;
			if(keyPressed==SDLK_DOWN || keyPressed==SDLK_UP)
				Mario.speedY = 0;
			break;		
		case SDL_QUIT: //X button in right up corner
			quit(gameInfo);
			break;
		}
	}
}

void SDLSpace()
{
	SDL_FreeSurface(SDL.charset);
	SDL_FreeSurface(SDL.screen);
	SDL_FreeSurface(SDL.player);
	SDL_FreeSurface(SDL.barrel);
	SDL_FreeSurface(SDL.trophy);
	SDL_DestroyTexture(SDL.scrtex);
	SDL_DestroyRenderer(SDL.renderer);
	SDL_DestroyWindow(SDL.window);
}

void quit(GameInfo* gameInfo)
{
	gameInfo->quit = true;
	SDLSpace();
	SDL_Quit();
}
