#pragma once

#include "SDL.h"
#include "Drawable.h"

class EndScreen {
public:
	EndScreen();
	~EndScreen();

	void setPlayerWon(bool redPlayerWon);
	void draw();
	void update(bool keyPressed);

	static SDL_Texture* M_BACKGROUNDTEXTURE;
	static SDL_Texture* M_OVERLAYBLUETEXTURE;
	static SDL_Texture* M_OVERLAYREDTEXTURE;
	static Drawable M_TEXT;

	bool nextStage();

private:
	bool m_textAlphaIncrease;
	bool m_redPlayerWon;
	bool m_draw;
};