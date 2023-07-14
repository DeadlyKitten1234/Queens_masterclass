#include <iostream>
using std::cout;
#include "EndScreen.h"
#include "Presenter.h"

SDL_Texture* EndScreen::M_BACKGROUNDTEXTURE = nullptr;
SDL_Texture* EndScreen::M_OVERLAYBLUETEXTURE = nullptr;
SDL_Texture* EndScreen::M_OVERLAYREDTEXTURE = nullptr;
Drawable EndScreen::M_TEXT = Drawable();

EndScreen::EndScreen() {}

EndScreen::~EndScreen() {}

void EndScreen::setPlayerWon(bool redPlayerWon) {
	m_draw = 1;
	m_redPlayerWon = redPlayerWon;
	m_textAlphaIncrease = 1;
}

void EndScreen::draw() {
	Presenter::drawObject(M_BACKGROUNDTEXTURE);
	if (m_redPlayerWon) {
		Presenter::drawObject(M_OVERLAYBLUETEXTURE);
	} else {
		Presenter::drawObject(M_OVERLAYREDTEXTURE);
	}
	SDL_SetTextureAlphaMod(M_TEXT.m_texture, M_TEXT.m_alpha);
	Presenter::drawObject(M_TEXT);
}

void EndScreen::update(bool keyPressed) {
	if (m_textAlphaIncrease) {
		M_TEXT.m_alpha += 5;
		if (M_TEXT.m_alpha >= 255) {
			M_TEXT.m_alpha = 255;
			m_textAlphaIncrease = 0;
		}
	}
	else {
		M_TEXT.m_alpha -= 5;
		if (M_TEXT.m_alpha <= 0) {
			M_TEXT.m_alpha = 0;
			m_textAlphaIncrease = 1;
		}
	}

	if (keyPressed) {
		m_draw = 0;
	}
}

bool EndScreen::nextStage() {
	return !m_draw;
}
