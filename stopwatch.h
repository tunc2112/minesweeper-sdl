#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "gui.h"

class Stopwatch
{
public:
	Stopwatch();
	Stopwatch(MainWindow* win, std::string font_dir, int font_size, SDL_Color fg, SDL_Color bg, int px, int py);
	~Stopwatch();
	void printTime();
	std::string getTime();
	void start();
	void stop();
	void pause();
	void unpause();
	void reset();
	bool isStarted();
	bool isStopped();

private:
	MainWindow* parent;
	TTF_Font* font;
	SDL_Color text_fg;
	SDL_Color text_bg;
	SDL_Texture* text_texture;
	int packed_x;
	int packed_y;
	int start_time;
	int paused_time;
	int old_seconds = -1;
	bool is_started = false;
	bool is_paused = false;
	bool is_stopped = false;
};

Uint32 timer_callback(Uint32 interval, void* param);

#endif