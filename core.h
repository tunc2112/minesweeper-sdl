#ifndef _CORE_H
#define _CORE_H

#include <string>
#include "gui.h"

class MinesweeperGUI {
public:
	MinesweeperGUI();
	MinesweeperGUI(MainWindow* win, int px, int py, std::string level="beginner");
	MinesweeperGUI(MainWindow* win, int px, int py, int _w, int _h, int _bombs);
	~MinesweeperGUI();
	void setup();
	// void view();
	void toggleFlag(int r, int c);
	void openCell(int r, int c);
	void openABomb(int r, int c);
	void openCellsFrom(int r, int c);
	void gameOver();
	void captureEvent(SDL_Event& event);

private:
	MainWindow* parent;
	int packed_x;
	int packed_y;
	int width;
	int height;
	int bombs;
	
	ButtonImage face_btn;

	int cells_status[51][51];
	int cells_uncovered_value[51][51];
	ButtonImage cells_image[51][51];
	static const int CELL_WIDTH = 24;
	static const int BOMB = -1;
	enum cell_status {
		COVERED,
		OPENED,
		FLAGGED
	};
	bool is_game_over = false;

	SDL_Texture* IMG_COVERED;
	SDL_Texture* IMG_COVERED_FLAGGED;
	SDL_Texture* IMG_COVERED_MINE;
	SDL_Texture* IMG_UNCOVERED_0;
	SDL_Texture* IMG_UNCOVERED_1;
	SDL_Texture* IMG_UNCOVERED_2;
	SDL_Texture* IMG_UNCOVERED_3;
	SDL_Texture* IMG_UNCOVERED_4;
	SDL_Texture* IMG_UNCOVERED_5;
	SDL_Texture* IMG_UNCOVERED_6;
	SDL_Texture* IMG_UNCOVERED_7;
	SDL_Texture* IMG_UNCOVERED_8;
	SDL_Texture* IMG_UNCOVERED_EXPLODED;
	SDL_Texture* IMG_UNCOVERED_INCORRECT_FLAGGED;
	SDL_Texture* IMG_FACE[5];

	void setupCore();
	void setupGUI();
};

#endif
