#ifndef _GUI_H
#define _GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <string>

class RGBA {
public:
	int r;
	int g;
	int b;
	int a;

	RGBA(int _r=0, int _g=0, int _b=0, int _a=255);
	RGBA(const RGBA& c);
};

typedef void (*command)(SDL_MouseButtonEvent& e);
typedef void (*activity)(SDL_Event& e);

class MainWindow {
public:
	SDL_Window* root = NULL;
	SDL_Renderer* renderer = NULL;
	// activity captureEvent;
	void (*captureEvent)(SDL_Event& e) = NULL;

	MainWindow(std::string window_title="", int width=400, int height=300);
	~MainWindow();
	/*
	const int NONE = -1;
	void setWindowTitle(std::string new_title);
	void setWindowSize(int width=NONE, int height=NONE);
	void config(std::string new_window_title="", int new_width=NONE, int new_height=NONE);
	*/
	void mainloop();
	void close();
};

enum MOUSE_STATE {
	DEFAULT,
	CLICKED,
	MOUSE_OUT,
	MOUSE_OVER,
	MOUSE_DOWN,
	MOUSE_UP,
	TOTAL_MOUSE_STATES
};

class Image {
public:
	Image(MainWindow &win, std::string img_dir) {
		texture = IMG_LoadTexture(win.renderer, img_dir.c_str());
		assert(texture != NULL);
	}

	Image(SDL_Texture* img_texture) {
		texture = img_texture;
		assert(texture != NULL);
	}

	~Image() {
		SDL_DestroyTexture(texture);
	}

	void view(MainWindow &win, SDL_Rect* dest_rect) {
		assert(win.renderer != renderer);
		SDL_RenderCopy(renderer, texture, NULL, dest_rect);
		SDL_RenderPresent(win.renderer);
	}
private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
};

class _Button {
public:
	_Button() {};
	~_Button() {};
	virtual void drawButton() {};
	int getMouseState();
	virtual void setBackgroundByMouseState(int state) {};
	void bindCommand(command f, std::string clicked_mouse="left");
	void runCommand(SDL_MouseButtonEvent& b, std::string clicked_mouse="left");
	void handleEvent(SDL_Event& e);
protected:
	MainWindow* parent;
	int packed_x;
	int packed_y;
	int width;
	int height;
	SDL_Rect btn_rect;
	int mouse_state;
	command left_click_command = NULL;
	command middle_click_command = NULL;
	command right_click_command = NULL;
};

class Button: public _Button {
public:
	Button();
	Button(MainWindow* win, const RGBA& c, int w, int h, int x=0, int y=0);
	~Button();
	void drawButton();
	void setChangingStateBackground(int state, const RGBA& c);
	void setBackgroundByMouseState(int state);
private:
	RGBA color[TOTAL_MOUSE_STATES];
};

class ButtonImage: public _Button {
public:
	ButtonImage();
	ButtonImage(MainWindow* win, std::string img_dir, int w, int h, int x=0, int y=0);
	ButtonImage(MainWindow* win, SDL_Texture* img, int w, int h, int x=0, int y=0);
	~ButtonImage();
	void drawButton();
	// void setChangingStateBackground(int state, SDL_Texture* img);
	// void setBackgroundByMouseState(int state);
	void setBackground(SDL_Texture* img);
private:
	SDL_Texture* bg_image[TOTAL_MOUSE_STATES];
};

class MinesweeperGUI {
public:
	MinesweeperGUI();
	MinesweeperGUI(MainWindow* win, int px, int py, std::string level="beginner");
	MinesweeperGUI(MainWindow* win, int px, int py, int _w, int _h, int _bombs);
	~MinesweeperGUI();
	void setup();
	void toggleFlag(int r, int c);
	void openCell(int r, int c);
	void openABomb(int r, int c);
	void view(bool open_all=false);
	void openCellsFrom(int r, int c);
	void captureEvent(SDL_Event& event);

private:
	MainWindow* parent;
	int packed_x;
	int packed_y;
	int width;
	int height;
	int bombs;
	
	int cells_status[51][51];
	int cells_uncovered_value[51][51];
	ButtonImage cells_image[51][51];
	static const int CELL_WIDTH = 25;
	static const int BOMB = -1;
	enum cell_status {
		COVERED,
		OPENED,
		FLAGGED
	};
	bool game_over = false;

	SDL_Texture* IMG_COVERED;
	SDL_Texture* IMG_COVERED_FLAGGED;
	SDL_Texture* IMG_COVERED_MINE;
	SDL_Texture* IMG_UNCOVERED_0;
	SDL_Texture* IMG_UNCOVERED_1;
	SDL_Texture* IMG_UNCOVERED_2;
	SDL_Texture* IMG_UNCOVERED_3;
	SDL_Texture* IMG_UNCOVERED_4;
	SDL_Texture* IMG_UNCOVERED_5;
	SDL_Texture* IMG_UNCOVERED_6;
	SDL_Texture* IMG_UNCOVERED_7;
	SDL_Texture* IMG_UNCOVERED_8;
	SDL_Texture* IMG_UNCOVERED_EXPLODED;
	SDL_Texture* IMG_UNCOVERED_INCORRECT_FLAGGED;

	void setupCore();
	void setupGUI();
};

#endif
