#ifndef _GUI_H
#define _GUI_H

#include <SDL2/SDL.h>
#include <set>
#include <utility>

class Window {
public:
	SDL_Window* root = NULL;
	SDL_Renderer* renderer = NULL;

	Window(const char* window_title="", int width=400, int height=300);
	~Window();
	/*
	const int NONE = -1;
	void setWindowTitle(const char* new_title);
	void setWindowSize(int width=NONE, int height=NONE);
	void config(const char* new_window_title="", int new_width=NONE, int new_height=NONE);
	*/
	virtual void main_activity() {};
	void close();
};

class RunningProcesses {
public:
	RunningProcesses();
	~RunningProcesses();
	void add_process(Window* win);
	void end_process(int win_id);
	void end_process(Window* win);
	void mainloop();
	void kill_all();

private:
	std::set< std::pair<int, Window*> > running_processes;
};

class BombFieldGUI {
public:
	BombFieldGUI(MinesweeperCore gc);
	~BombFieldGUI();
	void show_all_cells();
	void open_cells(int r, int c);

private:
	MinesweeperCore game_core;
};

#endif
