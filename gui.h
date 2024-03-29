#ifndef _GUI_H
#define _GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <string>

typedef void (*command)(SDL_MouseButtonEvent* e);
typedef void (*activity)(SDL_Event& e);

class MainWindow
{
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
	void setWindowTitle(std::string new_title);
	void config(std::string new_window_title="", int new_width=NONE, int new_height=NONE);
	*/
	void mainloop();
	void close();
};

class ButtonImage
{
public:
	ButtonImage();
	ButtonImage(MainWindow* win, std::string img_dir, int w, int h, int px=0, int py=0);
	ButtonImage(MainWindow* win, SDL_Texture* img, int w, int h, int px=0, int py=0);
	~ButtonImage();
	void drawButton(bool lazy_loading=false);
	int getMouseState();
	bool isXYInside(int x, int y);
	void setBackground(SDL_Texture* img, bool lazy_loading=false);

private:
	MainWindow* parent = NULL;
	int packed_x;
	int packed_y;
	int width;
	int height;
	SDL_Rect btn_rect;

	SDL_Texture* bg_image = NULL;
};

#endif
