#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include "gui.h"
#include "core.h"

Button btn_list[5][5];

void main_activity(SDL_Event& e) {
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

	SDL_Texture* img = IMG_LoadTexture(window.renderer, "img/minesweeper_tiles.png");
	int d = 128;
	SDL_Rect r1_dst;
	r1_dst.x = 50;
	r1_dst.y = 0;
	r1_dst.w = d / 4;
	r1_dst.h = d / 4;

	Image i1(img, 0, 0, d, d);
	i1.view(window.renderer, &r1_dst);
	/*
	SDL_Rect r1_src;
	r1_src.x = 0;
	r1_src.y = 0;
	r1_src.w = d;
	r1_src.h = d;

	SDL_RenderCopy(window.renderer, img, &r1_src, &r1_dst);
	*/

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