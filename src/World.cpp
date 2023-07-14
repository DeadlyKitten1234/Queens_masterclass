#include "World.h"
#include <iostream>
using std::cout;

World::World() {
	m_exit = 0;
}

World::~World() {}

void World::init() {

	m_config.readPositions();
	m_config.readOpacityChanges();
	m_presenter.init();
	m_config.readTextures(m_presenter.getRenderer());
	m_grid = Grid();
	m_grid.setSize(5, 5, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT);

	m_titleScreen = TitleScreen();
	m_menu = Menu();
	m_optionsScreen.init();
	m_endScreen = EndScreen();

	m_state = State::TITLE_SCREEN;
}

void World::update() {
	m_input.getInput();

	if (m_input.m_quit) {
		m_exit = 1;
	}

	switch (m_state) {
	case State::TITLE_SCREEN:
		updateTitleScreen();
		break;
	case State::MENU:
		updateMenu();
		break;
	case State::GAME_OPTIONS_SCREEN:
		updateGameOptionsScreen();
		break;
	case State::PLAYING:
		updateGame();
		break;
	case State::END_SCREEN:
		updateEndScreen();
		break;
	}
}

void World::updateTitleScreen() {
	m_titleScreen.update(m_input.m_keyReleased);

	if (m_titleScreen.nextStage()) {
		m_state = State::MENU;
	}
}

void World::updateMenu() {
	m_menu.update(m_input.m_mouseIsPressed, m_input.m_mouseButtonReleased, m_input.m_mouseCoord.x, m_input.m_mouseCoord.y, m_input.m_keyReleased);
	if (m_menu.nextStage()) {
		m_state = State::GAME_OPTIONS_SCREEN;
		m_optionsScreen.reset();
	}
}

void World::updateGameOptionsScreen() {
	if (m_menu.getFadingAway()) {
		m_menu.update(m_input.m_mouseIsPressed, m_input.m_mouseButtonReleased, m_input.m_mouseCoord.x, m_input.m_mouseCoord.y, m_input.m_keyReleased);
		return;
	}

	m_optionsScreen.update(m_input.m_mouseCoord.x, m_input.m_mouseCoord.y, m_input.m_mouseIsPressed, m_input.m_mouseButtonReleased, m_input.m_keyReleased);
	if (m_optionsScreen.getBack()) {
		m_menu.reset();
		m_state = State::MENU;
	}
	if (m_optionsScreen.getPlay()) {
		m_state = State::PLAYING;
		int2 gridSz = m_optionsScreen.getBoardSz();
		m_grid.setSize(gridSz.x, gridSz.y, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT);
	}
}

void World::updateGame() {
	if (m_optionsScreen.getFadingAway()) {
		m_optionsScreen.update(m_input.m_mouseCoord.x, m_input.m_mouseCoord.y, m_input.m_mouseIsPressed, m_input.m_mouseButtonReleased, m_input.m_keyReleased);
	}
	m_grid.update(m_input.m_mouseIsPressed, m_input.m_mouseButtonReleased, m_input.m_mouseCoord.x, m_input.m_mouseCoord.y);
	if (m_grid.gameOver()) {
		m_state = State::END_SCREEN;
		m_endScreen.setPlayerWon(m_grid.getPlayerOnTurn());
	}
}

void World::updateEndScreen() {
	m_endScreen.update(m_input.m_keyReleased);
	if (m_endScreen.nextStage()) {
		//reset
		m_state = State::MENU;
		m_menu.reset();
		m_grid.setSize(5, 5, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT);
	}
}

void World::draw() {
	switch (m_state) {
	case State::TITLE_SCREEN:
		m_titleScreen.draw();
		break;
	case State::MENU:
		m_menu.draw();
		break;
	case State::GAME_OPTIONS_SCREEN:
		m_optionsScreen.draw(); 
		if (m_menu.getFadingAway()) {
			m_menu.draw();
		}
		break;
	case State::PLAYING:
		Presenter::drawObject(Presenter::M_BACKGROUND_TEXTURE);
		m_grid.draw();
		if (m_optionsScreen.getFadingAway()) {
			m_optionsScreen.draw();
		}
		break;
	case State::END_SCREEN:
		m_endScreen.draw();
		break;
	}
	m_presenter.draw();
}

bool World::exit() {
	if (m_menu.exit()) {
		m_exit = 1;
	}
	return m_exit;
}
