#pragma once

#include<iostream>
#include "SDL.h"
using namespace std;

extern SDL_DisplayMode SCREEN_RESOLUTION;

extern int SCREEN_W;
extern int SCREEN_H;
extern int SPLASH_SIZE;
extern int HEART_W;
extern int HEART_H;
extern int LIVES;
extern float GRAVITY_PULL;
extern float MULTIPLY_X;
extern float MULTIPLY_Y;


const int TICKS_BETWEEN_FRUIT_SPAWNS = 100;
const int TRAIL_LIFE_TICKS = 50;
const int COMBO_LENGTH = 2000; //Miliseconds

const int TICKS_PER_SECOND = 60;
const int FRAMES_PER_SECOND = 100;


const int LOGICAL_SIZE_W = 1920;
const int LOGICAL_SIZE_H = 1080;

SDL_Texture* loadTexture(string in, SDL_Renderer* renderer);

struct float2 {
	float2();
	float2(float st_x, float st_y);
	float x;
	float y;
};

struct int2 {
	int2();
	int2(int st_x, int st_y);
	int x;
	int y;
};

bool coordsInRect(int x, int y, SDL_Rect rect);

bool collisionSegmentWithRect(int2 segmentStart, int2 segmentEnd, SDL_Rect rect);

bool collisionTwoSegments(int2 segment1Start, int2 segment1End, int2 HorizontalOrVertical_segment2Start, int2 HorizontalOrVertical_segment2End);