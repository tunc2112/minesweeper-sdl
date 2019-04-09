#include "core.h"

MinesweeperCore::MinesweeperCore(string level) {
	if (level == "beginner") {
		width = 8;
		height = 8;
		bombs = 10;
	} else if (level == "intermediate") {
		width = 16;
		height = 16;
		bombs = 40;
	} else if (level == "expert") {
		width = 30;
		height = 16;
		bombs = 99;
	}
}

MinesweeperCore::MinesweeperCore(int _w, int _h, int _bombs) {
	width = _w;
	height = _h;
	bombs = _bombs;
}

MinesweeperCore::~MinesweeperCore() {}

void setup() {
	srand(time(NULL));

	for (int r = 0; r <= height; r++)
		for (int c = 0; c <= width; c++) {
			status[i][j] = COVERED;
			count_bombs[i][j] = 0;
		}

	for (int i = 1; i <= bombs; i++) {
		while (1) {
			int r = (rand() % height) + 1;
			int c = (rand() % width) + 1;
			if (count_bombs[r][c] == 0) {
				status[r][c] = BOMB;
				break;
			}
		}
	}

	for (int r = 1; r <= height; r++)
		for (int c = 1; c <= width; c++)
			if (status[r][c] != BOMB) {
				for (int i = 0; i < 8; i++) {
					int adj_r = r + dr[i], adj_c = c + dc[i];
					if (1 <= adj_r && adj_r <= height && 1 <= adj_c && adj_c <= width && status[adj_r][adj_c] == BOMB)
						count_bombs[r][c]++;
				}
			}
}

void MinesweeperCore::updateStatus(int r, int c) {
	status[r][c] = OPENED;
	// view

	if (count_bombs[r][c] == 0) {
		for (int i = 0; i < 8; i++) {
			int adj_r = r + dr[i], adj_c = c + dc[i];
			if (1 <= adj_r && adj_r <= height && 1 <= adj_c && adj_c <= width && status[adj_r][adj_c] == COVERED) {
				MinesweeperCore::updateStatus(adj_r, adj_c);
			}
		}
	}
}