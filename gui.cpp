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

	renderer = SDL_CreateRenderer(root, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);

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

Image::Image()
{}

Image::Image(MainWindow* win, SDL_Texture* img, int w, int h, int px, int py)
{
	parent = win;
	bg_image = img;
	img_rect.x = px;
	img_rect.y = py;
	img_rect.w = w;
	img_rect.h = h;
}

Image::~Image()
{}

void Image::view()
{
	SDL_RenderCopy(parent->renderer, bg_image, NULL, &img_rect);
	SDL_RenderPresent(parent->renderer);
}

void Image::setBackground(SDL_Texture* img, bool lazy_loading)
{
	bg_image = img;
	SDL_RenderCopy(parent->renderer, bg_image, NULL, &img_rect);
	if (!lazy_loading)
		SDL_RenderPresent(parent->renderer);
}

ButtonImage::ButtonImage()
{
	bg_image = NULL;
	left_click_command = NULL;
	middle_click_command = NULL;
	right_click_command = NULL;
}

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

	left_click_command = NULL;
	middle_click_command = NULL;
	right_click_command = NULL;
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

	left_click_command = NULL;
	middle_click_command = NULL;
	right_click_command = NULL;
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

void ButtonImage::drawButton()
{
	SDL_RenderCopy(parent->renderer, bg_image, NULL, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}

int ButtonImage::getMouseState()
{
	return mouse_state;
}

bool ButtonImage::isXYInside(int x, int y)
{
	return (packed_x <= x && x <= packed_x + width && packed_y <= y && y <= packed_y + height);
}

void ButtonImage::setBackground(SDL_Texture* img)
{
	bg_image = img;
	SDL_RenderCopy(parent->renderer, img, NULL, &btn_rect);
	SDL_RenderPresent(parent->renderer);
}

void ButtonImage::bindCommand(command f, std::string clicked_mouse)
{
	if (clicked_mouse == "left")
		left_click_command = f;

	else if (clicked_mouse == "middle")
		middle_click_command = f;

	else if (clicked_mouse == "right")
		right_click_command = f;
}

void ButtonImage::runCommand(SDL_MouseButtonEvent* b, std::string clicked_mouse)
{
	if (clicked_mouse == "left")
		left_click_command(b);

	else if (clicked_mouse == "middle")
		middle_click_command(b);

	else if (clicked_mouse == "right")
		right_click_command(b);
}

void ButtonImage::handleEvent(SDL_Event &event)
{
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (packed_x <= x && x <= packed_x + width && packed_y <= y && y <= packed_y + height)
		{
			// printf("%d %d\n", x, y);
			if (event.type == SDL_MOUSEMOTION)
			{
				mouse_state = MOUSE_OVER;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				mouse_state = MOUSE_DOWN;

				SDL_MouseButtonEvent mouse_event = event.button;
				if (mouse_event.button == SDL_BUTTON_LEFT)
				{
					if (left_click_command != NULL)
					{
						runCommand(&mouse_event, "left");
					}
				}
				else if (mouse_event.button == SDL_BUTTON_MIDDLE)
				{
					if (middle_click_command != NULL)
					{
						runCommand(&mouse_event, "middle");
					}
				}
				else if (mouse_event.button == SDL_BUTTON_RIGHT)
				{
					if (right_click_command != NULL)
					{
						runCommand(&mouse_event, "right");
					}
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				mouse_state = MOUSE_UP;
			}
		}
		else
		{
			mouse_state = MOUSE_OUT;
		}
	}
}
