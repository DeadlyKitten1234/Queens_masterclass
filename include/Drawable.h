#pragma once
#include "SDL.h"

class Drawable {
public:
	Drawable();
	~Drawable();

	void setRect(SDL_Rect rect);
	void setTexture(SDL_Texture* texture);
	void setAlpha(int alpha);

	SDL_Rect m_rect;
	SDL_Texture* m_texture;
	int m_alpha;
};