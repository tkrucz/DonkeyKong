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

void printGameInfo();

void printPlayerInfo();

void printGround();

void basicSetting();

void createColor();

void playerWalking();

void playerClimbing();

void playerJumping();

void playerMove();

void addPoints();

void jumpOverBarrel();

void endTheStage();

void getTrophy();

void addScore();

void loseLive();

void timeCounting();

void createPlatforms();

void createLadders();

void graivityApply();

bool playerOnLadder(); //na razie nie korzystam

bool playerOnPlatform(); //na razie nie korzystam

void whereIsPLayer(); //na razie nie korzystam

void freeSpace();