#include "Menu.h"
#include "Presenter.h"

SDL_Texture* Menu::M_MENUTEXTURE = nullptr;
Drawable Menu::M_PLAYBUTTON = Drawable();
Drawable Menu::M_EXITBUTTON = Drawable();
int Menu::M_ALPHA_CHANGE = 5;

Menu::Menu() {
	m_pressedButton = -1;
	m_draw = 1;
	m_exit = 0;

	m_alpha = 0;
	m_fadeIn = 1;
	m_fadeAway = 0;
	m_alphaChange = M_ALPHA_CHANGE;
}

Menu::~Menu() {}

void Menu::draw() {
	SDL_SetTextureAlphaMod(M_MENUTEXTURE, m_alpha);
	SDL_SetTextureAlphaMod(M_PLAYBUTTON.m_texture, m_alpha);
	SDL_SetTextureAlphaMod(M_EXITBUTTON.m_texture, m_alpha);
	Presenter::drawObject(M_MENUTEXTURE);
	Presenter::drawObject(M_PLAYBUTTON);
	Presenter::drawObject(M_EXITBUTTON);
}

void Menu::update(bool mousePressed, bool mouseReleased, int mouse_x, int mouse_y, bool keyReleased) {
	if (m_fadeIn) {
		if (mouseReleased || keyReleased) {
			m_alphaChange *= 5;
		}
		m_alpha += m_alphaChange;
		if (m_alpha >= 255) {
			m_alpha = 255;
			m_fadeIn = 0;
			m_alphaChange = M_ALPHA_CHANGE;
		}
		return;
	}
	if (m_fadeAway) {
		if (mouseReleased || keyReleased) {
			m_alphaChange *= 5;
		}
		m_alpha -= m_alphaChange;
		if (m_alpha <= 0) {
			m_alpha = 0;
			m_fadeAway = 0;
		}
		return;
	}

	if (!mousePressed && !mouseReleased) {
		return;
	}

	if (M_PLAYBUTTON.m_rect.x < mouse_x && mouse_x < M_PLAYBUTTON.m_rect.x + M_PLAYBUTTON.m_rect.w) {
		if (M_PLAYBUTTON.m_rect.y < mouse_y && mouse_y < M_PLAYBUTTON.m_rect.y + M_PLAYBUTTON.m_rect.h) {
			if (mousePressed) {
				m_pressedButton = 1;
			}
			else {
				if (m_pressedButton == 1) {
					m_draw = 0;
					m_pressedButton = -1;
					m_fadeAway = 1;
				}
			}
			return;
		}
	}

	if (M_EXITBUTTON.m_rect.x < mouse_x && mouse_x < M_EXITBUTTON.m_rect.x + M_EXITBUTTON.m_rect.w) {
		if (M_EXITBUTTON.m_rect.y < mouse_y && mouse_y < M_EXITBUTTON.m_rect.y + M_EXITBUTTON.m_rect.h) {
			if (mousePressed) {
				m_pressedButton = 2;
			}
			else {
				if (m_pressedButton == 2) {
					m_draw = 0;
					m_exit = 1;
					m_pressedButton = -1;
				}
			}
			return;
		}
	}
	m_pressedButton = -1;
}

void Menu::reset() {
	m_pressedButton = -1;
	m_draw = 1;
	m_exit = 0;

	m_alpha = 0;
	m_fadeIn = 1;
	m_fadeAway = 0;
	m_alphaChange = M_ALPHA_CHANGE;
}

bool Menu::nextStage() {
	return !m_draw;
}

bool Menu::exit() { 
	return m_exit;
}

bool Menu::getFadingAway() {
	return m_fadeAway;
}
