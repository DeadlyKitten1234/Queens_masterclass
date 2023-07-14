#include "Tile.h"
#include "Presenter.h"

SDL_Texture* Tile::M_TILE_TEXTURE = nullptr;
SDL_Texture* Tile::M_TILE_ATTACKED_TEXTURE = nullptr;
int Tile::M_ALPHA_CHANGE = 3;

Tile::Tile() : Drawable() {
	m_queenOnTile = 0;
	m_attacked = 0;
	m_texture = M_TILE_TEXTURE;
	m_changing = 0;
	m_framesDelay = 0;
	m_changedTexture = 0;
}

Tile::~Tile() {}

void Tile::setRect(int x, int y, int w, int h) {
	m_rect = { x, y, w, h };
}

void Tile::makeAttacked() {
	m_attacked = 1;
	//m_texture = M_TILE_ATTACKED_TEXTURE;
}

void Tile::putQueenOnTile() {
	m_queenOnTile = 1;
	m_attacked = 1;
}

void Tile::draw() {
	if (m_changing) {
		SDL_SetTextureAlphaMod(M_TILE_TEXTURE, m_alpha);
		m_texture = M_TILE_TEXTURE;
		Presenter::drawObject(*this);
		SDL_SetTextureAlphaMod(M_TILE_TEXTURE, 255);

		SDL_SetTextureAlphaMod(M_TILE_ATTACKED_TEXTURE, 255 - m_alpha);
		m_texture = M_TILE_ATTACKED_TEXTURE;
		Presenter::drawObject(*this);
		SDL_SetTextureAlphaMod(M_TILE_ATTACKED_TEXTURE, 255);
		
		updateAlpha();
	} else {
		Presenter::drawObject(*this);
	}
}

void Tile::changeTexture(int frameDelay) {
	if (!m_changedTexture || m_framesDelay > frameDelay) {
		m_framesDelay = frameDelay;
		m_changing = 1;
	}
}

void Tile::updateAlpha() {
	if (m_framesDelay > 0) {
		m_framesDelay--;
	} else {
		m_alpha -= M_ALPHA_CHANGE;
		if (m_alpha <= 0) {
			m_alpha = 0;
			m_changing = 0;
			m_changedTexture = 1;
		}
	}
}

bool Tile::getAttacked() {
	return m_attacked;
}
