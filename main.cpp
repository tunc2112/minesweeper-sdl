#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "gui.h"
#include "core.h"
#include "label.h"

const int WIN_WIDTH = 480;
const int WIN_HEIGHT = 640;
const int MAX_CUSTOM_WIDTH = 30;
const int MAX_CUSTOM_HEIGHT = 24;
const int MIN_CUSTOM_WIDTH = 8;
const int MIN_CUSTOM_HEIGHT = 8;

const int TRIANGLE_PADDING = 40;
const int TRIANGLE_HEIGHT = 60;

std::string local_screen = "home";

bool check_easy_inside, check_medium_inside, check_hard_inside, check_custom_inside, check_next_inside;
int height_custom = 8, width_custom = 8, bombs_custom = 10;
MainWindow window;

/* structure: { x, y, w, h} */
SDL_Rect background;
SDL_Rect menu;
SDL_Rect easy;
SDL_Rect medium;
SDL_Rect hard;
SDL_Rect custom;
SDL_Rect next;
SDL_Rect back;
SDL_Rect tri[3][2];

SDL_Texture* IMG_HOME_BACKGROUND;
SDL_Texture* IMG_WHITE;
SDL_Texture* IMG_MENU;
SDL_Texture* IMG_EASY1;
SDL_Texture* IMG_EASY2;
SDL_Texture* IMG_MEDIUM1;
SDL_Texture* IMG_MEDIUM2;
SDL_Texture* IMG_HARD1;
SDL_Texture* IMG_HARD2;
SDL_Texture* IMG_CUSTOM1;
SDL_Texture* IMG_CUSTOM2;
SDL_Texture* IMG_TRI1;
SDL_Texture* IMG_TRI2;
SDL_Texture* IMG_TRI3;
SDL_Texture* IMG_TRI4;
SDL_Texture* IMG_NEXT1;
SDL_Texture* IMG_NEXT2;
SDL_Texture* IMG_BACK;

SDL_Texture* Easy;
SDL_Texture* Medium;
SDL_Texture* Hard;
SDL_Texture* Custom;
SDL_Texture* TriL;
SDL_Texture* TriR;
SDL_Texture* Next;
SDL_Texture* Back;

Label* height_cnt;
Label* width_cnt;
Label* bombs_cnt;

MinesweeperGUI* game = NULL;

void capture_event_menu(SDL_Event& e);
void capture_event_custom(SDL_Event& e);

bool isXYInsideRect(SDL_Rect rect, int x, int y)
{
	return (rect.x <= x && x <= rect.x + rect.w && rect.y <= y && y <= rect.y + rect.h);
}

bool isXYInside_rightTriangle(int row_id, int x, int y)
{
	int px = tri[row_id][1].x;
	int py = tri[row_id][1].y;

	if (px <= x && x <= px + tri[row_id][1].w && py <= y && y <= py + tri[row_id][1].h)
	{
		if (y > py + TRIANGLE_HEIGHT / 2)
			y = py + TRIANGLE_HEIGHT - y + py;
		int Y = y - py;
		int X = 2 * Y + px;
		return (x <= X);
	}
	return false;
}

bool isXYInside_leftTriangle(int row_id, int x, int y)
{
	int px = tri[row_id][0].x;
	int py = tri[row_id][0].y;

	if (px <= x && x <= px + tri[row_id][0].w && py <= y && y <= py + tri[row_id][0].h)
	{
		if (y > py + TRIANGLE_HEIGHT / 2)
			y = py + TRIANGLE_HEIGHT - y + py;
		int Y = y - py;
		int X = px + TRIANGLE_HEIGHT - 2 * Y;
		return (x >= X);
	}
	return false;
}

void init()
{
	background.x = 0;
	background.y = 0;
	background.w = WIN_WIDTH;
	background.h = WIN_HEIGHT;
	menu.w = 90;
	menu.h = 90;
	menu.x = (WIN_WIDTH - menu.w) / 2;
	menu.y = 35;
	easy.w = 160;
	easy.h = 80;
	easy.x = (WIN_WIDTH - easy.w) / 2;
	easy.y = 150;
	medium.w = 310;
	medium.h = 90;
	medium.x = (WIN_WIDTH - medium.w) / 2;
	medium.y = 270;
	hard.w = 180;
	hard.h = 70;
	hard.x = (WIN_WIDTH - hard.w) / 2;
	hard.y = 395;
	custom.w = 270;
	custom.h = 100;
	custom.x = (WIN_WIDTH - custom.w) / 2;
	custom.y = 500;

	/*
	int w, h;
	SDL_QueryTexture(IMG_EASY1, NULL, NULL, &w, &h);
	std::cout << w << " " << h << "\n";
	*/

	// 1: L, 2: R
	tri[0][0].x = TRIANGLE_PADDING;
	tri[0][0].y = 80;
	tri[0][0].w = TRIANGLE_HEIGHT;
	tri[0][0].h = TRIANGLE_HEIGHT;

	tri[0][1].x = WIN_WIDTH - TRIANGLE_PADDING - 60;
	tri[0][1].y = 80;
	tri[0][1].w = TRIANGLE_HEIGHT;
	tri[0][1].h = TRIANGLE_HEIGHT;

	tri[1][0].x = TRIANGLE_PADDING;
	tri[1][0].y = 230;
	tri[1][0].w = TRIANGLE_HEIGHT;
	tri[1][0].h = TRIANGLE_HEIGHT;

	tri[1][1].x = WIN_WIDTH - TRIANGLE_PADDING - 60;
	tri[1][1].y = 230;
	tri[1][1].w = TRIANGLE_HEIGHT;
	tri[1][1].h = TRIANGLE_HEIGHT;

	tri[2][0].x = TRIANGLE_PADDING;
	tri[2][0].y = 380;
	tri[2][0].w = TRIANGLE_HEIGHT;
	tri[2][0].h = TRIANGLE_HEIGHT;

	tri[2][1].x = WIN_WIDTH - TRIANGLE_PADDING - 60;
	tri[2][1].y = 380;
	tri[2][1].w = TRIANGLE_HEIGHT;
	tri[2][1].h = TRIANGLE_HEIGHT;

	next.x = 305;
	next.y = 520;
	next.w = 190 / 2;
	next.h = 80 / 2;

	back.x = 80;
	back.y = 520;
	back.w = 40;
	back.h = 40;

	// Lazy loading
	IMG_HOME_BACKGROUND = IMG_LoadTexture(window.renderer, "img/background.png");
	IMG_WHITE = IMG_LoadTexture(window.renderer, "img_test/white.png");

	IMG_MENU = IMG_LoadTexture(window.renderer, "img_test/bomb.png");
	IMG_EASY1 = IMG_LoadTexture(window.renderer, "img_test/easy1.png");
	IMG_EASY2 = IMG_LoadTexture(window.renderer, "img_test/easy2.png");
	IMG_MEDIUM1 = IMG_LoadTexture(window.renderer, "img_test/medium1.png");
	IMG_MEDIUM2 = IMG_LoadTexture(window.renderer, "img_test/medium2.png");
	IMG_HARD1 = IMG_LoadTexture(window.renderer, "img_test/hard1.png");
	IMG_HARD2 = IMG_LoadTexture(window.renderer, "img_test/hard2.png");
	IMG_CUSTOM1 = IMG_LoadTexture(window.renderer, "img_test/custom1.png");
	IMG_CUSTOM2 = IMG_LoadTexture(window.renderer, "img_test/custom2.png");

	IMG_TRI1 = IMG_LoadTexture(window.renderer, "img_test/triangle1.png");
	IMG_TRI2 = IMG_LoadTexture(window.renderer, "img_test/triangle2.png");
	IMG_TRI3 = IMG_LoadTexture(window.renderer, "img_test/triangle3.png");
	IMG_TRI4 = IMG_LoadTexture(window.renderer, "img_test/triangle4.png");

	IMG_NEXT1 = IMG_LoadTexture(window.renderer, "img_test/next1.png");
	IMG_NEXT2 = IMG_LoadTexture(window.renderer, "img_test/next2.png");

	IMG_BACK = IMG_LoadTexture(window.renderer, "img/back_round.png");

	// Assignment
	Easy = IMG_EASY1;
	Medium = IMG_MEDIUM1;
	Hard = IMG_HARD1;
	Custom = IMG_CUSTOM1;
	TriL = IMG_TRI1;
	TriR = IMG_TRI2;
	Next = IMG_NEXT1;
	Back = IMG_BACK;
}

void draw_menu()
{
	SDL_SetRenderDrawColor(window.renderer, 0, 63, 127, 255);
	SDL_RenderClear(window.renderer);
	SDL_RenderCopy(window.renderer, IMG_HOME_BACKGROUND, NULL, &background);
	SDL_RenderCopy(window.renderer, IMG_MENU, NULL, &menu);
	SDL_RenderCopy(window.renderer, Easy, NULL, &easy);
	SDL_RenderCopy(window.renderer, Medium, NULL, &medium);
	SDL_RenderCopy(window.renderer, Hard, NULL, &hard);
	SDL_RenderCopy(window.renderer, Custom, NULL, &custom);
	SDL_RenderPresent(window.renderer);
}

void draw_texture(SDL_Rect rect, SDL_Texture* texture)
{
	SDL_RenderCopy(window.renderer, texture, NULL, &rect);
	SDL_RenderPresent(window.renderer);
}

void setup_homescreen()
{
	local_screen = "home";
	window.setWindowSize(WIN_WIDTH, WIN_HEIGHT);
	window.center();
	draw_menu();
}

void setup_custom_screen()
{
	local_screen = "custom";

	height_custom = MIN_CUSTOM_WIDTH;
	width_custom = MIN_CUSTOM_HEIGHT;
	bombs_custom = 10;

	SDL_RenderClear(window.renderer);
	SDL_RenderCopy(window.renderer, IMG_WHITE, NULL, &background);
	SDL_RenderPresent(window.renderer);

	draw_texture(tri[0][0], TriL);
	draw_texture(tri[0][1], TriR);
	draw_texture(tri[1][0], TriL);
	draw_texture(tri[1][1], TriR);
	draw_texture(tri[2][0], TriL);
	draw_texture(tri[2][1], TriR);

	draw_texture(next, Next);
	draw_texture(back, Back);

	SDL_RenderPresent(window.renderer);

	SDL_Color bg = {255, 255, 255, 255}, fg = {0, 0, 0, 255};
	Label height(&window, "height", "font/consolas.ttf", 28, fg, bg, 150, -1, 20, 20);
	height.show();
	Label width(&window, "width", "font/consolas.ttf", 28, fg, bg, 150, -1, 20, 20 + 150);		
	width.show();
	Label bombs(&window, "bombs", "font/consolas.ttf", 28, fg, bg, 150, -1, 20, 20 + 300);
	bombs.show();

	height_cnt = new Label(&window, std::to_string(height_custom), "font/consolas.ttf", 52, fg, bg,
	                       280, 60, 100, 80);
	width_cnt = new Label(&window, std::to_string(width_custom), "font/consolas.ttf", 52, fg, bg,
	                       280, 60, 100, 230);
	bombs_cnt = new Label(&window, std::to_string(bombs_custom), "font/consolas.ttf", 52, fg, bg,
	                       280, 60, 100, 380);
	// height_cnt->show("center");
	// width_cnt->show("center");
	// bombs_cnt->show("center");
}

void setup_playscreen(std::string level)
{
	local_screen = "game";
	game = new MinesweeperGUI(&window, 0, 0, level);
	game->setup();
}

void setup_playscreen(int w, int h, int b)
{
	local_screen = "game";
	game = new MinesweeperGUI(&window, 0, 0, w, h, b);
	game->setup();
}

void capture_event_menu(SDL_Event& e) 
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (isXYInsideRect(easy, x, y))
	{
		if (!check_easy_inside)
		{
			check_easy_inside = 1;
			Easy = IMG_EASY2;
			draw_menu();
		}
	}
	else
	{
		if (check_easy_inside)
		{
			check_easy_inside = 0;
			Easy = IMG_EASY1;
			draw_menu();
		}
	}
	if (isXYInsideRect(medium, x, y))
	{
		if (!check_medium_inside)
		{
			check_medium_inside = 1;
			Medium = IMG_MEDIUM2;
			draw_menu();
		}
	}
	else
	{
		if (check_medium_inside)
		{
			check_medium_inside = 0;
			Medium = IMG_MEDIUM1;
			draw_menu();
		}
	}
	if (isXYInsideRect(hard, x, y))
	{
		if (!check_hard_inside)
		{
			check_hard_inside = 1;
			Hard = IMG_HARD2;
			draw_menu();
		}
	}
	else
	{
		if (check_hard_inside)
		{
			check_hard_inside = 0;
			Hard = IMG_HARD1;
			draw_menu();
		}
	}
	if (isXYInsideRect(custom, x, y))
	{
		if (!check_custom_inside)
		{
			check_custom_inside = 1;
			Custom = IMG_CUSTOM2;
			draw_menu();
		}
	}
	else
	{
		if (check_custom_inside)
		{
			check_custom_inside = 0;
			Custom = IMG_CUSTOM1;
			draw_menu();
		}
	}
	// enter menu
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (isXYInsideRect(easy, x, y))
		{
			setup_playscreen("easy");
		}
		if (isXYInsideRect(medium, x, y))
		{
			setup_playscreen("medium");
		}
		if (isXYInsideRect(hard, x, y))
		{
			setup_playscreen("hard");
		}
		if (isXYInsideRect(custom, x, y))
		{
			setup_custom_screen();
		}
	}
}

void capture_event_custom(SDL_Event& e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	height_cnt->setText(std::to_string(height_custom));
	height_cnt->show("center");
	width_cnt->setText(std::to_string(width_custom));
	width_cnt->show("center");
	bombs_cnt->setText(std::to_string(bombs_custom));
	bombs_cnt->show("center");

	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (isXYInside_leftTriangle(0, x, y))
		{
			TriL = IMG_TRI3;
			draw_texture(tri[0][0], TriL);
			SDL_Delay(100);
			TriL = IMG_TRI1;
			draw_texture(tri[0][0], TriL);
			if (height_custom > MIN_CUSTOM_HEIGHT)
				--height_custom;
		}
		if (isXYInside_rightTriangle(0, x, y))
		{
			TriR = IMG_TRI4;
			draw_texture(tri[0][1], TriR);
			SDL_Delay(100);
			TriR = IMG_TRI2;
			draw_texture(tri[0][1], TriR);
			if (height_custom < MAX_CUSTOM_HEIGHT)
				++height_custom;
		}
		if (isXYInside_leftTriangle(1, x, y))
		{
			TriL = IMG_TRI3;
			draw_texture(tri[1][0], TriL);
			SDL_Delay(100);
			TriL = IMG_TRI1;
			draw_texture(tri[1][0], TriL);
			if (width_custom > MIN_CUSTOM_WIDTH)
				--width_custom;
		}
		if (isXYInside_rightTriangle(1, x, y))
		{
			TriR = IMG_TRI4;
			draw_texture(tri[1][1], TriR);
			SDL_Delay(100);
			TriR = IMG_TRI2;
			draw_texture(tri[1][1], TriR);
			if (width_custom < MAX_CUSTOM_WIDTH)
				++width_custom;
		}
		if (isXYInside_leftTriangle(2, x, y))
		{
			TriL = IMG_TRI3;
			draw_texture(tri[2][0], TriL);
			SDL_Delay(100);
			TriL = IMG_TRI1;
			draw_texture(tri[2][0], TriL);
			if (bombs_custom > 1)
				--bombs_custom;
		}
		if (isXYInside_rightTriangle(2, x, y))
		{
			TriR = IMG_TRI4;
			draw_texture(tri[2][1], TriR);
			SDL_Delay(100);
			TriR = IMG_TRI2;
			draw_texture(tri[2][1], TriR);
			if (bombs_custom < width_custom * height_custom - 1)
				++bombs_custom;
		}
		if (isXYInsideRect(next, x, y))
		{
			setup_playscreen(width_custom, height_custom, bombs_custom);
		}
		if (isXYInsideRect(back, x, y))
		{
			setup_homescreen();
			return;
		}
	}
	if (isXYInsideRect(next, x, y))
	{
		if (!check_next_inside)
		{
			check_next_inside = 1;
			Next = IMG_WHITE;
			draw_texture(next, Next);
			Next = IMG_NEXT2;
			draw_texture(next, Next);
		}
	}
	else
	{
		if (check_next_inside)
		{
			check_next_inside = 0;
			Next = IMG_WHITE;
			draw_texture(next, Next);
			Next = IMG_NEXT1;
			draw_texture(next, Next);
		}
	}
}

void capture_event(SDL_Event& e)
{
	if (local_screen == "home")
	{
		capture_event_menu(e);
	} else if (local_screen == "custom") {
		capture_event_custom(e);
	} else if (local_screen == "game") {
		if (game != NULL)
		{
			game->captureEvent(e);
			if (game->isGameQuit())
			{
				setup_homescreen();
				// delete game;
			}
		}
	}
	else
	{
		setup_homescreen();
	}
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	TTF_Init();

	window = MainWindow("Minesweeper", WIN_WIDTH, WIN_HEIGHT);
	init();
	window.captureEvent = &capture_event;

	setup_homescreen();
	// setup_playscreen();
	window.mainloop();
	delete game;
	return 0;
}
