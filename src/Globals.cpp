#include "Globals.h"
#include "SDL_ttf.h"

int SCREEN_W = 1920;
int SCREEN_H = 1080;
int SPLASH_SIZE = 300;
int HEART_W = 100;
int HEART_H = 114;
int LIVES = 3;
float GRAVITY_PULL = 0.5;
float MULTIPLY_X = 1;
float MULTIPLY_Y = 1;
SDL_DisplayMode SCREEN_RESOLUTION;

SDL_Texture* loadTexture(string in, SDL_Renderer* renderer) {
	in = "assets\\img\\" + in + ".bmp";
	SDL_Surface* loadingSurface = SDL_LoadBMP(in.c_str());
	SDL_Texture* out = nullptr;
	out = SDL_CreateTextureFromSurface(renderer, loadingSurface);
	SDL_FreeSurface(loadingSurface);
	return out;
}

bool coordsInRect(int x, int y, SDL_Rect rect) {
	if ((rect.x <= x && x <= rect.x + rect.w) && (rect.y <= y && y <= rect.y + rect.h)) {
		return true;
	}
	return false;
}

bool collisionTwoSegments(int2 a, int2 b, int2 c, int2 d)
{
	/*
	 a and b are from the (probably) NOT horizontal or vertical segment
	 c and d are from the horizontal or vertical segment
		a   c
	   /    |
	  /     |
	 b      d
	*/
	bool vertical = (c.x == d.x);
	int min_x = min(a.x, b.x);
	int min_y = min(a.y, b.y);
	int max_x = max(a.x, b.x);
	int max_y = max(a.y, b.y);

	int min_xHV = min(c.x, d.x);
	int min_yHV = min(c.y, d.y);
	int max_xHV = max(c.x, d.x);
	int max_yHV = max(c.y, d.y);

	if (a.y == b.y) {
		if (((min_x <= c.x && c.x <= max_x) || (min_x <= d.x && d.x <= min_x)) && (c.y <= a.y && a.y <= d.y)) {
			return true;
		}
		return false;
	}
	if (a.x == b.x) {
		if (((min_y <= c.y && c.y <= max_y) || (min_y <= d.y && d.y <= min_y)) && (c.x <= a.x && a.x <= d.x)) {
			return true;
		}
		return false;
	}
	float xToY = (max_x - min_x) / (max_y - min_y);

	if (vertical) {
		if (c.x < min_x || max_x < c.x) {
			return false;
		}
		int x = c.x;
		int y = (x - min_x) / xToY + min_y;

		if (min_yHV <= y && y <= max_yHV) {
			return true;
		}
	}
	if (!vertical) {
		if (c.y < min_y || max_y < c.y) {
			return false;
		}
		int y = c.y;
		int x = (y - min_y) * xToY + min_x;

		if (min_xHV <= x && x <= max_xHV) {
			return true;
		}
	}

	return false;
}

bool collisionSegmentWithRect(int2 a, int2 b, SDL_Rect rect) {
	if (collisionTwoSegments(a, b, int2(rect.x, rect.y), int2(rect.x + rect.w, rect.y))) {
		return true;
	}
	if (collisionTwoSegments(a, b, int2(rect.x, rect.y), int2(rect.x, rect.y + rect.h))) {
		return true;
	}
	if (collisionTwoSegments(a, b, int2(rect.x + rect.w, rect.y), int2(rect.x + rect.w, rect.y + rect.h))) {
		return true;
	}
	if (collisionTwoSegments(a, b, int2(rect.x, rect.y + rect.h), int2(rect.x + rect.w, rect.y + rect.h))) {
		return true;
	}
	return false;
}

int2::int2()
{
}

int2::int2(int st_x, int st_y)
{
	x = st_x;
	y = st_y;
}

float2::float2()
{
}

float2::float2(float st_x, float st_y)
{
	x = st_x;
	y = st_y;
}
