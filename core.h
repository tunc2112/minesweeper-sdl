#ifndef _CORE_H
#define _CORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <queue>
#include "gui.h"
#include "stopwatch.h"
#include "label.h"

class MinesweeperGUI {
public:
	Stopwatch* watch;

	MinesweeperGUI();
	MinesweeperGUI(MainWindow* win, int px, int py, std::string lvl="easy");
	MinesweeperGUI(MainWindow* win, int px, int py, int _w, int _h, int _bombs);
	~MinesweeperGUI();
	void setup();
	// void view();
	void toggleFlag(int r, int c);
	void openCell(int r, int c);
	void openABomb(int r, int c);
	void openCellsFrom(int start_r, int start_c, bool is_middle_clicked);
	void gameOver();
	void gameWon();
	bool isGameQuit();
	void askToQuit();
	void captureEvent(SDL_Event& event);

private:
	MainWindow* parent;
	std::string level;
	int packed_x;
	int packed_y;
	int width;
	int height;
	int bombs;
	SDL_TimerID timer_id;

	const SDL_Color game_bg = {192, 192, 192, 255}; // {0, 63, 127, 255};

	ButtonImage home_btn, face_btn;

	int cells_status[51][51];
	int cells_uncovered_value[51][51];
	ButtonImage cells_image[51][51];
	
	static const int PADDING = 6;
	static const int info_height = 24;
	static const int line2_start_y = info_height + 12;
	static const int line3_start_y = line2_start_y + PADDING + info_height;
	static const int CELL_WIDTH = 24;
	static const int FACE_WIDTH = 52;
	static const int BOMB = -1;
	enum cell_status {
		COVERED,
		OPENED,
		FLAGGED
	};
	int count_opened_cells;
	int count_remaining_flags;
	bool is_game_over;
	bool is_game_won;
	bool is_game_quit;
	bool is_in_game;

	std::queue<int> cells_queue;

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

	SDL_Texture* IMG_HOME;
	SDL_Texture* IMG_MINE;
	SDL_Texture* IMG_WATCH;

	Label* remaining_flags;

	void setupCore();
	void setupGUI();
};

#endif
