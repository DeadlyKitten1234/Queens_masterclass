#include <cmath>
#include <algorithm>
using std::min;
using std::sqrt;
#include "Grid.h"

int Grid::m_width = 0;
int Grid::m_height = 0;
int Grid::m_offsetX = 0;
int Grid::m_offsetY = 0;
int Grid::m_tileSize = 0;
int Grid::m_tilePressed = -1;
int Grid::m_remainingTiles = -1;
bool Grid::m_secondPlayerOnTurn = 0;
Tile** Grid::m_tile = nullptr;
vector<Queen> Grid::m_queen = vector<Queen>();

Grid::Grid() {
	m_width = 0;
	m_height = 0;
	m_tilePressed = -1;
	m_remainingTiles = -1;
}

Grid::Grid(int w, int h, int screenW, int screenH) {
	m_width = w;
	m_height = h;
	m_tileSize = min(min(100, screenW / w), screenH / h);
	m_offsetX = (screenW - m_tileSize * w) / 2;
	m_offsetY = (screenH - m_tileSize * h) / 2;
	m_remainingTiles = w * h;
}

Grid::~Grid() {}

void Grid::setSize(int w, int h, int screenW, int screenH) {
	for (int i = 0; i < m_width; i++) {
		delete[] m_tile[i];
	}
	if (m_width > 0 && m_height > 0) {
		delete[] m_tile;
	}
	m_tilePressed = -1;
	m_queen.clear();
	if (w == 0 || h == 0) {
		m_width = 0;
		m_height = 0;
		return;
	}

	m_width = w;
	m_height = h;
	m_tileSize = min(min(100, screenW / w), screenH / h);
	m_offsetX = (screenW - m_tileSize * w) / 2;
	m_offsetY = (screenH - m_tileSize * h) / 2;
	m_remainingTiles = w * h;
	m_secondPlayerOnTurn = 0;

	m_tile = new Tile*[m_width]();
	for (int i = 0; i < m_width; i++) {
		m_tile[i] = new Tile[m_height]();
	}

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			m_tile[i][j].setRect(m_offsetX + i * m_tileSize, m_offsetY + j * m_tileSize, m_tileSize, m_tileSize);
		}
	}

}

int Grid::mouseOnTile(int mouseX, int mouseY) {
	if (mouseX < m_offsetX || m_offsetX + m_tileSize * m_width <= mouseX || mouseY < m_offsetY || m_offsetY + m_tileSize * m_height <= mouseY) {
		return -1;
	}
	return (mouseX - m_offsetX) / m_tileSize + (mouseY - m_offsetY) / m_tileSize * m_width;
}

void Grid::attackTiles(int queenCol, int queenRow) {
	m_remainingTiles--;
	for (int i = 0; i < 9; i++) {
		int offset = (i / 3 - 1) * 1 + (i % 3 - 1) * m_width;
		if (offset == 0) {
			continue;
		}
		int x = queenCol, y = queenRow, j = 0;
		while (0 <= x && x < m_width && 0 <= y && y < m_height) {
			if (!m_tile[x][y].getAttacked()) {
				m_remainingTiles--;
			}
			m_tile[x][y].makeAttacked();
			//m_tile[x][y].changeTexture(j);
			m_tile[x][y].changeTexture(min(7, int(sqrt(10000 / (m_width * m_height)))) * j);
			x += (i / 3 - 1);
			y += (i % 3 - 1);
			j++;
		}
	}
}

void Grid::update(bool mousePressed, bool mouseReleased, int mouseX, int mouseY) {
	if (mousePressed) {
		m_tilePressed = mouseOnTile(mouseX, mouseY);
	}
	if (mouseReleased) {
		if (mouseOnTile(mouseX, mouseY) == m_tilePressed && m_tilePressed >= 0) {
			int col = m_tilePressed % m_width, row = m_tilePressed / m_width;
			if (m_tile[col][row].getAttacked()) {
				return;
			}
			//Place queen
			m_secondPlayerOnTurn = !m_secondPlayerOnTurn;
			m_tile[col][row].putQueenOnTile();
			m_queen.push_back(Queen());
			m_queen[m_queen.size() - 1].setTile(col, row, m_tileSize, m_offsetX, m_offsetY);
			attackTiles(col, row);
		}
	}
}

void Grid::draw() {
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			m_tile[i][j].draw();
		}
	}
	for (int i = 0; i < m_queen.size(); i++) {
		m_queen[i].draw();
	}
}

bool Grid::gameOver() {
	return (m_remainingTiles == 0);
}

bool Grid::getPlayerOnTurn() {
	return m_secondPlayerOnTurn;
}

int Grid::getRemainingTiles() {
	return m_remainingTiles;
}

int Grid::getTileSize() {
	return m_tileSize;
}

int2 Grid::getGridStPos() {
	return int2(m_offsetX, m_offsetY);
}

vector<bool> Grid::getTilesState() {
	vector<bool> ans;
	for (int i = 0; i < m_width * m_height; i++) {
		ans.push_back(m_tile[i % m_width][i / m_width].getAttacked());
		/*Goes
		 ->
		 ->
		 ...
		 And not
		 ||...
		 VV
		*/
	}
	return ans;
}

int Grid::getW() {
	return m_width;
}

int Grid::getH() {
	return m_height;
}
