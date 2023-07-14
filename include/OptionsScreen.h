#pragma once

#include <utility>
#include "Globals.h"
#include "Drawable.h"
#include "Slider.h"
#include "AI.h"
#include "SDL.h"
using std::pair;

class OptionsScreen {
public:
	OptionsScreen();
	~OptionsScreen();

	static void init();
	static void update(int mouseX, int mouseY, bool mouseButtonDown, bool mouseButtonUp, bool keyUp);
	static void draw();
	static void reset();

	static bool getPlay();
	static bool getBack();
	static bool getFadingAway();

	static int2 getBoardSz();
	static Difficulty getDifficulty();

	static SDL_Texture* M_BACKGROUND_TEXTURE;
	static Drawable M_PLAY_BUTTON;
	static Drawable M_BACK_BUTTON;
	static Drawable M_TEXT[3];
	static SDL_Rect M_SLIDER_POS[3];

	static int m_alphaDecreaseDefault;
	static int m_alphaDecrease;

private:
	static int m_pressedButton;
	static Slider m_sliderW;
	static Slider m_sliderH;
	static Slider m_sliderDifficulty;
	static bool m_nextStage;
	static bool m_back;
	static bool m_fadingAway;

	static int m_alpha;
};