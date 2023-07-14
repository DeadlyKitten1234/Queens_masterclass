#include "Queen.h"
#include "Presenter.h"

SDL_Texture* Queen::M_QUEEN_TEXTURE = nullptr;

Queen::Queen() : Drawable() {
	m_texture = M_QUEEN_TEXTURE;
}

Queen::~Queen() {}

void Queen::draw() {
	Presenter::drawObject(*this);
}

void Queen::setTile(int col, int row, int tileSize, int2 gridStPos) {
	m_tile.x = col;
	m_tile.y = row;

	m_rect = {col * tileSize + gridStPos.x, row * tileSize + gridStPos.y, tileSize, tileSize};
}

void Queen::setTile(int col, int row, int tileSize, int gridStX, int gridStY) {
	m_tile.x = col;
	m_tile.y = row;

	m_rect = {col * tileSize + gridStX, row * tileSize + gridStY, tileSize, tileSize};
}
