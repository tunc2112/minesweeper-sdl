#include <SDL2/SDL.h>
#include <cstdio>
#include <string>
#include "gui.h"
#include "core.h"

Button btn_list[5][5];

void MainWindow::main_activity(SDL_Event& e) {
	for (int i = 0; i < 5; i++)
		btn_list[i][i].handleEvent(e);
}

void print(SDL_MouseButtonEvent &b) {
	int x = b.x, y = b.y;
	printf("%d %d\n", x / 50, y / 50);
	// int mouse_state = btn_list[y / 50][x / 50].getMouseState();
	// // printf("%d\n", mouse_state);
	// btn_list[y / 50][x / 50].setColorByMouseState(mouse_state);
}

void setup_homescreen(MainWindow& window) {
	SDL_SetRenderDrawColor(window.renderer, 0, 63, 127, 255);
	SDL_RenderClear(window.renderer); // clear window

	for (int i = 0; i < 5; i++) {
		btn_list[i][i] = Button(&window, 50, 50, RGBA(255, 255, 255, 255), i*50, i*50);
		btn_list[i][i].setChangingStateColor(MOUSE_DOWN, RGBA(0, 255, 255, 180));
		btn_list[i][i].setChangingStateColor(MOUSE_OUT, RGBA(255, 255, 255, 255));
		btn_list[i][i].bindCommand(print, "left");
		btn_list[i][i].drawButton();
	}

	SDL_RenderPresent(window.renderer);
}

void setup_playscreen(MainWindow& window) {
}

int main(int argc, char* argv[]) {
	MainWindow window("SDL2 Test", 450, 350);

	setup_homescreen(window);
	// setup_playscreen(window);
	window.mainloop();
	return 0;
}