#ifndef _gui_h
#define _gui_h

#include <SDL2/SDL.h>
#include <string>
#include <set>
#include <utility>

const int NONE = -1;

class Window {
public:
	SDL_Window* root = NULL;
	SDL_Renderer* renderer = NULL;

	Window(const char* window_title="", int width=400, int height=300);
	~Window();

	void setWindowTitle(const char* new_title);
	void setWindowSize(int width=NONE, int height=NONE);
	void config(const char* new_window_title="", int new_width=NONE, int new_height=NONE);

	virtual void main_activity() {};
	void close();
};

class RunningProcesses {
public:
	RunningProcesses();
	~RunningProcesses();
	void add_process(Window* win);
	void remove_process(int win_id);
	void remove_process(Window* win);
	void mainloop();
	void kill_all();

private:
	std::set< std::pair<int, Window*> > running_processes;
};

#endif
