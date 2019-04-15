#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "gui.h"

Button btn_list[5][5];
ButtonImage bi1;
bool flagged = false, clicked = false;
SDL_Texture *covered_img, *flagged_img, *clicked_img;

void main_activity(SDL_Event& e) {
	for (int i = 0; i < 5; i++)
		btn_list[i][i].handleEvent(e);

	bi1.handleEvent(e);
}

void print(SDL_MouseButtonEvent &b) {
	int x = b.x, y = b.y;
	std::cout << x / 50 << " " << y / 50 << std::endl;
	// int mouse_state = btn_list[y / 50][x / 50].getMouseState();
	// // std::cout << mouse_state << std::endl;
	// btn_list[y / 50][x / 50].setColorByMouseState(mouse_state);
}

void reverse_flagged_state(SDL_MouseButtonEvent &b) {
	if (clicked)
		return;

	flagged = !flagged;
	if (flagged) {
		bi1.setBackground(flagged_img);
	} else {
		bi1.setBackground(covered_img);
	}
}

void open_button(SDL_MouseButtonEvent& b) {
	if (!clicked) {
		std::cout << "boumb!" << std::endl;
		clicked = true;
		bi1.setBackground(clicked_img);
	}
}

void setup_homescreen(MainWindow& window) {
	SDL_SetRenderDrawColor(window.renderer, 0, 63, 127, 255);
	SDL_RenderClear(window.renderer); // clear window

	clicked_img = IMG_LoadTexture(window.renderer, "img/uncovered_0.png");
	covered_img = IMG_LoadTexture(window.renderer, "img/covered.png");
	flagged_img = IMG_LoadTexture(window.renderer, "img/covered_flagged.png");

	bi1 = ButtonImage(&window, covered_img, 50, 50, 50, 0);
	bi1.drawButton();
	bi1.bindCommand(open_button, "left");
	bi1.bindCommand(reverse_flagged_state, "right");

	for (int i = 0; i < 5; i++) {
		btn_list[i][i] = Button(&window, RGBA(255, 255, 255, 255), 50, 50, i*50, i*50);
		btn_list[i][i].setChangingStateBackground(MOUSE_DOWN, RGBA(0, 255, 255, 180));
		btn_list[i][i].setChangingStateBackground(MOUSE_OUT, RGBA(255, 255, 255, 255));
		btn_list[i][i].bindCommand(print, "left");
		btn_list[i][i].drawButton();
	}
	// SDL_RenderPresent(window.renderer);
}

void setup_playscreen(MainWindow& window) {
}

/*
https://wiki.libsdl.org/SDL_CreateTextureFromSurface
https://wiki.libsdl.org/SDL_CreateRGBSurface
https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
*/

int main(int argc, char* argv[]) {
	MainWindow window("SDL2 Test", 450, 350);
	window.main_activity = &main_activity;
	setup_homescreen(window);
	// setup_playscreen(window);
	window.mainloop();
	return 0;
}