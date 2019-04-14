#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <cassert>
#include <string>
#include "gui.h"
#include "core.h"

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

Image::Image(SDL_Renderer* renderer, std::string img_dir, int crop_x, int crop_y, int crop_width, int crop_height) {
	texture = IMG_LoadTexture(renderer, img_dir.c_str());
	assert(texture != NULL);

	texture_part = new SDL_Rect();
	texture_part->x = crop_x;
	texture_part->y = crop_y;
	texture_part->w = crop_width;
	texture_part->h = crop_height;
}

Image::Image(SDL_Texture* img_texture) {
	texture = img_texture;
	assert(texture != NULL);

	texture_part = NULL;
}

Image::Image(SDL_Texture* img_texture, int crop_x, int crop_y, int crop_width, int crop_height) {
	texture = img_texture;
	assert(texture != NULL);

	texture_part = new SDL_Rect();
	texture_part->x = crop_x;
	texture_part->y = crop_y;
	texture_part->w = crop_width;
	texture_part->h = crop_height;
}

Image::~Image() {
	SDL_DestroyTexture(texture);
	texture_part = NULL;
}

void Image::view(SDL_Renderer* renderer, SDL_Rect* dest_rect) {
	SDL_RenderCopy(renderer, texture, texture_part, dest_rect);
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
			}
			else if (event.type == SDL_WINDOWEVENT) {
				continue;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
			}
			main_activity(event);
			SDL_Delay(16);
		}
	}
	close();
}

Button::Button() {};

Button::Button(MainWindow* win, int w, int h, const RGBA& c, int x, int y) {
	parent = win;
	width = w;
	height = h;
	color[MOUSE_OUT] = c;
	packed_x = x;
	packed_y = y;

	btn_rect = {packed_x, packed_y, width, height};
}

Button::~Button() {}

int Button::getMouseState() {
	return mouse_state;
}

void Button::setChangingStateColor(int state, const RGBA& c) {
	assert(state == MOUSE_OUT || state == MOUSE_OVER || state == MOUSE_DOWN || state == MOUSE_UP);
	color[state] = c;
}

void Button::setColorByMouseState(int state) {
	SDL_SetRenderDrawColor(parent->renderer, color[state].r, color[state].g, color[state].b, color[state].a);
	SDL_RenderFillRect(parent->renderer, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}

void Button::drawButton() {
	SDL_SetRenderDrawColor(parent->renderer, color[MOUSE_OUT].r, color[MOUSE_OUT].g,
	                                         color[MOUSE_OUT].b, color[MOUSE_OUT].a);
	SDL_RenderFillRect(parent->renderer, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}

void Button::bindCommand(command f, std::string clicked_mouse) {
	if (clicked_mouse == "left")
		left_click_command = f;

	else if (clicked_mouse == "middle")
		middle_click_command = f;

	else if (clicked_mouse == "right")
		right_click_command = f;
}

void Button::runCommand(SDL_MouseButtonEvent &b, std::string clicked_mouse) {
	if (clicked_mouse == "left")
		left_click_command(b);

	else if (clicked_mouse == "middle")
		middle_click_command(b);

	else if (clicked_mouse == "right")
		right_click_command(b);
}

void Button::handleEvent(SDL_Event &event) {
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
				setColorByMouseState(mouse_state);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				mouse_state = MOUSE_DOWN;
				setColorByMouseState(mouse_state);

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
				setColorByMouseState(mouse_state);
			}
		} else {
			mouse_state = MOUSE_OUT;
			setColorByMouseState(mouse_state);
		}
	}
}
/*
BombFieldGUI::BombFieldGUI(MainWindow* win, int width, int height, int bombs) {
	parent = win;
	game_core = MinesweeperCore(width, height, bombs);
}

BombFieldGUI::~BombFieldGUI() {}

void BombFieldGUI::showAllCells() {}

void BombFieldGUI::openCells(int r, int c) {}
*/
MinesweeperCore::MinesweeperCore(std::string level) {
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

void MinesweeperCore::setup() {
	srand(time(NULL));

	for (int r = 0; r <= height; r++)
		for (int c = 0; c <= width; c++) {
			status[r][c] = COVERED;
			count_bombs[r][c] = 0;
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
				for (int dr = -1; dr <= 1; dr++) 
					for (int dc = -1; dc <= 1; dc++) {
						int adj_r = r + dr, adj_c = c + dc;
						if (1 <= adj_r && adj_r <= height && 1 <= adj_c && adj_c <= width && status[adj_r][adj_c] == BOMB)
							count_bombs[r][c]++;
					}
			}
}

void showAllCells();

void MinesweeperCore::openCells(int r, int c) {
	status[r][c] = OPENED;
	// view

	if (count_bombs[r][c] == 0) {
		for (int dr = -1; dr <= 1; dr++) 
			for (int dc = -1; dc <= 1; dc++) {
				int adj_r = r + dr, adj_c = c + dc;
				if (1 <= adj_r && adj_r <= height && 1 <= adj_c && adj_c <= width && status[adj_r][adj_c] == COVERED) {
					MinesweeperCore::openCells(adj_r, adj_c);
				}
			}
	}
}