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

typedef void (*command)(SDL_MouseButtonEvent* e);
typedef void (*activity)(SDL_Event& e);

class MainWindow {
public:
	SDL_Window* root = NULL;
	SDL_Renderer* renderer = NULL;
	// activity captureEvent;
	void (*captureEvent)(SDL_Event& e) = NULL;

	MainWindow();
	MainWindow(std::string window_title, int width, int height);
	~MainWindow();
	void setWindowSize(int width, int height);
	void center();
	/*
	const int NONE = -1;
	void setWindowTitle(std::string new_title);
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

class _Button {
public:
	_Button();
	~_Button() {};
	virtual void drawButton() {};
	int getMouseState();
	void disable();
	void enable();
	bool isXYInside(int x, int y);
	virtual void setBackgroundByMouseState(int state) {};
	void bindCommand(command f, std::string clicked_mouse="left");
	void runCommand(SDL_MouseButtonEvent* b, std::string clicked_mouse="left");
	void handleEvent(SDL_Event& e);
protected:
	MainWindow* parent;
	int packed_x;
	int packed_y;
	int width;
	int height;
	bool is_active = true;
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

#endif
