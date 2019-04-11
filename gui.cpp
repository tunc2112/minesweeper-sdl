#include <SDL2/SDL.h>
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

MainWindow::MainWindow(const char* window_title, int width, int height) {
	root = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(root, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

MainWindow::~MainWindow() {
	renderer = NULL;
	root = NULL;
}

// void MainWindow::main_activity(SDL_Event& e) { SDL_Delay(16); }

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

BombFieldGUI::BombFieldGUI(MainWindow* win, int width, int height, int bombs) {
	parent = win;
	game_core = MinesweeperCore(width, height, bombs);
}

BombFieldGUI::~BombFieldGUI() {}

void BombFieldGUI::showAllCells() {}

void BombFieldGUI::openCells(int r, int c) {}
