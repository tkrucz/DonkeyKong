#pragma once
#include "structures.h"
#include "define.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y, SDL_Rect* src = nullptr);

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

void createWindow();

void printWindow();

void refreshWindow();

void printGameInfo();

void printPlayerInfo();

void printGround();

void basicSetting();

void playerSettings();

void createColor();

void playerWalking();

void playerClimbing();

void graivityApply(); //checks if Mario is jumping, change his position while jumping

void playerJumping();

void playerMove();

void addPoints(); //function needed only right for test

void jumpOverBarrel();

void endTheStage();

void getTrophy();

void addScore();

void loseLive();

void timeCounting(); //counting the game time

void createPlatforms();

void createLadders();

void playerOnLadder(); 

void playerOnPlatform(); 

void playerNoWhere();

void whereIsPLayer(); 

void freeSpace();