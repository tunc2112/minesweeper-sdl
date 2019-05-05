#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "gui.h"
#include "stopwatch.h"

Stopwatch::Stopwatch() {};

Stopwatch::Stopwatch(MainWindow* win, std::string font_dir, int font_size,
	                 SDL_Color fg, SDL_Color bg, int px, int py) {
	parent = win;
	font = TTF_OpenFont(font_dir.c_str(), font_size);
	text_fg = fg;
	text_bg = bg;
	packed_x = px;
	packed_y = py;
};

Stopwatch::~Stopwatch() {
	TTF_CloseFont(font);
	SDL_DestroyTexture(text_texture);
}

void Stopwatch::start() {
	is_started = true;
	is_stopped = false;
	old_seconds = -1;
	start_time = SDL_GetTicks() - 1000;
	this->printTime();
}

void Stopwatch::stop() {
	is_started = false;
	is_stopped = true;
}

void Stopwatch::pause() {
	if (is_started && !is_paused) {
		is_paused = true;
		paused_time = SDL_GetTicks() - start_time;
		start_time = 0;
	}
}

void Stopwatch::unpause() {
	if (is_started && is_paused) {
		is_paused = false;
		start_time = SDL_GetTicks() - (paused_time - paused_time % 1000);
		paused_time = 0;
	}
}

bool Stopwatch::isStarted() {
	return is_started;
}

bool Stopwatch::isStopped() {
	return is_stopped;
}

void Stopwatch::printTime() {
	if (!is_stopped) {
		int seconds = (is_started ? (SDL_GetTicks() - start_time) / 1000 : 0);
		if (seconds != old_seconds) { // avoid printing a value multiple times
			old_seconds = seconds;
			int minutes = seconds / 60;
			seconds %= 60;
			std::string text = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
			                   (seconds < 10 ? "0" : "") + std::to_string(seconds);

			SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text_fg);
			text_texture = SDL_CreateTextureFromSurface(parent->renderer, surface);
			SDL_FreeSurface(surface);

			// get real size of text
			int texW = 0;
			int texH = 0;
			SDL_QueryTexture(text_texture, NULL, NULL, &texW, &texH);
			SDL_Rect dstrect = { packed_x, packed_y, texW, texH };

			/*
			// image background
			if (text_bg == NULL) {
				SDL_RenderClear(parent->renderer);
			} else {
				// SDL_RenderCopy(parent->renderer, text_bg, NULL, &bg_rect);
			}
			*/
			// color background
			SDL_SetRenderDrawColor(parent->renderer, text_bg.r, text_bg.g, text_bg.b, text_bg.a);
			SDL_RenderFillRect(parent->renderer, &dstrect);

			// print text to renderer
			SDL_RenderCopy(parent->renderer, text_texture, NULL, &dstrect);
			SDL_RenderPresent(parent->renderer);
		}
	}
}
