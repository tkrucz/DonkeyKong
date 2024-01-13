#pragma once
//REMEMBER: GET RID OF MAGIC NUMBERS !!!
//+ 1
#include "ObjectsDefine.h"

#define SCREEN_WIDTH	720
#define SCREEN_HEIGHT	520
#define SECONDS_BETWEEN_REFRESH 0.5
#define REFRESH_RATE 1/SECONDS_BETWEEN_REFRESH

#define ZERO_COLUMN 0 
#define TEN_COLUMN 10
#define ONE_HUNDRED_TWENTY 120
#define ONE_HUNDRED_FIFTHY_COLUMN 150
#define ONE_HUNDRED_SEVENTY_COLUMN 170
#define FIVE_HUNDRED_COLUMN 500
#define FIVE_HUNDRED_EIGHTY_COLUMN 580
#define NAME_COLUMN 300
#define WRITING_NAME_COLUMN 220

#define FIRST_ROW 1
#define TITLE_ROW 5
#define REQUIREMENTS_ROW 20
#define TIME_ROW 35
#define THIRTY_FIVE 35
#define OPTIONS_ROW 50
#define KEYS_ROW 65
#define EIGHTY_ROW 80
#define EIGHTY_FIVE_ROW 85
#define HUNDRED_ROW 100
#define SCOREBOARD_ROW 280 
#define AUTHOR_INFO_ROW SCREEN_HEIGHT - 12
#define GROUND_HEIGHT SCREEN_HEIGHT - 20

#define TABLE_HEIGHT 80

#define MILI 0.001
#define ZERO 0
#define HALF 0.5
#define ONE 1
#define TWO 2
#define THREE 3
#define EIGHT 8
#define FIFTEEN 15

#define GRAVITY_SPEED 1
#define JUMPING_SPEED 0.45
#define MAX_DIFFERNECE_DISTANCE 85
#define ELASTIC_COLISION_CONST -106 

#define NULL_SPEED 0
#define WALKING_SPEED 50
#define CLIMBING_SPEED 30

#define PLAYER_SPAWN_POINT_X 360 
#define PLAYER_SPAWN_POINT_Y 500
#define PLAYER_DIFFERENCE_IN_X 144
#define PLAYER_DIFFERENCE_IN_Y 50

#define PLAYER_WIDTH 37 
#define PLAYER_HEIGHT 34
#define PLAYER_REAL_SIZE 16

#define PLAYER_DEFAULT_LIVES 3
#define PLAYER_DEFAULT_POINTS 0

#define MARIO_BMP_COLUMN_DISTANCE 3 //const which allows to show the whole Mario graphic
#define MARIO_BMP_ROW_DISTANCE 6 //const which allows to show the whole Mario graphic

#define JUMP_OVER_BARREL_POINTS 1000
#define GET_TROPHY_POINTS 500
#define END_THE_STAGE_POINTS 10000

#define SHOWING_TEXT_TIME 1
#define SHOWING_ANIMATION_TIME 1

#define NUMBER_OF_PLAYERS 5

///Animation defines
#define PLAYER_JUMP_LEFT 1
#define PLAYER_WALK_LEFT 2
#define PLAYER_STAND_LEFT 3
#define PLAYER_STAND_RIGHT 4
#define PLAYER_WALK_RIGHT 5 
#define PLAYER_JUMP_RIGHT 6
#define PLAYER_CLIMB_ONE 3
#define PLAYER_CLIMB_TWO 4