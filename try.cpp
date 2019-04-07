#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "gui.h"

RunningProcesses tasks;

class MainWindow: public Window {
public:
	MainWindow(const char* window_title, int width, int height): Window(window_title, width, height) {}

	void main_activity() { // Polymorphism
		SDL_SetRenderDrawColor(this->renderer, 0, 63, 127, 255);
		SDL_RenderClear(this->renderer);
		SDL_RenderPresent(this->renderer);

		SDL_Delay(16);
	}
};

int main(int argc, char* argv[]) {
	MainWindow window("SDL2 Test", 450, 350);
	Window window1("SDL2 Test 2", 450, 350);
	// window.close();

	tasks.add_process(&window);
	tasks.add_process(&window1);
	tasks.mainloop();

	tasks.kill_all();
	return 0;
}