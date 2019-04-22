#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <string>
#include <ctime>
#include "gui.h"

int min(int x, int y) {
	return (x < y ? x : y);
}

int max(int x, int y) {
	return (x > y ? x : y);
}

RGBA::RGBA(int _r, int _g, int _b, int _a) {
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

RGBA::RGBA(const RGBA& c) {
	r = c.r;
	g = c.g;
	b = c.b;
	a = c.a;
}

MainWindow::MainWindow(std::string window_title, int width, int height) {
	root = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(root, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

MainWindow::~MainWindow() {
	renderer = NULL;
	root = NULL;
}

void MainWindow::close() {
	assert(renderer != NULL);
	assert(root != NULL);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(root);
	renderer = NULL;
	root = NULL;
}

void MainWindow::mainloop() {
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
				break;
			} else if (event.type == SDL_WINDOWEVENT) {
			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			}
			captureEvent(event);
			SDL_Delay(16);
		}
	}
	close();
}

int _Button::getMouseState() {
	return mouse_state;
}

void _Button::bindCommand(command f, std::string clicked_mouse) {
	if (clicked_mouse == "left")
		left_click_command = f;

	else if (clicked_mouse == "middle")
		middle_click_command = f;

	else if (clicked_mouse == "right")
		right_click_command = f;
}

void _Button::runCommand(SDL_MouseButtonEvent &b, std::string clicked_mouse) {
	if (clicked_mouse == "left")
		left_click_command(b);

	else if (clicked_mouse == "middle")
		middle_click_command(b);

	else if (clicked_mouse == "right")
		right_click_command(b);
}

void _Button::handleEvent(SDL_Event &event) {
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool is_mouse_inside = (packed_x <= x && x <= packed_x + width && packed_y <= y && y <= packed_y + height);
		// printf("%d %d\n", x, y);
		// printf("%d %d %d %d ", packed_x, packed_y, packed_x + width, packed_y + height);
		// printf("%d\n", is_mouse_inside);

		if (is_mouse_inside) {
			// printf("%d %d\n", x, y);
			if (event.type == SDL_MOUSEMOTION) {
				mouse_state = MOUSE_OVER;
				setBackgroundByMouseState(mouse_state);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				mouse_state = MOUSE_DOWN;
				setBackgroundByMouseState(mouse_state);

				SDL_MouseButtonEvent mouse_event = event.button;
				if (mouse_event.button == SDL_BUTTON_LEFT) {
					// printf("%d %d LEFT\n", x, y);
					if (left_click_command != NULL) {
						runCommand(mouse_event, "left");
					}
				}
				else if (mouse_event.button == SDL_BUTTON_MIDDLE) {
					// printf("%d %d MIDDLE\n", x, y);
					if (middle_click_command != NULL) {
						runCommand(mouse_event, "middle");
					}
				}
				else if (mouse_event.button == SDL_BUTTON_RIGHT) {
					// printf("%d %d RIGHT\n", x, y);
					if (right_click_command != NULL) {
						runCommand(mouse_event, "right");
					}
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				mouse_state = MOUSE_UP;
				setBackgroundByMouseState(mouse_state);
			}
		} else {
			mouse_state = MOUSE_OUT;
			setBackgroundByMouseState(mouse_state);
		}
	}
}

Button::Button() {}

Button::Button(MainWindow* win, const RGBA& c, int w, int h, int x, int y) {
	parent = win;
	width = w;
	height = h;
	color[MOUSE_OUT] = c;
	packed_x = x;
	packed_y = y;

	btn_rect.x = packed_x;
	btn_rect.y = packed_y;
	btn_rect.w = width;
	btn_rect.h = height;
}

Button::~Button() {}

void Button::drawButton() {
	SDL_SetRenderDrawColor(parent->renderer, color[MOUSE_OUT].r, color[MOUSE_OUT].g,
	                                         color[MOUSE_OUT].b, color[MOUSE_OUT].a);
	SDL_RenderFillRect(parent->renderer, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}

void Button::setChangingStateBackground(int state, const RGBA& c) {
	assert(state == MOUSE_OUT || state == MOUSE_OVER || state == MOUSE_DOWN || state == MOUSE_UP);
	color[state] = c;
}

void Button::setBackgroundByMouseState(int state) {
	SDL_SetRenderDrawColor(parent->renderer, color[state].r, color[state].g, color[state].b, color[state].a);
	SDL_RenderFillRect(parent->renderer, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}

ButtonImage::ButtonImage() {
	bg_image[MOUSE_OUT] = NULL;
	bg_image[MOUSE_OVER] = NULL;
	bg_image[MOUSE_DOWN] = NULL;
	bg_image[MOUSE_UP] = NULL;
}

ButtonImage::ButtonImage(MainWindow* win, std::string img_dir, int w, int h, int x, int y) {
	parent = win;
	width = w;
	height = h;
	bg_image[DEFAULT] = IMG_LoadTexture(win->renderer, img_dir.c_str());
	bg_image[MOUSE_OUT] = bg_image[DEFAULT];
	packed_x = x;
	packed_y = y;

	btn_rect.x = packed_x;
	btn_rect.y = packed_y;
	btn_rect.w = width;
	btn_rect.h = height;
}

ButtonImage::ButtonImage(MainWindow* win, SDL_Texture* img, int w, int h, int x, int y) {
	parent = win;
	width = w;
	height = h;
	bg_image[DEFAULT] = img;
	bg_image[MOUSE_OUT] = bg_image[DEFAULT];
	packed_x = x;
	packed_y = y;

	btn_rect.x = packed_x;
	btn_rect.y = packed_y;
	btn_rect.w = width;
	btn_rect.h = height;
}

ButtonImage::~ButtonImage() {
	/*
	if (bg_image[MOUSE_OUT] != NULL)
		SDL_DestroyTexture(bg_image[MOUSE_OUT]);

	if (bg_image[MOUSE_OVER] != NULL)
		SDL_DestroyTexture(bg_image[MOUSE_OVER]);

	if (bg_image[MOUSE_DOWN] != NULL)
		SDL_DestroyTexture(bg_image[MOUSE_DOWN]);

	if (bg_image[MOUSE_UP] != NULL)
		SDL_DestroyTexture(bg_image[MOUSE_UP]);
	*/
}

void ButtonImage::drawButton() {
	SDL_RenderCopy(parent->renderer, bg_image[MOUSE_OUT], NULL, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}
/*
void ButtonImage::setChangingStateBackground(int state, SDL_Texture* img) {
	std::cout << state << std::endl;
	assert(state == MOUSE_OUT || state == MOUSE_OVER || state == MOUSE_DOWN || state == MOUSE_UP);
	if (img != NULL)
		bg_image[state] = img;
}

void ButtonImage::setBackgroundByMouseState(int state) {
	SDL_RenderCopy(parent->renderer, bg_image[state], NULL, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}
*/
void ButtonImage::setBackground(SDL_Texture* img) {
	bg_image[DEFAULT] = img;
	SDL_RenderCopy(parent->renderer, img, NULL, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}

MinesweeperGUI::MinesweeperGUI() {}

MinesweeperGUI::MinesweeperGUI(MainWindow* win, int px, int py, std::string level) {
	parent = win;
	packed_x = px;
	packed_y = py;

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

MinesweeperGUI::MinesweeperGUI(MainWindow* win, int px, int py, int _w, int _h, int _bombs) {
	parent = win;
	packed_x = px;
	packed_y = py;

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
}

void MinesweeperGUI::setup() {
	setupCore();
	setupGUI();
}

void MinesweeperGUI::setupCore() {
	game_over = false;

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

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++) {
			cells_image[r][c] = ButtonImage(parent, IMG_COVERED, CELL_WIDTH, CELL_WIDTH, 
			                                packed_x+c*CELL_WIDTH, packed_y+r*CELL_WIDTH);
		}
}

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

void MinesweeperGUI::view(bool open_all) {
	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++) {
			if (cells_status[r][c] == FLAGGED) {
				if (cells_uncovered_value[r][c] == BOMB)
					cells_image[r][c].setBackground(IMG_COVERED_FLAGGED);
				else
					cells_image[r][c].setBackground(IMG_UNCOVERED_INCORRECT_FLAGGED);
			} else if (open_all && cells_status[r][c] == COVERED) {
				openCell(r, c);
			} else if (cells_status[r][c] == COVERED)
				cells_image[r][c].drawButton();
		}
}

void MinesweeperGUI::openCellsFrom(int r, int c) {
	if (cells_uncovered_value[r][c] == BOMB) {
		cells_status[r][c] = OPENED;
		cells_image[r][c].setBackground(IMG_UNCOVERED_EXPLODED);
		MinesweeperGUI::view(true);
		game_over = true;
		return;
	}
	MinesweeperGUI::openCell(r, c);

	if (cells_uncovered_value[r][c] == 0) {
		for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++) // always in range [0, height)
			for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) // always in range [0, width)
			{
				if (cells_status[adj_r][adj_c] == COVERED) {
					MinesweeperGUI::openCellsFrom(adj_r, adj_c);
				}
			}
	}
}

void MinesweeperGUI::captureEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && !game_over) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		bool is_mouse_inside = (packed_x <= mouse_x && mouse_x <= packed_x + CELL_WIDTH*width) && 
		                       (packed_y <= mouse_y && mouse_y <= packed_y + CELL_WIDTH*height);

		if (is_mouse_inside) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				int r = (mouse_y - packed_y) / CELL_WIDTH;
				int c = (mouse_x - packed_x) / CELL_WIDTH;
				SDL_MouseButtonEvent mouse_event = event.button;
				if (mouse_event.button == SDL_BUTTON_LEFT) {
					MinesweeperGUI::openCellsFrom(r, c);
				}
				else if (mouse_event.button == SDL_BUTTON_MIDDLE) {
					if (cells_status[r][c] == OPENED) {
						int count_adjacent_flags = 0;
						for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++) // always in range [0, height)
							for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) // always in range [0, width)
							{
								if (cells_status[adj_r][adj_c] == FLAGGED)
									count_adjacent_flags++;
							}

						if (cells_uncovered_value[r][c] == count_adjacent_flags) {
							for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++)
								for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) {
									if (cells_status[adj_r][adj_c] == COVERED)
										MinesweeperGUI::openCellsFrom(adj_r, adj_c);
								}
						}
					}
				}
				else if (mouse_event.button == SDL_BUTTON_RIGHT) {
					MinesweeperGUI::toggleFlag(r, c);
				}
			}
		}
	}
}