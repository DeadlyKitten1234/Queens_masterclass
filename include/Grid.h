#pragma once

#include "Globals.h"
#include "Tile.h"
#include "Queen.h"
#include <vector>
using std::vector;

class Grid {
public:
	Grid();
	Grid(int w, int h, int screenW, int screenH);
	~Grid();

	static void setSize(int w, int h, int screenW, int screenH);

	static int mouseOnTile(int msouseX, int mouseY);
	static void update(bool mousePressed, bool mouseReleased, int mouseX, int mouseY);
	static void draw();

	static bool gameOver();

	static bool getPlayerOnTurn();
	static int getRemainingTiles();
	static int getTileSize();
	static int2 getGridStPos();
	static vector<bool> getTilesState();//Free or attacked
	static int getW();
	static int getH();

private:
	static void attackTiles(int queenCol, int queenRow);

	static int m_width;
	static int m_height;
	static int m_offsetX;
	static int m_offsetY;
	static int m_tileSize;
	static int m_tilePressed;
	static int m_remainingTiles;

	static bool m_secondPlayerOnTurn;

	static Tile** m_tile;

	static vector<Queen> m_queen;
};