#ifndef _LABEL_H
#define _LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "gui.h"

class Label {
public:
	Label();
	Label(MainWindow* win, std::string txt, std::string font_dir, int font_size,
		  SDL_Color fg, SDL_Color bg, int w, int h, int px, int py);
	~Label();
	void setText(std::string new_text);
	void show();

private:
	MainWindow* parent;
	std::string text;
	TTF_Font* font;
	SDL_Color text_fg;
	SDL_Color text_bg;
	SDL_Texture* text_texture;
	int width;
	int height;
	int packed_x;
	int packed_y;
};

#endif
