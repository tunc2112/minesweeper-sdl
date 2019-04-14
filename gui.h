#ifndef _GUI_H
#define _GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

class Image {
public:
	Image(SDL_Renderer* renderer, std::string img_dir, int crop_x, int crop_y, int crop_width, int crop_height);
	Image(SDL_Texture* img_texture);
	Image(SDL_Texture* img_texture, int crop_x, int crop_y, int crop_width, int crop_height);
	void view(SDL_Renderer* renderer, SDL_Rect* dest_rect=NULL);
	~Image();
private:
	SDL_Texture* texture = NULL;
	SDL_Rect* texture_part = NULL;
};

typedef void (*command)(SDL_MouseButtonEvent& e);
typedef void (*activity)(SDL_Event& e);

class MainWindow {
public:
	SDL_Window* root = NULL;
	SDL_Renderer* renderer = NULL;
	// activity main_activity;
	void (*main_activity)(SDL_Event& e);

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
	void handleEvent(SDL_Event &event);

private:
	MainWindow* parent;
	int packed_x;
	int packed_y;
	int width;
	int height;
	SDL_Rect btn_rect;
	Image bg_image[TOTAL_MOUSE_STATES];
	RGBA color[TOTAL_MOUSE_STATES];
	int mouse_state;

	command left_click_command = NULL;
	command middle_click_command = NULL;
	command right_click_command = NULL;

	SDL_Texture* tiles = NULL;
};
/*
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
*/
class MinesweeperCore {
public:
	MinesweeperCore(MainWindow* win, std::string level="beginner");
	MinesweeperCore(MainWindow* win, int _w, int _h, int _bombs);
	~MinesweeperCore();
	void setup();
	void showAllCells();
	void openCells(int r, int c);

private:
	MainWindow* parent;
	int width;
	int height;
	int bombs;
	int status[101][101];
	int count_bombs[101][101];
	bool game_over = false;

	static const int BOMB = -1;
	enum cell_status {
		COVERED,
		OPENED,
		FLAGGED
	};
};

#endif
