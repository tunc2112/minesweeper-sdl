#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <set>
#include <cassert>
#include <utility>
#include "gui.h"

Window::Window(const char* window_title, int width, int height) {
	root = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(root, -1, SDL_RENDERER_ACCELERATED);
}

Window::~Window() {
	renderer = NULL;
	root = NULL;
}

void Window::close() {
	assert(renderer != NULL);
	assert(root != NULL);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(root);
	// SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

RunningProcesses::RunningProcesses() {
	running_processes.clear();
	assert(SDL_Init(SDL_INIT_VIDEO) == 0);
}

RunningProcesses::~RunningProcesses() {
	kill_all();
}

void RunningProcesses::add_process(Window* win) {
	int win_id = SDL_GetWindowID(win->root);
	running_processes.insert(std::make_pair(win_id, win));
}

void RunningProcesses::remove_process(int win_id) {
	std::pair<int, Window*> tmp(win_id, NULL);
	std::set< std::pair<int, Window*> >::iterator win_it = running_processes.lower_bound(tmp);

	assert(win_it != running_processes.end() && win_it->second != NULL);

	Window* win = win_it->second;
	if (win != NULL) {
		win->close();
		running_processes.erase(win_it);
	}

	if (running_processes.size() == 0) { // all processes are closed
		SDL_Quit();
		exit(0);
	}
}

void RunningProcesses::remove_process(Window* win) {
	assert(win != NULL);

	if (win != NULL) {
		int win_id = SDL_GetWindowID(win->root);
		std::pair<int, Window*> tmp(win_id, win);
		std::set< std::pair<int, Window*> >::iterator win_it = running_processes.find(tmp);
		assert(win_it != running_processes.end());

		win->close();
		running_processes.erase(win_it);
	}
}

void RunningProcesses::kill_all() {
	// SDL_Quit shuts down all SDL subsystems and frees the resources allocated to them. 
	// This should always be called before you exit. 
	/*
	// avoiding memory leak
	for (std::set< std::pair<int, Window*> >::iterator
	    win_it = running_processes.begin(); win_it != running_processes.end(); win_it++) {
		Window* win = win_it->second;
		win->close();
	}
	*/
	SDL_Quit();
	running_processes.clear();
}

void RunningProcesses::mainloop() {
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
				break;
			}
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
					// Window* win = SDL_GetWindowFromID(event.window.windowID);
					// remove_process(win);
					remove_process(event.window.windowID);
				}
			}
		}
		for (std::set< std::pair<int, Window*> >::iterator
		    win_it = running_processes.begin(); win_it != running_processes.end(); win_it++) {
			Window* win = win_it->second;
			win->main_activity();
		}
	}
	kill_all();
}
