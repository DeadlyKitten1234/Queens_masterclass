#include <iostream>
using std::cout;
#include "TitleScreen.h"
#include "Presenter.h"

SDL_Texture* TitleScreen::M_TITLESCREENTEXTURE = nullptr;
Drawable TitleScreen::M_TEXT = Drawable();
int TitleScreen::M_ALPHA_CHANGE = 3;

TitleScreen::TitleScreen() {
	m_draw = true;
	m_textAlphaIncrease = 0;
	m_screenAlpha = 0;
	m_fade = 0;
	m_screenAlpha = 0;
	m_alphaChange = M_ALPHA_CHANGE;
}

TitleScreen::~TitleScreen() {}

void TitleScreen::update(bool keyReleased) {
	if (m_fade) {
		if (keyReleased) {
			m_alphaChange *= 5;
		}
		m_screenAlpha -= m_alphaChange;
		if (m_screenAlpha <= 0) {
			m_screenAlpha = 0;
			m_draw = 0;
			m_fade = 0;
		}
		return;
	}

	if (m_screenAlpha < 255) {
		if (keyReleased) {
			m_alphaChange *= 5;
		}
		m_screenAlpha += m_alphaChange;
		if (m_screenAlpha >= 255) {
			m_screenAlpha = 255;
			m_alphaChange = M_ALPHA_CHANGE;
		}
		return;
	}
	else {
		m_screenAlpha = 255;
	}

	if (keyReleased) {
		hide();
		return;
	}
	
	M_TEXT.m_alpha += (m_textAlphaIncrease * 2 - 1) * 5;
	if (M_TEXT.m_alpha <= 0) {
		m_textAlphaIncrease = 1;
	}
	if (M_TEXT.m_alpha >= 255) {
		m_textAlphaIncrease = 0;
	}
}

void TitleScreen::hide() {
	m_fade = 1;
	return;
}

void TitleScreen::draw() {
	if (m_draw) {
		if (m_screenAlpha != 255) {
			SDL_SetTextureAlphaMod(M_TITLESCREENTEXTURE, m_screenAlpha);
		}
		Presenter::drawObject(M_TITLESCREENTEXTURE);
		SDL_SetTextureAlphaMod(M_TEXT.m_texture, (M_TEXT.m_alpha * m_screenAlpha) / 255.0);
		Presenter::drawObject(M_TEXT);
	}
}

bool TitleScreen::nextStage() {
	return !m_draw;
}
