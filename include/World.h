#pragma once
#include "SDL.h"
#include "Grid.h"
#include "Presenter.h"
#include "TitleScreen.h"
#include "Menu.h"
#include "OptionsScreen.h"
#include "EndScreen.h"
#include "ConfigManager.h"
#include "InputManager.h"



enum class State {
	TITLE_SCREEN = 0,
	MENU = 1,
	GAME_OPTIONS_SCREEN = 2,
	PLAYING = 3,
	END_SCREEN = 4
};

class World {
public:
	World();
	~World();

	void init();
	void update();
	void draw();

	bool exit();

private:
	void updateTitleScreen();
	void updateMenu();
	void updateGameOptionsScreen();
	void updateGame();
	void updateEndScreen();

	bool m_exit;

	Presenter m_presenter;
	ConfigManager m_config;
	InputManager m_input;
	State m_state;

	Grid m_grid;
	TitleScreen m_titleScreen;
	Menu m_menu;
	OptionsScreen m_optionsScreen;
	EndScreen m_endScreen;
};