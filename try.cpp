#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "gui.h"
#include "core.h"
#include "label.h"

Button btn_list[62][71];
ButtonImage bi1;
int check_easy_inside, check_medium_inside, check_hard_inside, check_custom_inside, check_next_inside, height_custom = 8, width_custom = 8, booms_custom = 10;
bool flagged = false, clicked = false;
MainWindow window("Minesweeper Test", 620, 710);
SDL_Texture *covered_img, *flagged_img, *clicked_img;
SDL_Rect background;
SDL_Rect menu;
SDL_Rect easy;
SDL_Rect medium;
SDL_Rect hard;
SDL_Rect custom;
SDL_Rect tri1;
SDL_Rect tri2;
SDL_Rect next;
SDL_Texture* Background = IMG_LoadTexture(window.renderer, "img_test/grid.jpg");
SDL_Texture* Menu = IMG_LoadTexture(window.renderer, "img_test/bomb.png");
SDL_Texture* Easy = IMG_LoadTexture(window.renderer, "img_test/easy1.png");
SDL_Texture* Medium = IMG_LoadTexture(window.renderer, "img_test/medium1.png");
SDL_Texture* Hard = IMG_LoadTexture(window.renderer, "img_test/hard1.png");
SDL_Texture* Custom = IMG_LoadTexture(window.renderer, "img_test/custom1.png");
SDL_Texture* Tri1 = IMG_LoadTexture(window.renderer, "img_test/triangle1.png");
SDL_Texture* Tri2 = IMG_LoadTexture(window.renderer, "img_test/triangle2.png");
SDL_Texture* Next = IMG_LoadTexture(window.renderer, "img_test/next1.png");
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
	SDL_RenderClear(window.renderer);
	SDL_RenderCopy(window.renderer, Background, NULL, &background);
	SDL_RenderCopy(window.renderer, Menu, NULL, &menu);
	SDL_RenderCopy(window.renderer, Easy, NULL, &easy);
	SDL_RenderCopy(window.renderer, Medium, NULL, &medium);
	SDL_RenderCopy(window.renderer, Hard, NULL, &hard);
	SDL_RenderCopy(window.renderer, Custom, NULL, &custom);
	SDL_RenderPresent(window.renderer);
}

void draw_one(SDL_Rect rect, SDL_Texture* texture)
{
	SDL_RenderCopy(window.renderer, texture, NULL, &rect);
	SDL_RenderPresent(window.renderer);
}

void setup_playscreen(MainWindow& window) {
	SDL_SetRenderDrawColor(window.renderer, 0, 63, 127, 255);
	SDL_RenderClear(window.renderer); // clear window
	game = new MinesweeperGUI(&window, 0, 50, "intermediate");
	game->setup();
	window.captureEvent = capture_game_event;
	SDL_RenderPresent(window.renderer);
}

bool check_inside_right(int px, int py, int x, int y)
{
	if(y > py + 30)
		y = py + 60 - y + py;
	int Y = y - py;
	int X = 2 * Y + px;
	return (x <= X);
}

bool check_inside_left(int px, int py, int x, int y)
{
	if(y > py + 30)
		y = py + 60 - y + py;
	int Y = y - py;
	int X = px + 60 - 2 * Y;
	return (x >= X);
}

void capture_event_custom(SDL_Event& e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Color bg = {255, 255, 255, 255}, fg = {0, 0, 0, 255};
	Label* height_cnt = new Label(&window, std::to_string(height_custom) , "font/consolas.ttf", 52, fg, bg, 100, -1, 280, 90);
	Label* width_cnt = new Label(&window, std::to_string(width_custom) , "font/consolas.ttf", 52, fg, bg, 100, -1, 280, 240);
	Label* booms_cnt = new Label(&window, std::to_string(booms_custom) , "font/consolas.ttf", 52, fg, bg, 100, -1, 280, 390);
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		if(x >= 460 && y >= 80 && x <= 520 && y <= 140 && check_inside_right(460, 80, x, y))
		{
			++height_custom;
		}
		if(x >= 100 && y >= 80 && x <= 160 && y <= 140 && check_inside_left(100, 80, x, y))
		{
			--height_custom;
		}
		if(x >= 460 && y >= 230 && x <= 520 && y <= 290 && check_inside_right(460, 230, x, y))
		{
			++width_custom;
		}
		if(x >= 100 && y >= 230 && x <= 160 && y <= 290 && check_inside_left(100, 230, x, y))
		{
			--width_custom;
		}
		if(x >= 460 && y >= 380 && x <= 520 && y <= 440 && check_inside_right(460, 380, x, y))
		{
			++booms_custom;
		}
		if(x >= 100 && y >= 380 && x <= 160 && y <= 440 && check_inside_left(100, 380, x, y))
		{
			--booms_custom;
		}
		if(x >= 400 && y >= 550 && x <= 350 + 190 && y <= 550 + 80)
		{
			//vao game
		}
	}
	if(x >= 400 && y >= 550 && x <= 350 + 190 && y <= 550 + 80)
	{
		if(check_next_inside == 0)
		{
			check_next_inside = 1;
			Next = IMG_LoadTexture(window.renderer, "img_test/white.png");
			draw_one(next, Next);
			Next = IMG_LoadTexture(window.renderer, "img_test/next2.png");
			draw_one(next, Next);
		}
	}
	else
	{
		if(check_next_inside == 1)
		{
			check_next_inside = 0;
			Next = IMG_LoadTexture(window.renderer, "img_test/white.png");
			draw_one(next, Next);
			Next = IMG_LoadTexture(window.renderer, "img_test/next1.png");
			draw_one(next, Next);
		}
	}
	height_cnt->show();
	width_cnt->show();
	booms_cnt->show();
}

void capture_event_menu(SDL_Event& e) 
{
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
		{
			// fix size
			setup_playscreen(window);
		}
		if(x >= 160 && y >= 290 && x <= 160 + 290 && y <= 290 + 100)
			printf("Medium\n");
		if(x >= 200 && y >= 440 && x <= 200 + 210 && y <= 440 + 100)
			printf("Hard\n");
		if(x >= 170 && y >= 590 && x <= 170 + 270 && y <= 590 + 100)
		{
			SDL_Texture* Background = IMG_LoadTexture(window.renderer, "img_test/white.png");
			SDL_RenderClear(window.renderer);
			SDL_RenderCopy(window.renderer, Background, NULL, &background);
			SDL_RenderPresent(window.renderer);
			tri1.x = 100;
			tri1.y = 80;
			tri1.w = 60;
			tri1.h = 60;
			draw_one(tri1, Tri1);
			tri2.x = 460;
			tri2.y = 80;
			tri2.w = 60;
			tri2.h = 60;
			draw_one(tri2, Tri2);
			tri1.x = 100;
			tri1.y = 230;
			tri1.w = 60;
			tri1.h = 60;
			draw_one(tri1, Tri1);
			tri2.x = 460;
			tri2.y = 230;
			tri2.w = 60;
			tri2.h = 60;
			draw_one(tri2, Tri2);
			tri1.x = 100;
			tri1.y = 380;
			tri1.w = 60;
			tri1.h = 60;
			draw_one(tri1, Tri1);
			tri2.x = 460;
			tri2.y = 380;
			tri2.w = 60;
			tri2.h = 60;
			draw_one(tri2, Tri2);
			next.x = 400;
			next.y = 550;
			next.w = 190;
			next.h = 80;
			draw_one(next, Next);
			SDL_Color bg = {255, 255, 255, 255}, fg = {0, 0, 0, 255};
			Label* height = new Label(&window, "height", "font/consolas.ttf", 28, fg, bg, 150, -1, 20, 20);
			Label* width = new Label(&window, "width", "font/consolas.ttf", 28, fg, bg, 150, -1, 20, 20 + 150);		
			Label* booms = new Label(&window, "booms", "font/consolas.ttf", 28, fg, bg, 150, -1, 20, 20 + 300);
			height->show();
			width->show();
			booms->show();
			window.captureEvent = capture_event_custom;
		}
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
	window.captureEvent = capture_event_menu;
}

int main(int argc, char* argv[]) {
	TTF_Init();
	 setup_homescreen(window);
	//setup_playscreen(window);
	window.mainloop();
	delete game;
	return 0;
}
