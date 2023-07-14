#pragma once

#include "SDL.h"
#include "Globals.h"

struct Coord {
	int x;
	int y;
};

class InputManager {
public:
	InputManager();
	~InputManager();
	
	bool m_mouseIsPressed;
	bool m_mouseButtonReleased;
	bool m_mouseMoved;
	bool m_keyReleased;
	bool m_mouseIsHeld;
	bool m_quit;
	Coord m_mouseCoord;

	void getInput();
};