#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "gui.h"

Button btn_list[62][71];
ButtonImage bi1;
int check_easy_inside, check_medium_inside, check_hard_inside, check_custom_inside;
bool flagged = false, clicked = false;
SDL_Texture *covered_img, *flagged_img, *clicked_img;
SDL_Rect background;
SDL_Rect menu;
SDL_Rect easy;
SDL_Rect medium;
SDL_Rect hard;
SDL_Rect custom;
SDL_Texture* Background = IMG_LoadTexture(window.renderer, "img_test/grid.jpg");
SDL_Texture* Menu = IMG_LoadTexture(window.renderer, "img_test/bomb.png");
SDL_Texture* Easy = IMG_LoadTexture(window.renderer, "img_test/easy1.png");
SDL_Texture* Medium = IMG_LoadTexture(window.renderer, "img_test/medium1.png");
SDL_Texture* Hard = IMG_LoadTexture(window.renderer, "img_test/hard1.png");
SDL_Texture* Custom = IMG_LoadTexture(window.renderer, "img_test/custom1.png");
MainWindow window("Minesweeper Test", 620, 710);
MinesweeperGUI* game = NULL;

void capture_event(SDL_Event& e) {
	for (int i = 0; i < 30; i++)
	for (int j = 0; j < 30; j++)
		btn_list[i][j].handleEvent(e);

	bi1.handleEvent(e);
}

void capture_game_event(SDL_Event& e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	 std::cout << x << " " << y << std::endl;

	if (game != NULL)
		game->captureEvent(e);
}

void print(SDL_MouseButtonEvent &b) {
	int x = b.x, y = b.y;
	std::cout << x / 10 << " " << y / 10 << std::endl;
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

void draw_everything(MainWindow &window)
{
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

	SDL_SetRenderDrawColor(window.renderer, 255, 0, 0, 255);
	SDL_RenderClear(window.renderer);

	SDL_RenderCopy(window.renderer, Background, NULL, &background);
	SDL_RenderCopy(window.renderer, Menu, NULL, &menu);
	SDL_RenderCopy(window.renderer, Easy, NULL, &easy);
	SDL_RenderCopy(window.renderer, Medium, NULL, &medium);
	SDL_RenderCopy(window.renderer, Hard, NULL, &hard);
	SDL_RenderCopy(window.renderer, Custom, NULL, &custom);

	SDL_RenderPresent(window.renderer);
}

void capture_event1(SDL_Event& e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if(x >= 200 && y >= 140 && x <= 200 + 210 && y <= 140 + 100)
	{
		if(check_easy_inside == 0)
		{
			check_easy_inside = 1;
			Easy = IMG_LoadTexture(window.renderer, "img_test/easy2.png");
			draw_everything(window);
		}
	}
	else
	{
		if(check_easy_inside == 1)
		{
			check_easy_inside = 0;
			Easy = IMG_LoadTexture(window.renderer, "img_test/easy1.png");
			draw_everything(window);
		}
	}
	if(x >= 160 && y >= 290 && x <= 160 + 290 && y <= 290 + 100)
	{
		if(check_medium_inside == 0)
		{
			check_medium_inside = 1;
			Medium = IMG_LoadTexture(window.renderer, "img_test/medium2.png");
			draw_everything(window);
		}
	}
	else
	{
		if(check_medium_inside == 1)
		{
			check_medium_inside = 0;
			Medium = IMG_LoadTexture(window.renderer, "img_test/medium1.png");
			draw_everything(window);
		}
	}
	if(x >= 200 && y >= 440 && x <= 200 + 210 && y <= 440 + 100)
	{
		if(check_hard_inside == 0)
		{
			check_hard_inside = 1;
			Hard = IMG_LoadTexture(window.renderer, "img_test/hard2.png");
			draw_everything(window);
		}
	}
	else
	{
		if(check_hard_inside == 1)
		{
			check_hard_inside = 0;
			Hard = IMG_LoadTexture(window.renderer, "img_test/hard1.png");
			draw_everything(window);
		}
	}
	if(x >= 170 && y >= 590 && x <= 170 + 270 && y <= 590 + 100)
	{
		if(check_custom_inside == 0)
		{
			check_custom_inside = 1;
			Custom = IMG_LoadTexture(window.renderer, "img_test/custom2.png");
			draw_everything(window);
		}
	}
	else
	{
		if(check_custom_inside == 1)
		{
			check_custom_inside = 0;
			Custom = IMG_LoadTexture(window.renderer, "img_test/custom1.png");
			draw_everything(window);
		}
	}
	// cho nay de nhan xem co click ko xong neu click vao cai nao thi choi game theo cai do
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		if(x >= 200 && y >= 140 && x <= 200 + 210 && y <= 140 + 100)
			printf("Easy\n");
		if(x >= 160 && y >= 290 && x <= 160 + 290 && y <= 290 + 100)
			printf("Medium\n");
		if(x >= 200 && y >= 440 && x <= 200 + 210 && y <= 440 + 100)
			printf("Hard\n");
		if(x >= 170 && y >= 590 && x <= 170 + 270 && y <= 590 + 100)
			printf("Custom\n");
	}
}

void setup_homescreen(MainWindow& window) {
	/*SDL_SetRenderDrawColor(window.renderer, 0, 63, 127, 255);
	SDL_RenderClear(window.renderer); // clear window

	clicked_img = IMG_LoadTexture(window.renderer, "img/uncovered_0.png");
	covered_img = IMG_LoadTexture(window.renderer, "img/covered.png");
	flagged_img = IMG_LoadTexture(window.renderer, "img/covered_flagged.png");

	bi1 = ButtonImage(&window, covered_img, 50, 50, 50, 0);
	bi1.drawButton();
	bi1.bindCommand(open_button, "left");
	bi1.bindCommand(reverse_flagged_state, "right");*
	draw_everything(window);
	for (int i = 0; i < 30; i++)
	for (int j = 0; j < 30; j++) {
		btn_list[i][j] = Button(&window, RGBA(255, 255, 255, 255), 10, 10, i*10, j*10);
		btn_list[i][j].setChangingStateBackground(MOUSE_DOWN, RGBA(0, 255, 255, 180));
		btn_list[i][j].setChangingStateBackground(MOUSE_OUT, RGBA(255, 255, 255, 255));
		btn_list[i][j].bindCommand(print, "left");
		btn_list[i][j].drawButton();
	}
	window.captureEvent = &capture_event;
	// SDL_RenderPresent(window.renderer);*/
	draw_everything(window);
	window.captureEvent = capture_event1;
}

void setup_playscreen(MainWindow& window) {
	SDL_SetRenderDrawColor(window.renderer, 0, 63, 127, 255);
	SDL_RenderClear(window.renderer); // clear window
	game = new MinesweeperGUI(&window, 0, 50, "intermediate");
	game->setup();
	game->view(false);
	window.captureEvent = capture_game_event;
	SDL_RenderPresent(window.renderer);
}

int main(int argc, char* argv[]) {
	 setup_homescreen(window);
	//setup_playscreen(window);
	window.mainloop();
	delete game;
	return 0;
}
