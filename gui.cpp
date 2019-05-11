#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <string>
#include "gui.h"

MainWindow::MainWindow()
{};

MainWindow::MainWindow(std::string window_title, int width, int height)
{
	root = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_HIDDEN);

	renderer = SDL_CreateRenderer(root, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE|
		                                    SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_ShowWindow(root); // prevent not showing elements on renderer
}

MainWindow::~MainWindow()
{
	renderer = NULL;
	root = NULL;
}

void MainWindow::setWindowSize(int width, int height)
{
	SDL_SetWindowSize(root, width, height);
}

void MainWindow::center()
{
	SDL_SetWindowPosition(root, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void MainWindow::close()
{
	assert(renderer != NULL);
	assert(root != NULL);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(root);
}

void MainWindow::mainloop()
{
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			if (captureEvent != NULL)
				captureEvent(event);
		}
		// SDL_Delay(10);
	}
}

ButtonImage::ButtonImage()
{}

ButtonImage::ButtonImage(MainWindow* win, std::string img_dir, int w, int h, int px, int py)
{
	parent = win;
	width = w;
	height = h;
	bg_image = IMG_LoadTexture(win->renderer, img_dir.c_str());
	packed_x = px;
	packed_y = py;

	btn_rect.x = packed_x;
	btn_rect.y = packed_y;
	btn_rect.w = width;
	btn_rect.h = height;
}

ButtonImage::ButtonImage(MainWindow* win, SDL_Texture* img, int w, int h, int px, int py)
{
	parent = win;
	width = w;
	height = h;
	bg_image = img;
	packed_x = px;
	packed_y = py;

	btn_rect.x = packed_x;
	btn_rect.y = packed_y;
	btn_rect.w = width;
	btn_rect.h = height;
}

ButtonImage::~ButtonImage()
{
	/*
	if (bg_image != NULL)
		SDL_DestroyTexture(bg_image);

	left_click_command = NULL;
	middle_click_command = NULL;
	right_click_command = NULL;
	*/
}

void ButtonImage::drawButton(bool lazy_loading)
{
	SDL_RenderCopy(parent->renderer, bg_image, NULL, &btn_rect);
	if (!lazy_loading)
		SDL_RenderPresent(parent->renderer);
}

bool ButtonImage::isXYInside(int x, int y)
{
	return (packed_x <= x && x <= packed_x + width && packed_y <= y && y <= packed_y + height);
}

void ButtonImage::setBackground(SDL_Texture* img, bool lazy_loading)
{
	bg_image = img;
	SDL_RenderCopy(parent->renderer, img, NULL, &btn_rect);
	if (!lazy_loading)
		SDL_RenderPresent(parent->renderer);
}
