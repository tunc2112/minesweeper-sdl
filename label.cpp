#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

void Label::show() {
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text_fg);
	text_texture = SDL_CreateTextureFromSurface(parent->renderer, surface);
	SDL_FreeSurface(surface);

	// get real size of text
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(text_texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { packed_x, packed_y, texW, texH };
	SDL_Rect bg_rect = { packed_x, packed_y, (width != -1 ? width : texW), (height != -1 ? height : texH) };
	// fixed with/height or not

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
	SDL_RenderCopy(parent->renderer, text_texture, NULL, &dstrect);
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