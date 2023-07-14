#pragma once

#include "Drawable.h"

class Tile : public Drawable {
public:
	Tile();
	~Tile();

	void setRect(int x, int y, int w, int h);
	void putQueenOnTile();
	void makeAttacked();
	void draw();
	void changeTexture(int frameDelay);

	static SDL_Texture* M_TILE_TEXTURE;
	static SDL_Texture* M_TILE_ATTACKED_TEXTURE;
	static int M_ALPHA_CHANGE;

	bool getAttacked();

private:
	void updateAlpha();

	int m_framesDelay;
	bool m_changing;
	bool m_changedTexture;
	bool m_queenOnTile;
	bool m_attacked;
};