#pragma once

#include "SDL.h"

class ConfigManager {
public:
	ConfigManager();
	~ConfigManager();

	static void readTextures(SDL_Renderer* renderer);
	static void readOpacityChanges();
	static void readPositions();
};