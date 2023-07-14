#include "Drawable.h"

Drawable::Drawable() {
	m_texture = nullptr;
	m_rect = {-1, -1, 0, 0};
	m_alpha = 255;
}

Drawable::~Drawable() {}

void Drawable::setRect(SDL_Rect rect) {
	m_rect = rect;
}

void Drawable::setTexture(SDL_Texture* texture) {
	m_texture = texture;
}

void Drawable::setAlpha(int alpha) {
	m_alpha = alpha;
}
