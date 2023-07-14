#pragma once

#include <vector>
#include "SDL.h"
#include "Drawable.h"
using std::vector;

class Slider {
public:
	Slider();
	Slider(int stX, int stY, int totalWPixels, int sz);
	~Slider();

	void setSize(int stX, int stY, int totalWPixels, int sz);
	void setValueRange(int minVal, int maxVal);
	
	void update(int mouseX, int mouseY, bool mouseButtonUp, bool mouseButtonDown);
	void draw();
	void draw(int alpha);
	int getCurrVal();

	void setLastOnePressed(bool lastOnePressed);
	bool getHeld();

	static SDL_Texture* M_FRONT_TEXTURE;
	static SDL_Texture* M_MIDDLE_TEXTURE;
	static SDL_Texture* M_BACK_TEXTURE;
	static SDL_Texture* M_BALL_TEXTURE;
	static SDL_Texture* M_VALUE_INDICATOR_TEXTURE;
	static SDL_Texture* M_VALUE_INDICATOR_SMALL_TEXTURE;

private:
	bool m_lastOnePressed;
	bool m_mouseBeingHeld;

	int m_sz;
	
	int m_currVal;
	int m_minVal;
	int m_maxVal;
	int m_possValNum;

	int m_tileSz;
	int m_offsetX;
	int m_offsetY;

	int m_ballDestX;
	float m_ballVelX;
	float m_ballXFloat;
	vector<Drawable> m_part;
	vector<Drawable> m_valueIndicator;
	Drawable m_ball;
};