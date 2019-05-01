#include <iostream>
#include <ctime>
#include "core.h"

int min(int x, int y) {
	return (x < y ? x : y);
}

int max(int x, int y) {
	return (x > y ? x : y);
}

MinesweeperGUI::MinesweeperGUI() {}

MinesweeperGUI::MinesweeperGUI(MainWindow* win, int px, int py, std::string level) {
	parent = win;
	packed_x = px;
	packed_y = py + FACE_WIDTH; // packed_y = place in Oy of game filed

	if (level == "easy") {
		width = 8;
		height = 8;
		bombs = 10;
	} else if (level == "medium") {
		width = 16;
		height = 16;
		bombs = 40;
	} else if (level == "hard") {
		width = 30;
		height = 16;
		bombs = 99;
	}
}

MinesweeperGUI::MinesweeperGUI(MainWindow* win, int px, int py, int _w, int _h, int _bombs) {
	parent = win;
	packed_x = px;
	packed_y = py + FACE_WIDTH; // packed_y = place in Oy of game filed

	width = _w;
	height = _h;
	bombs = _bombs;
}

MinesweeperGUI::~MinesweeperGUI() {
	SDL_DestroyTexture(IMG_COVERED);
	SDL_DestroyTexture(IMG_COVERED_FLAGGED);
	SDL_DestroyTexture(IMG_COVERED_MINE);
	SDL_DestroyTexture(IMG_UNCOVERED_0);
	SDL_DestroyTexture(IMG_UNCOVERED_1);
	SDL_DestroyTexture(IMG_UNCOVERED_2);
	SDL_DestroyTexture(IMG_UNCOVERED_3);
	SDL_DestroyTexture(IMG_UNCOVERED_4);
	SDL_DestroyTexture(IMG_UNCOVERED_5);
	SDL_DestroyTexture(IMG_UNCOVERED_6);
	SDL_DestroyTexture(IMG_UNCOVERED_7);
	SDL_DestroyTexture(IMG_UNCOVERED_8);
	SDL_DestroyTexture(IMG_UNCOVERED_EXPLODED);
	SDL_DestroyTexture(IMG_UNCOVERED_INCORRECT_FLAGGED);
	SDL_DestroyTexture(IMG_FACE[0]);
	SDL_DestroyTexture(IMG_FACE[1]);
	SDL_DestroyTexture(IMG_FACE[2]);
	SDL_DestroyTexture(IMG_FACE[3]);
	SDL_DestroyTexture(IMG_FACE[4]);
}

void MinesweeperGUI::setup() {
	this->setupCore();
	this->setupGUI();
	// this->view();
}

void MinesweeperGUI::setupCore() {
	count_opened_cells = 0;
	is_game_over = false;

	srand(time(NULL));

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++) {
			cells_status[r][c] = COVERED;
			cells_uncovered_value[r][c] = 0;
		}

	for (int i = 1; i <= bombs; i++) {
		while (1) {
			int r = rand() % height;
			int c = rand() % width;
			if (cells_uncovered_value[r][c] == 0) {
				cells_uncovered_value[r][c] = BOMB;
				break;
			}
		}
	}
	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
			if (cells_uncovered_value[r][c] != BOMB) {
				for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++) // always in range [0, height)
					for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) // always in range [0, width)
					{
						if (cells_uncovered_value[adj_r][adj_c] == BOMB)
							cells_uncovered_value[r][c]++;
					}
			}
}

void MinesweeperGUI::setupGUI() {
	// resize window
	int gameGUI_height = CELL_WIDTH * height;
	int gameGUI_width = CELL_WIDTH * width;
	parent->setWindowSize(packed_x + gameGUI_width, packed_y + gameGUI_height);
	parent->center();
	// set background
	SDL_SetRenderDrawColor(parent->renderer, 192, 192, 192, 255);
	// SDL_SetRenderDrawColor(parent->renderer, 0, 63, 127, 255);
	SDL_RenderClear(parent->renderer); // clear window
	
	IMG_COVERED = IMG_LoadTexture(parent->renderer, "img/covered.png");
	IMG_COVERED_FLAGGED = IMG_LoadTexture(parent->renderer, "img/covered_flagged.png");
	IMG_COVERED_MINE = IMG_LoadTexture(parent->renderer, "img/covered_mine.png");
	IMG_UNCOVERED_0 = IMG_LoadTexture(parent->renderer, "img/uncovered_0.png");
	IMG_UNCOVERED_1 = IMG_LoadTexture(parent->renderer, "img/uncovered_1.png");
	IMG_UNCOVERED_2 = IMG_LoadTexture(parent->renderer, "img/uncovered_2.png");
	IMG_UNCOVERED_3 = IMG_LoadTexture(parent->renderer, "img/uncovered_3.png");
	IMG_UNCOVERED_4 = IMG_LoadTexture(parent->renderer, "img/uncovered_4.png");
	IMG_UNCOVERED_5 = IMG_LoadTexture(parent->renderer, "img/uncovered_5.png");
	IMG_UNCOVERED_6 = IMG_LoadTexture(parent->renderer, "img/uncovered_6.png");
	IMG_UNCOVERED_7 = IMG_LoadTexture(parent->renderer, "img/uncovered_7.png");
	IMG_UNCOVERED_8 = IMG_LoadTexture(parent->renderer, "img/uncovered_8.png");
	IMG_UNCOVERED_EXPLODED = IMG_LoadTexture(parent->renderer, "img/uncovered_exploded.png");
	IMG_UNCOVERED_INCORRECT_FLAGGED = IMG_LoadTexture(parent->renderer, "img/uncovered_incorrect_flagged.png");

	IMG_FACE[0] = IMG_LoadTexture(parent->renderer, "img/face_0.png");
	IMG_FACE[1] = IMG_LoadTexture(parent->renderer, "img/face_1.png");
	IMG_FACE[2] = IMG_LoadTexture(parent->renderer, "img/face_2.png");
	IMG_FACE[3] = IMG_LoadTexture(parent->renderer, "img/face_3.png");
	IMG_FACE[4] = IMG_LoadTexture(parent->renderer, "img/face_4.png");

	SDL_Texture* IMG_HOME = IMG_LoadTexture(parent->renderer, "img/home.png");
	ButtonImage btn_home = ButtonImage(parent, IMG_HOME, 48, 48, 0, 0);
	btn_home.drawButton();

	SDL_Texture* IMG_MINE = IMG_LoadTexture(parent->renderer, "img/mine.png");
	SDL_Rect RECT_MINE = {50, 0, 30, 30};
	SDL_RenderCopy(parent->renderer, IMG_MINE, NULL, &RECT_MINE);

	SDL_Texture* IMG_WATCH = IMG_LoadTexture(parent->renderer, "img/stopwatch.png");
	SDL_Rect RECT_WATCH = {120, 0, 30, 30};
	SDL_RenderCopy(parent->renderer, IMG_WATCH, NULL, &RECT_WATCH);

	face_btn = ButtonImage(parent, IMG_FACE[0], FACE_WIDTH, FACE_WIDTH,
		                   (gameGUI_width - FACE_WIDTH) / 2, packed_y - FACE_WIDTH);
	face_btn.drawButton();

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++) {
			cells_image[r][c] = ButtonImage(parent, IMG_COVERED, CELL_WIDTH, CELL_WIDTH, 
			                                packed_x+c*CELL_WIDTH, packed_y+r*CELL_WIDTH);
			cells_image[r][c].drawButton();
		}
}
/*
void MinesweeperGUI::view() {
	face_btn.drawButton();

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++) {
			cells_image[r][c].drawButton();
		}
}
*/
void MinesweeperGUI::toggleFlag(int r, int c) {
	if (cells_status[r][c] == FLAGGED) {
		cells_status[r][c] = COVERED;
		cells_image[r][c].setBackground(IMG_COVERED);
	} else if (cells_status[r][c] == COVERED) {
		cells_status[r][c] = FLAGGED;
		cells_image[r][c].setBackground(IMG_COVERED_FLAGGED);
	}
}

void MinesweeperGUI::openCell(int r, int c) {
	if (cells_status[r][c] == COVERED) {
		count_opened_cells++;

		cells_status[r][c] = OPENED;
		if (cells_uncovered_value[r][c] == BOMB) {
			cells_image[r][c].setBackground(IMG_COVERED_MINE);
		} else if (cells_uncovered_value[r][c] == 0)
			cells_image[r][c].setBackground(IMG_UNCOVERED_0);
		else if (cells_uncovered_value[r][c] == 1)
			cells_image[r][c].setBackground(IMG_UNCOVERED_1);
		else if (cells_uncovered_value[r][c] == 2)
			cells_image[r][c].setBackground(IMG_UNCOVERED_2);
		else if (cells_uncovered_value[r][c] == 3)
			cells_image[r][c].setBackground(IMG_UNCOVERED_3);
		else if (cells_uncovered_value[r][c] == 4)
			cells_image[r][c].setBackground(IMG_UNCOVERED_4);
		else if (cells_uncovered_value[r][c] == 5)
			cells_image[r][c].setBackground(IMG_UNCOVERED_5);
		else if (cells_uncovered_value[r][c] == 6)
			cells_image[r][c].setBackground(IMG_UNCOVERED_6);
		else if (cells_uncovered_value[r][c] == 7)
			cells_image[r][c].setBackground(IMG_UNCOVERED_7);
		else if (cells_uncovered_value[r][c] == 8)
			cells_image[r][c].setBackground(IMG_UNCOVERED_8);
	}
}

void MinesweeperGUI::openABomb(int r, int c) {
	cells_status[r][c] = OPENED;
	cells_image[r][c].setBackground(IMG_UNCOVERED_EXPLODED);
}

void MinesweeperGUI::openCellsFrom(int r, int c) {
	if (cells_uncovered_value[r][c] == BOMB) {
		this->openABomb(r, c);
		this->gameOver();
		return;
	}
	if (cells_status[r][c] == COVERED) {
		this->openCell(r, c);
	}

	if (cells_uncovered_value[r][c] == 0) {
		for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++) // always in range [0, height)
			for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) // always in range [0, width)
			{
				if (cells_status[adj_r][adj_c] == COVERED) {
					this->openCellsFrom(adj_r, adj_c);
				}
			}
	}
}

void MinesweeperGUI::gameOver() {
	is_game_over = true;

	face_btn.setBackground(IMG_LoadTexture(parent->renderer, "img/face_3.png"));

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++) {
			cells_image[r][c].disable();

			if (cells_status[r][c] == FLAGGED) {
				if (cells_uncovered_value[r][c] != BOMB)
					cells_image[r][c].setBackground(IMG_UNCOVERED_INCORRECT_FLAGGED);
			}
			else if (cells_status[r][c] == COVERED) {
				if (cells_uncovered_value[r][c] == BOMB)
					cells_image[r][c].setBackground(IMG_COVERED_MINE);
			}
		}
}

void MinesweeperGUI::captureEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		bool is_mouse_inside_gamefield = (packed_x <= mouse_x && mouse_x <= packed_x + CELL_WIDTH*width) && 
		                                 (packed_y <= mouse_y && mouse_y <= packed_y + CELL_WIDTH*height);

		SDL_MouseButtonEvent mouse_event = event.button;

		if (face_btn.isXYInside(mouse_x, mouse_y)) {
			if (mouse_event.button == SDL_BUTTON_LEFT) {
				if (event.type == SDL_MOUSEBUTTONDOWN)
					face_btn.setBackground(IMG_FACE[1]);
				else if (event.type == SDL_MOUSEBUTTONUP)
					this->setup();
			}
		} else {
			if (is_game_over) {
				face_btn.setBackground(IMG_FACE[3]);
			} else if (count_opened_cells == height * width - bombs) { // win game
				face_btn.setBackground(IMG_FACE[4]);
			} else {
				if (is_mouse_inside_gamefield) {
					if (event.type == SDL_MOUSEBUTTONDOWN) {
						if (mouse_event.button != SDL_BUTTON_RIGHT)
							face_btn.setBackground(IMG_FACE[2]);
					} else if (event.type == SDL_MOUSEBUTTONUP) {
						face_btn.setBackground(IMG_FACE[0]);

						int r = (mouse_y - packed_y) / CELL_WIDTH;
						int c = (mouse_x - packed_x) / CELL_WIDTH;
					
						if (mouse_event.button == SDL_BUTTON_LEFT) {
							if (cells_status[r][c] == COVERED)
								this->openCellsFrom(r, c);
							if (count_opened_cells == height * width - bombs) { // win game
								face_btn.setBackground(IMG_FACE[4]);
							}
						}
						else if (mouse_event.button == SDL_BUTTON_MIDDLE) {
							if (cells_status[r][c] == OPENED) {
								int count_adjacent_flags = 0;
								for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++)
									for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) {
										if (cells_status[adj_r][adj_c] == FLAGGED)
											count_adjacent_flags++;
									}

								if (cells_uncovered_value[r][c] == count_adjacent_flags) {
									for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++)
										for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) {
											if (cells_status[adj_r][adj_c] == COVERED) {
												if (cells_uncovered_value[adj_r][adj_c] == BOMB) {
													this->openABomb(adj_r, adj_c);
													this->gameOver();
												}
												this->openCellsFrom(adj_r, adj_c);
											}
										}
									if (count_opened_cells == height * width - bombs) { // win game
										face_btn.setBackground(IMG_FACE[4]);
									}
								}
							}
						}
						else if (mouse_event.button == SDL_BUTTON_RIGHT) {
							this->toggleFlag(r, c);
						}
					}
				} else {
					face_btn.setBackground(IMG_FACE[0]);
				}
			}
		}
	}
}