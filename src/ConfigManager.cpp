#include "ConfigManager.h"
#include "Presenter.h"
#include "TitleScreen.h"
#include "Menu.h"
#include "OptionsScreen.h"
#include "Slider.h"
#include "EndScreen.h"

#include "Tile.h"
#include "Queen.h"
#include <iostream>
#include <string>
#include <fstream>
using std::fstream;
using std::string;

ConfigManager::ConfigManager() {}

ConfigManager::~ConfigManager() {}

void ConfigManager::readTextures(SDL_Renderer* renderer) {
	fstream read;
	read.open("assets\\config\\TexturePath.txt");

	int i = 0;
	while (!read.eof()) {
		string texturePath;
		getline(read, texturePath);
		switch (i) {
		case 0:
			Presenter::M_BACKGROUND_TEXTURE = loadTexture(texturePath, renderer);
			break;
		case 1:


			TitleScreen::M_TITLESCREENTEXTURE = loadTexture(texturePath, renderer);
			break;
		case 2:
			TitleScreen::M_TEXT.m_texture = loadTexture(texturePath, renderer);
			EndScreen::M_TEXT.m_texture = loadTexture(texturePath, renderer);
			break;


		case 3:
			Menu::M_MENUTEXTURE = loadTexture(texturePath, renderer);
			break;
		case 4:
			Menu::M_PLAYBUTTON.m_texture = loadTexture(texturePath, renderer);
			break;
		case 5:
			Menu::M_EXITBUTTON.m_texture = loadTexture(texturePath, renderer);
			break;


		case 6:
			EndScreen::M_BACKGROUNDTEXTURE = loadTexture(texturePath, renderer);
			break;
		case 7:
			EndScreen::M_OVERLAYBLUETEXTURE = loadTexture(texturePath, renderer);
			break;
		case 8:
			EndScreen::M_OVERLAYREDTEXTURE = loadTexture(texturePath, renderer);
			break;


		case 9:
			Tile::M_TILE_TEXTURE = loadTexture(texturePath, renderer);
			break;
		case 10:
			Tile::M_TILE_ATTACKED_TEXTURE = loadTexture(texturePath, renderer);
			break;


		case 11:
			Queen::M_QUEEN_TEXTURE = loadTexture(texturePath, renderer);
			break;

		case 12:
			Slider::M_FRONT_TEXTURE = loadTexture(texturePath, renderer);
			break;
		case 13:
			Slider::M_BACK_TEXTURE = loadTexture(texturePath, renderer);
			break;
		case 14:
			Slider::M_MIDDLE_TEXTURE = loadTexture(texturePath, renderer);
			break;
		case 15:
			Slider::M_BALL_TEXTURE = loadTexture(texturePath, renderer);
			break;
		case 16:
			Slider::M_VALUE_INDICATOR_TEXTURE = loadTexture(texturePath, renderer);
			break;
		case 17:
			Slider::M_VALUE_INDICATOR_SMALL_TEXTURE = loadTexture(texturePath, renderer);
			break;

		case 18:
			OptionsScreen::M_BACKGROUND_TEXTURE = loadTexture(texturePath, renderer);
			break;
		case 19:
			OptionsScreen::M_PLAY_BUTTON.m_texture = loadTexture(texturePath, renderer);
			break;
		case 20:
			OptionsScreen::M_BACK_BUTTON.m_texture = loadTexture(texturePath, renderer);
			break;
		case 21:
			OptionsScreen::M_TEXT[0].m_texture = loadTexture(texturePath, renderer);
			break;
		case 22:
			OptionsScreen::M_TEXT[1].m_texture = loadTexture(texturePath, renderer);
			break;
		case 23:
			OptionsScreen::M_TEXT[2].m_texture = loadTexture(texturePath, renderer);
			break;

		default:
			break;
		}
		
		i++;
	}
}

void ConfigManager::readOpacityChanges() {
	fstream read;
	read.open("assets\\config\\OpacityChange.txt");

	int i = 0;
	while (!read.eof()) {
		string name;
		int opacity;
		read >> name >> opacity;
		switch (i) {
		case 0:
			TitleScreen::M_ALPHA_CHANGE = opacity;
			break;
		case 1:
			Menu::M_ALPHA_CHANGE = opacity;
			break; 
		case 2:
			OptionsScreen::m_alphaDecreaseDefault = opacity;
			break;
		case 3:
			Tile::M_ALPHA_CHANGE = opacity;
			break; 
		}
		i++;
	}
}

void ConfigManager::readPositions() {
	fstream read;
	read.open("assets\\config\\Position.txt");

	int i = 0;
	while (!read.eof()) {
		string name;//Dummy
		int x, y, w, h;
		read >> name >> x >> y >> w >> h;

		switch (i) {
		case 0:
			TitleScreen::M_TEXT.m_rect = { x, y, w, h };
			EndScreen::M_TEXT.m_rect = { x, y, w, h };
			break;
		case 1:
			Menu::M_PLAYBUTTON.m_rect = { x, y, w, h };
			OptionsScreen::M_PLAY_BUTTON.m_rect = { x, y, w, h };
			break;
		case 2:
			Menu::M_EXITBUTTON.m_rect = { x, y, w, h };
			OptionsScreen::M_BACK_BUTTON.m_rect = { x, y, w, h };
			break;

		case 3:
			OptionsScreen::M_TEXT[0].m_rect = { x, y, w, h };
			break;
		case 4:
			OptionsScreen::M_TEXT[1].m_rect = { x, y, w, h };
			break;
		case 5:
			OptionsScreen::M_TEXT[2].m_rect = { x, y, w, h };
			break;

		case 6:
			OptionsScreen::M_SLIDER_POS[0] = { x, y, w, h };
			break;
		case 7:
			OptionsScreen::M_SLIDER_POS[1] = { x, y, w, h };
			break;
		case 8:
			OptionsScreen::M_SLIDER_POS[2] = { x, y, w, h };
			break;
		default:
			break;
		}
		i++;
	}
}
