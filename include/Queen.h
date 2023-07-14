#pragma once

#include "SDL.h"
#include "Drawable.h"
#include "Globals.h"

class Queen : public Drawable {
public:
	Queen();
	~Queen();

	void draw();
	void setTile(int col, int row, int tileSize, int2 gridStPos);
	void setTile(int col, int row, int tileSize, int gridStX, int gridStY);

	static SDL_Texture* M_QUEEN_TEXTURE;

private:
	int2 m_tile;
};