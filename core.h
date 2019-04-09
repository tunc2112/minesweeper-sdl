#ifndef _CORE_H
#define _CORE_H

class MinesweeperCore {
public:
	MinesweeperCore(string level="beginner");
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

	const int dr[8] = {-1, -1,  1, 1, -1,  0, 0, 1};
	const int dc[8] = {-1,  1, -1, 1,  0, -1, 1, 0};
	const int BOMB = -1;
	enum cell_status {
		COVERED;
		OPENED;
		FLAGGED;
	};
};

#endif