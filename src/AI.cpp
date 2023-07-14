#include "AI.h"

AI::AI() {}

AI::~AI() {}

int2 AI::play(Difficulty diff, const Grid& grid) {
	switch (diff) {
	case Difficulty::Easy:
		return playEasy(grid);
		break;
	case Difficulty::Medium:
		return playMedium(grid);
		break;
	case Difficulty::Hard:
		return playHard(grid);
		break;
	default:
		break;
	}

	return int2(-1, -1);
}

int2 AI::playEasy(const Grid& grid) {
	//Plays random
	int x = rand() % grid.getRemainingTiles();
	vector<bool> tileState = grid.getTilesState();
	for (int i = 0; i < grid.getW() * grid.getH(); i++) {
		if (tileState[i]) {
			x--;
		}
		if (x == -1) {
			return int2(i % grid.getW(), i / grid.getW());
		}
	}
	return int2(-1, -1);//Shouldn't get to here
}

int2 AI::playMedium(const Grid& grid) {
	//Plays where most tiles are attacked
	vector<bool> tileState = grid.getTilesState();
	int maxAttacked = 0, w = grid.getW(), h = grid.getH();
	int2 maxAttackedPos = int2(-1, -1);
	int* freeInRow;
	int* freeInCol;
	int* freeInDiagLToR;//Goes like this / 
	/* Counted depending on startpa
	h - 1 + w ... h + 1, h , h - 1
							...
							2
							1
							0
		Formula: (w - tileCol - 1) + (h - 1 - tileRow) = w + h - tileCol - tileRow - 2
	*/
	int* freeInDiagRToL;//Goes like this \ 
	/* Counted depending on start
	h - 1, h, h + 1 ... h - 1 + w
	...
	2
	1
	0
		Formula: tileCol + (h - 1 - tileRow) = tileCol + h - tileRow - 1
	*/
	freeInCol = new int[w]();
	freeInRow = new int[h]();
	freeInDiagLToR = new int[w + h - 1]();
	freeInDiagRToL = new int[w + h - 1]();

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			bool tileFree = tileState[i + j * w];
			if (tileFree) {
				freeInCol[i]++;
				freeInRow[j]++;
				freeInDiagRToL[i + h - j - 1]++;
				freeInDiagLToR[w + h - i - j - 2]++;
			}
		}
	}
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (tileState[i + j * w]) {//Can place queen on tile
				// - 3 because the tile that the queen is standing on is counted four times
				int attacked = freeInCol[i] + freeInRow[j] + freeInDiagRToL[i + h - j - 1] + freeInDiagLToR[w + h - i - j - 2] - 3;
				if (attacked > maxAttacked) {
					maxAttacked = attacked;
					maxAttackedPos.x = i;
					maxAttackedPos.y = j;
				}
			}
		}
	}
	return maxAttackedPos;
}

int2 AI::playHard(const Grid& grid) {
	return int2();
}
