#ifndef _GUI_H
#define _GUI_H

#include <SDL2/SDL.h>
#include <string>
#include "core.h"

class RGBA {
public:
	int r;
	int g;
	int b;
	int a;

	RGBA(int _r=0, int _g=0, int _b=0, int _a=255);
	RGBA(const RGBA& c);
};

class MainWindow {
public:
	SDL_Window* root = NULL;
	SDL_Renderer* renderer = NULL;

	MainWindow(const char* window_title="", int width=400, int height=300);
	~MainWindow();
	/*
	const int NONE = -1;
	void setWindowTitle(const char* new_title);
	void setWindowSize(int width=NONE, int height=NONE);
	void config(const char* new_window_title="", int new_width=NONE, int new_height=NONE);
	*/
	void setup_inner_elements();
	void mainloop();
	void main_activity(SDL_Event& e);
	void close();
};

typedef void (*command)(SDL_MouseButtonEvent& e);

enum MOUSE_STATE {
	MOUSE_OUT,
	MOUSE_OVER,
	MOUSE_DOWN,
	MOUSE_UP,
	TOTAL_MOUSE_STATES
};

class Button {
public:
	Button();
	Button(MainWindow* win, int w, int h, const RGBA& c, int x=0, int y=0);
	~Button();
	int getMouseState();
	void setChangingStateColor(int state, const RGBA& c);
	void setColorByMouseState(int state);
	void drawButton();
	void bindCommand(command f, std::string clicked_mouse="left");
	void runCommand(SDL_MouseButtonEvent& b, std::string clicked_mouse="left");
	void handleEvent(SDL_Event &e);

private:
	MainWindow* parent;
	int packed_x;
	int packed_y;
	int width;
	int height;
	SDL_Rect btn_rect;
	RGBA color[TOTAL_MOUSE_STATES];
	int mouse_state;

	command left_click_command = NULL;
	command middle_click_command = NULL;
	command right_click_command = NULL;
};

class BombFieldGUI {
public:
	BombFieldGUI(MainWindow* win, int width, int height, int bombs);
	~BombFieldGUI();
	void showAllCells();
	void openCells(int r, int c);

private:
	MainWindow* parent;
	MinesweeperCore game_core;
};

#endif
