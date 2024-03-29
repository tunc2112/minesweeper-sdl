#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "gui.h"
#include "label.h"

Label::Label() {}

Label::Label(MainWindow* win, std::string txt, std::string font_dir, int font_size,
	         SDL_Color fg, SDL_Color bg, int w, int h, int px, int py) {
	parent = win;
	text = txt;
	font = TTF_OpenFont(font_dir.c_str(), font_size);
	text_fg = fg;
	text_bg = bg;
	width = w;
	height = h;
	packed_x = px;
	packed_y = py;
};

Label::~Label() {
	TTF_CloseFont(font);
	SDL_DestroyTexture(text_texture);
}

void Label::setText(std::string new_text) {
	text = new_text;
}

void Label::show(std::string alignment) {
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text_fg);
	text_texture = SDL_CreateTextureFromSurface(parent->renderer, surface);
	SDL_FreeSurface(surface);

	// get real size of text
	int textW = 0;
	int textH = 0;
	SDL_QueryTexture(text_texture, NULL, NULL, &textW, &textH);
	SDL_Rect bg_rect = { packed_x, packed_y, (width != -1 ? width : textW), (height != -1 ? height : textH) };
	// fixed with/height or not

	/*
	(px, py)
	   +-------------------+ ^
	   |                   | |
	   |     text here     | height
       |                   | |
       +-------------------+ v
       <------ width ------>
	*/
	SDL_Rect text_rect;
	if (alignment == "center") {
		text_rect.x = packed_x + (bg_rect.w - textW) / 2;
	} else if (alignment == "left") {
		text_rect.x = packed_x;
	} else if (alignment == "right") {
		text_rect.x = packed_x + bg_rect.w - textW;
	}
	text_rect.y = packed_y + (bg_rect.h - textH) / 2;
	text_rect.w = textW;
	text_rect.h = textH;

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
	SDL_RenderFillRect(parent->renderer, &bg_rect);

	// print text to renderer
	SDL_RenderCopy(parent->renderer, text_texture, NULL, &text_rect);
	SDL_RenderPresent(parent->renderer);
}
/*
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	MainWindow window("Test label", 640, 480);
	SDL_Color text_fg = { 255, 255, 255 };
	SDL_Texture* text_bg = IMG_LoadTexture(window.renderer, "img/stopwatch_background.png");
	Label* label = new Label(&window, "ahihi", "font/consolas.ttf", 48, text_fg, text_bg, 50, 50);
	label->show();

	SDL_Event event;
	for (bool quit = false; !quit; ) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
				break;
			}
		}
	}
	delete label;
	window.close();

	TTF_Quit();
	SDL_Quit();

	return 0;
}
*/