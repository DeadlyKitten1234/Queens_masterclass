#pragma once

#include "SDL.h"
#include "Drawable.h"

class TitleScreen {
public:
	TitleScreen();
	~TitleScreen();

	void update(bool keyReleased);
	void hide();
	void draw();

	bool nextStage();
	
	static SDL_Texture* M_TITLESCREENTEXTURE;
	static Drawable M_TEXT;
	static int M_ALPHA_CHANGE;

private:
	bool m_textAlphaIncrease;
	int m_screenAlpha;
	bool m_fade;

	bool m_draw;

	int m_alphaChange;
};