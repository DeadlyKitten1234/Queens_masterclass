#include "OptionsScreen.h"
#include "Presenter.h"

SDL_Texture* OptionsScreen::M_BACKGROUND_TEXTURE = nullptr;
Drawable OptionsScreen::M_PLAY_BUTTON = Drawable();
Drawable OptionsScreen::M_BACK_BUTTON = Drawable();

Drawable OptionsScreen::M_TEXT[3] = {Drawable()};
SDL_Rect OptionsScreen::M_SLIDER_POS[3] = {SDL_Rect()};

Slider OptionsScreen::m_sliderW = Slider();
Slider OptionsScreen::m_sliderH = Slider();
Slider OptionsScreen::m_sliderDifficulty = Slider();

int OptionsScreen::m_pressedButton = -1;
bool OptionsScreen::m_nextStage = false;
bool OptionsScreen::m_back = false;
int OptionsScreen::m_alphaDecreaseDefault = 5;
int OptionsScreen::m_alphaDecrease = 5;
int OptionsScreen::m_alpha = 255;
bool OptionsScreen::m_fadingAway = false;


OptionsScreen::OptionsScreen() {}

OptionsScreen::~OptionsScreen() {}

void OptionsScreen::init() {
	m_pressedButton = -1;

	m_sliderW = Slider(M_SLIDER_POS[0].x, M_SLIDER_POS[0].y, M_SLIDER_POS[0].w, M_SLIDER_POS[0].w / M_SLIDER_POS[0].h);
	m_sliderW.setValueRange(4, 100);
	m_sliderH = Slider(M_SLIDER_POS[1].x, M_SLIDER_POS[1].y, M_SLIDER_POS[1].w, M_SLIDER_POS[1].w / M_SLIDER_POS[1].h);
	m_sliderH.setValueRange(4, 100);
	m_sliderDifficulty = Slider(M_SLIDER_POS[2].x, M_SLIDER_POS[2].y, M_SLIDER_POS[2].w, M_SLIDER_POS[2].w / M_SLIDER_POS[2].h);
	m_sliderDifficulty.setValueRange(0, 3);
}

void OptionsScreen::update(int mouseX, int mouseY, bool mouseButtonDown, bool mouseButtonUp, bool keyUp) {
	m_sliderW.update(mouseX, mouseY, mouseButtonUp, mouseButtonDown);
	m_sliderH.update(mouseX, mouseY, mouseButtonUp, mouseButtonDown);
	m_sliderDifficulty.update(mouseX, mouseY, mouseButtonUp, mouseButtonDown);

	if (m_sliderW.getHeld() || m_sliderH.getHeld() || m_sliderDifficulty.getHeld()) {
		m_sliderW.setLastOnePressed(m_sliderW.getHeld());
		m_sliderH.setLastOnePressed(m_sliderH.getHeld());
		m_sliderDifficulty.setLastOnePressed(m_sliderDifficulty.getHeld());
		return;
	}

 	if (m_fadingAway) {
		m_alpha -= m_alphaDecrease;
		if (keyUp || mouseButtonUp) {
			m_alphaDecrease *= 5;
		}
		if (m_alpha <= 0) {
			m_alpha = 0;
			m_fadingAway = false;
		}
		return;
	}

	if (M_PLAY_BUTTON.m_rect.x <= mouseX && mouseX < M_PLAY_BUTTON.m_rect.x + M_PLAY_BUTTON.m_rect.w) {
		if (M_PLAY_BUTTON.m_rect.y <= mouseY && mouseY < M_PLAY_BUTTON.m_rect.y + M_PLAY_BUTTON.m_rect.h) {
			//Mouse on play button
			if (mouseButtonDown) {
				m_pressedButton = 1;
			}
			if (mouseButtonUp) {
				if (m_pressedButton == 1) {
					m_nextStage = true;
					m_fadingAway = true;
				}
			}
			return;
		}
	}
	if (M_BACK_BUTTON.m_rect.x <= mouseX && mouseX < M_BACK_BUTTON.m_rect.x + M_BACK_BUTTON.m_rect.w) {
		if (M_BACK_BUTTON.m_rect.y <= mouseY && mouseY < M_BACK_BUTTON.m_rect.y + M_BACK_BUTTON.m_rect.h) {
			//Mouse on back button
			if (mouseButtonDown) {
				m_pressedButton = 2;
			}
			if (mouseButtonUp) {
				if (m_pressedButton == 2) {
					m_back = true;
				}
			}
			return;
		}
	}
	if (mouseButtonDown || mouseButtonUp) {
		m_pressedButton = -1;
	}
}

void OptionsScreen::draw() {
	if (m_alpha != 255) {
		m_alpha = m_alpha;
	}
	SDL_SetTextureAlphaMod(M_BACKGROUND_TEXTURE, m_alpha);
	SDL_SetTextureAlphaMod(M_PLAY_BUTTON.m_texture, m_alpha);
	SDL_SetTextureAlphaMod(M_BACK_BUTTON.m_texture, m_alpha);

	Presenter::drawObject(M_BACKGROUND_TEXTURE);

	m_sliderW.draw(m_alpha);
	m_sliderH.draw(m_alpha);
	m_sliderDifficulty.draw(m_alpha);

	for (int i = 0; i < 3; i++) {
		SDL_SetTextureAlphaMod(M_TEXT[i].m_texture, m_alpha);
		Presenter::drawObject(M_TEXT[i]);
	}
	SDL_Rect temp = { M_TEXT[0].m_rect.x + M_TEXT[0].m_rect.w + 10, M_TEXT[0].m_rect.y , M_TEXT[0].m_rect.h * 32 / 42, M_TEXT[0].m_rect.h };
	Presenter::drawNumber(m_sliderW.getCurrVal(), int2(temp.x, temp.y), int2(temp.w, temp.h));
	temp = { M_TEXT[1].m_rect.x + M_TEXT[1].m_rect.w + 10, M_TEXT[1].m_rect.y , M_TEXT[1].m_rect.h * 32 / 42, M_TEXT[1].m_rect.h };
	Presenter::drawNumber(m_sliderH.getCurrVal(), int2(temp.x, temp.y), int2(temp.w, temp.h));
	temp = { M_TEXT[2].m_rect.x + M_TEXT[2].m_rect.w + 10, M_TEXT[2].m_rect.y , M_TEXT[2].m_rect.h * 32 / 42, M_TEXT[2].m_rect.h };
	Presenter::drawNumber(m_sliderDifficulty.getCurrVal(), int2(temp.x, temp.y), int2(temp.w, temp.h));

	Presenter::drawObject(M_PLAY_BUTTON);
	Presenter::drawObject(M_BACK_BUTTON);
}

void OptionsScreen::reset() {
	m_pressedButton = -1;
	m_nextStage = false;
	m_back = false;
	m_alpha = 255;
	m_alphaDecrease = m_alphaDecreaseDefault;
	m_fadingAway = false;
}

bool OptionsScreen::getPlay() {
	return m_nextStage;
}

bool OptionsScreen::getBack() {
	return m_back;
}

bool OptionsScreen::getFadingAway() {
	return m_fadingAway;
}

int2 OptionsScreen::getBoardSz() {
	return int2(m_sliderW.getCurrVal(), m_sliderH.getCurrVal());
}

Difficulty OptionsScreen::getDifficulty() {
	return Difficulty(m_sliderDifficulty.getCurrVal());
}
