#pragma once

#include "SDL.h"
#include "Drawable.h"

class Menu {
public:
	Menu();
	~Menu();

	static SDL_Texture* M_MENUTEXTURE;
	static Drawable M_PLAYBUTTON;
	static Drawable M_EXITBUTTON;
	static int M_ALPHA_CHANGE;

	void draw();
	void update(bool mousePressed, bool mouseReleased, int mouse_x, int mouse_y, bool keyReleased);
	
	void reset();

	bool nextStage();
	bool exit();
	bool getFadingAway();

private:
	int m_pressedButton;
	bool m_draw;
	bool m_exit;

	int m_alpha;
	bool m_fadeIn;
	bool m_fadeAway;

	int m_alphaChange;
};