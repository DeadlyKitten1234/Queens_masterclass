#include <algorithm>
#include "Slider.h"
#include "Presenter.h"
using std::min;
using std::max;

SDL_Texture* Slider::M_FRONT_TEXTURE = nullptr;
SDL_Texture* Slider::M_MIDDLE_TEXTURE = nullptr;
SDL_Texture* Slider::M_BACK_TEXTURE = nullptr;
SDL_Texture* Slider::M_BALL_TEXTURE = nullptr;
SDL_Texture* Slider::M_VALUE_INDICATOR_TEXTURE = nullptr;
SDL_Texture* Slider::M_VALUE_INDICATOR_SMALL_TEXTURE = nullptr;

Slider::Slider() {
	m_mouseBeingHeld = 0;
	m_lastOnePressed = 0;

	m_sz = -1;

	m_currVal = -1;
	m_minVal = -1;
	m_maxVal = -1;
	m_possValNum = -1;

	m_tileSz = 0;
	m_offsetX = 0;
	m_offsetY = 0;

	m_ballDestX = -1;
	m_ballVelX = -1;
	m_ballXFloat = -1;
}

Slider::Slider(int stX, int stY, int totalWPixels, int sz) : Slider() {
	setSize(stX, stY, totalWPixels, sz);
}

Slider::~Slider() {}

void Slider::setSize(int stX, int stY, int totalWPixels, int sz) {
	if (sz == 0) {
		return;
	}
	m_offsetX = stX;
	m_offsetY = stY;
	m_sz = sz;
	m_tileSz = totalWPixels / sz; 
	
	Drawable temp;
	temp.m_rect = {stX, stY, m_tileSz, m_tileSz};
	temp.m_texture = M_BALL_TEXTURE;
	m_ball = temp;

	for (int i = 0; i < sz; i++) {
		Drawable temp;
		temp.m_rect = {stX + i * m_tileSz, stY, m_tileSz, m_tileSz};
		if (i == 0) {
			temp.m_texture = M_FRONT_TEXTURE;
		} else {
			if (i == sz - 1) {
				temp.m_texture = M_BACK_TEXTURE;
			} else {
				temp.m_texture = M_MIDDLE_TEXTURE;
			}
		}
		m_part.push_back(temp);
	}
}

void Slider::setValueRange(int minVal, int maxVal) {
	m_minVal = minVal;
	m_maxVal = maxVal;
	m_possValNum = maxVal - minVal + 1;
	m_currVal = minVal;

	for (int i = 1; i < m_possValNum - 1; i++) {
		Drawable temp;
		if (m_possValNum > m_sz) {//Value indicators overlap
			temp.m_texture = M_VALUE_INDICATOR_SMALL_TEXTURE;
		} else {
			temp.m_texture = M_VALUE_INDICATOR_TEXTURE;
		}
		int tempX = m_offsetX + i * (m_sz * m_tileSz - m_tileSz) / (m_possValNum - 1);
		temp.m_rect = {tempX, m_offsetY, m_tileSz, m_tileSz};
		m_valueIndicator.push_back(temp);
	}
}

void Slider::update(int mouseX, int mouseY, bool mouseButtonUp, bool mouseButtonDown) {
	//So you can use arrows to change value
	if (m_lastOnePressed) {
		const Uint8* key = SDL_GetKeyboardState(NULL);
		if (key[SDL_SCANCODE_LEFT] || key[SDL_SCANCODE_DOWN]) {
			m_currVal = max(m_minVal, m_currVal - 1);
			m_ballDestX = m_offsetX + (m_currVal - m_minVal) * (m_sz * m_tileSz - m_tileSz) / (m_possValNum - 1);
			m_ballVelX = float(m_ballDestX - m_ball.m_rect.x) / 10;
			m_ballXFloat = m_ball.m_rect.x;
		}
		if (key[SDL_SCANCODE_RIGHT] || key[SDL_SCANCODE_UP]) {
			m_currVal = min(m_maxVal, m_currVal + 1);
			m_ballDestX = m_offsetX + (m_currVal - m_minVal) * (m_sz * m_tileSz - m_tileSz) / (m_possValNum - 1);
			m_ballVelX = float(m_ballDestX - m_ball.m_rect.x) / 10;
			m_ballXFloat = m_ball.m_rect.x;
		}
	}
	
	if (m_ballDestX != -1) {//Move to closest knob after released
		m_ballXFloat += m_ballVelX;
		m_ball.m_rect.x = m_ballXFloat;
		if (abs(m_ballXFloat - m_ballDestX) < 0.5) {
			m_ball.m_rect.x = m_ballDestX;
			m_ballDestX = -1;
		}
	}

	if (mouseButtonUp) {//Set closest knob after released
		m_mouseBeingHeld = 0;
		m_ballDestX = m_offsetX + (m_currVal - m_minVal) * (m_sz * m_tileSz - m_tileSz) / (m_possValNum - 1);
		m_ballVelX = float(m_ballDestX - m_ball.m_rect.x) / 10;
		m_ballXFloat = m_ball.m_rect.x;
		return;
	}
	//Mouse out of slider
	if (!m_mouseBeingHeld && (mouseX < m_offsetX || m_offsetX + m_sz * m_tileSz < mouseX || mouseY < m_offsetY || m_offsetY + m_tileSz < mouseY)) {
		return;
	}

	if (mouseButtonDown) {
		m_mouseBeingHeld = 1;
	} else {
		if (!m_mouseBeingHeld) {
			return;
		}
	}
	m_lastOnePressed = 1;
	mouseX -= m_tileSz / 2 + m_offsetX;
	m_ballDestX = -1;
	
	mouseX += (m_sz * m_tileSz - m_tileSz) / (m_possValNum - 1) / 2;//So it homes forward too
	int newVal = m_minVal + (mouseX * (m_possValNum - 1)) / (m_sz * m_tileSz - m_tileSz);
	mouseX += m_tileSz / 2 + m_offsetX - (m_sz * m_tileSz - m_tileSz) / (m_possValNum - 1) / 2;//Reset mouseX to its initial position
	
	m_currVal = max(m_minVal, min(newVal, m_maxVal));
	m_ball.m_rect.x = max(m_offsetX, min(m_offsetX + (m_sz - 1) * m_tileSz, mouseX - m_tileSz / 2));
}

void Slider::draw() {
	for (int i = 0; i < m_sz; i++) {
		Presenter::drawObject(m_part[i]);
	}
	for (int i = 0; i < m_possValNum - 2; i++) {
		Presenter::drawObject(m_valueIndicator[i]);
	}
	Presenter::drawObject(m_ball);
}

void Slider::draw(int alpha) {
	for (int i = 0; i < m_sz; i++) {
		SDL_SetTextureAlphaMod(m_part[i].m_texture, alpha);
		Presenter::drawObject(m_part[i]);
	}
	for (int i = 0; i < m_possValNum - 2; i++) {
		SDL_SetTextureAlphaMod(m_valueIndicator[i].m_texture, alpha);
		Presenter::drawObject(m_valueIndicator[i]);
	}
	SDL_SetTextureAlphaMod(m_ball.m_texture, alpha);
	Presenter::drawObject(m_ball);
}

int Slider::getCurrVal() {
	return m_currVal;
}

void Slider::setLastOnePressed(bool lastOnePressed) {
	m_lastOnePressed = lastOnePressed;
}

bool Slider::getHeld() {
	return m_mouseBeingHeld;
}
