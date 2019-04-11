#ifndef _CORE_H
#define _CORE_H

#include <string>

class MinesweeperCore {
public:
	MinesweeperCore(std::string level="beginner");
	MinesweeperCore(int _w, int _h, int _bombs);
	~MinesweeperCore();
	void setup();
	void updateStatus(int r, int c);

private:
	int width;
	int height;
	int bombs;
	int status[101][101];
	int count_bombs[101][101];
	bool game_over = false;

	static const int BOMB = -1;
	enum cell_status {
		COVERED,
		OPENED,
		FLAGGED
	};
};

#endif