#ifndef _CORE_H
#define _CORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <queue>
#include <fstream>
#include "gui.h"
#include "stopwatch.h"
#include "label.h"

class MinesweeperGUI
{
public:
	MinesweeperGUI();
	MinesweeperGUI(MainWindow* win, int px, int py, std::string lvl="easy");
	MinesweeperGUI(MainWindow* win, int px, int py, int _w, int _h, int _bombs);
	~MinesweeperGUI();
	void setup();
	void newGame();
	void updateHighScore();
	void showHighScore();
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
	Stopwatch* watch;
	SDL_TimerID timer_id = 0;

	const SDL_Color game_bg = {192, 192, 192, 255}; // {0, 63, 127, 255};

	ButtonImage home_btn, face_btn;

	int cells_status[32][32];
	int cells_uncovered_value[32][32];
	ButtonImage cells_image[32][32];

	static const int BOMB = -1;
	enum cell_status 
	{
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

	static const int PADDING = 6;
	static const int INFO_HEIGHT = 24;
	static const int LINE2_START_Y = INFO_HEIGHT + PADDING*2;
	static const int LINE3_START_Y = LINE2_START_Y + PADDING + INFO_HEIGHT;
	static const int CELL_WIDTH = 24;
	static const int FACE_WIDTH = 52;

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

	const SDL_Rect RECT_MINE = {PADDING, LINE2_START_Y, INFO_HEIGHT, INFO_HEIGHT};
	const SDL_Rect RECT_WATCH = {90, LINE2_START_Y, INFO_HEIGHT, INFO_HEIGHT};

	Label* remaining_flags;

	std::string highscore_easy, highscore_medium, highscore_hard;

	void setupCore();
	void setupGUI();
};

#endif
