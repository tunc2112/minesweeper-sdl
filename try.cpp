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

void draw_everything()
{
	SDL_Rect background;
	SDL_Rect menu;
	SDL_Rect easy;
	SDL_Rect medium;
	SDL_Rect hard;
	SDL_Rect custom;
	SDL_Texture* Background;
	SDL_Texture* Easy; 
	SDL_Texture* Medium;
	SDL_Texture* Hard;
	SDL_Texture* Custom;
	SDL_Texture* Menu;
	Background = IMG_LoadTexture(window.renderer, "grid.jpg");
	Menu = IMG_LoadTexture(window.renderer, "bomb.png");
	Easy = IMG_LoadTexture(window.renderer, "easy1.png");
	Medium = IMG_LoadTexture(window.renderer, "medium1.png");
	Hard = IMG_LoadTexture(window.renderer, "hard1.png");
	Custom = IMG_LoadTexture(window.renderer, "custom1.png");
	int w, h;
	SDL_GetWindowSize(window.root, &w, &h);
	background.x = 0;
	background.y = 0;
	background.w = w;
	background.h = h;
	menu.x = 260;
	menu.y = 35;
	menu.w = 100;
	menu.h = 100;
	easy.x = 200;
	easy.y = 140;
	easy.w = 210;
	easy.h = 100;
	medium.x = 160;
	medium.y = 290;
	medium.w = 290;
	medium.h = 100;
	hard.x = 200;
	hard.y = 440;
	hard.w = 210;
	hard.h = 100;
	custom.x = 170;
	custom.y = 590;
	custom.w = 270;
	custom.h = 100;
	SDL_RenderClear(window.renderer);
	SDL_SetRenderDrawColor(window.renderer, 255, 0, 0, 255 );
	SDL_RenderCopy(window.renderer, Background, NULL, &background);
	SDL_RenderCopy(window.renderer, Menu, NULL, &menu);
	SDL_RenderCopy(window.renderer, Easy, NULL, &easy);
	SDL_RenderCopy(window.renderer, Medium, NULL, &medium);
	SDL_RenderCopy(window.renderer, Hard, NULL, &hard);
	SDL_RenderCopy(window.renderer, Custom, NULL, &custom);
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
