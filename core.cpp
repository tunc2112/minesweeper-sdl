#include <iostream>
#include <ctime>
#include <queue>
#include "core.h"
#include "stopwatch.h"

int min(int x, int y)
{
	return (x < y ? x : y);
}

int max(int x, int y)
{
	return (x > y ? x : y);
}

MinesweeperGUI::MinesweeperGUI()
{}

MinesweeperGUI::MinesweeperGUI(MainWindow* win, int px, int py, std::string lvl)
{
	parent = win;
	packed_x = px;
	packed_y = py;
	packed_y += LINE3_START_Y + FACE_WIDTH; // add space for info field

	if (lvl == "easy")
	{
		level = lvl;
		width = 8;
		height = 8;
		bombs = 10;
	}
	else if (lvl == "medium")
	{
		level = lvl;
		width = 16;
		height = 16;
		bombs = 40;
	}
	else if (lvl == "hard")
	{
		level = lvl;
		width = 30;
		height = 16;
		bombs = 99;
	} else 
		level = "custom";
}

MinesweeperGUI::MinesweeperGUI(MainWindow* win, int px, int py, int _w, int _h, int _bombs)
{
	parent = win;
	level = "Custom";
	packed_x = px;
	packed_y = py;
	packed_y += LINE3_START_Y + FACE_WIDTH; // add space for info field

	width = _w;
	height = _h;
	bombs = _bombs;
}

MinesweeperGUI::~MinesweeperGUI()
{
	SDL_DestroyTexture(IMG_COVERED);
	SDL_DestroyTexture(IMG_COVERED_FLAGGED);
	SDL_DestroyTexture(IMG_COVERED_MINE);
	SDL_DestroyTexture(IMG_UNCOVERED_0);
	SDL_DestroyTexture(IMG_UNCOVERED_1);
	SDL_DestroyTexture(IMG_UNCOVERED_2);
	SDL_DestroyTexture(IMG_UNCOVERED_3);
	SDL_DestroyTexture(IMG_UNCOVERED_4);
	SDL_DestroyTexture(IMG_UNCOVERED_5);
	SDL_DestroyTexture(IMG_UNCOVERED_6);
	SDL_DestroyTexture(IMG_UNCOVERED_7);
	SDL_DestroyTexture(IMG_UNCOVERED_8);
	SDL_DestroyTexture(IMG_UNCOVERED_EXPLODED);
	SDL_DestroyTexture(IMG_UNCOVERED_INCORRECT_FLAGGED);
	SDL_DestroyTexture(IMG_FACE[0]);
	SDL_DestroyTexture(IMG_FACE[1]);
	SDL_DestroyTexture(IMG_FACE[2]);
	SDL_DestroyTexture(IMG_FACE[3]);
	SDL_DestroyTexture(IMG_FACE[4]);
	SDL_DestroyTexture(IMG_HOME);
	SDL_DestroyTexture(IMG_MINE);
	SDL_DestroyTexture(IMG_WATCH);

	SDL_RemoveTimer(timer_id);
	delete watch;
	delete remaining_flags;
}

void MinesweeperGUI::setupCore()
{
	count_opened_cells = 0;
	count_remaining_flags = bombs;
	is_game_over = false;
	is_game_won = false;
	is_game_quit = false;

	highscore_easy = "99:59";
	highscore_medium = "99:59";
	highscore_hard = "99:59";

	srand(time(NULL));

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
		{
			cells_status[r][c] = COVERED;
			cells_uncovered_value[r][c] = 0;
		}

	for (int i = 1; i <= bombs; i++)
	{
		while (1)
		{
			int r = rand() % height;
			int c = rand() % width;
			if (cells_uncovered_value[r][c] == 0)
			{
				cells_uncovered_value[r][c] = BOMB;
				break;
			}
		}
	}
	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
			if (cells_uncovered_value[r][c] != BOMB)
			{
				for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++) // always in range [0, height)
					for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) // always in range [0, width)
					{
						if (cells_uncovered_value[adj_r][adj_c] == BOMB)
							cells_uncovered_value[r][c]++;
					}
			}
	/*
	prevent bug: SDL_MOUSEBUTTONDOWN from home/custom screen will open cell(s).
	*/
	is_in_game = false;
}

void MinesweeperGUI::setupGUI()
{
	IMG_COVERED = IMG_LoadTexture(parent->renderer, "img/covered.png");
	IMG_COVERED_FLAGGED = IMG_LoadTexture(parent->renderer, "img/covered_flagged.png");
	IMG_COVERED_MINE = IMG_LoadTexture(parent->renderer, "img/covered_mine.png");
	IMG_UNCOVERED_0 = IMG_LoadTexture(parent->renderer, "img/uncovered_0.png");
	IMG_UNCOVERED_1 = IMG_LoadTexture(parent->renderer, "img/uncovered_1.png");
	IMG_UNCOVERED_2 = IMG_LoadTexture(parent->renderer, "img/uncovered_2.png");
	IMG_UNCOVERED_3 = IMG_LoadTexture(parent->renderer, "img/uncovered_3.png");
	IMG_UNCOVERED_4 = IMG_LoadTexture(parent->renderer, "img/uncovered_4.png");
	IMG_UNCOVERED_5 = IMG_LoadTexture(parent->renderer, "img/uncovered_5.png");
	IMG_UNCOVERED_6 = IMG_LoadTexture(parent->renderer, "img/uncovered_6.png");
	IMG_UNCOVERED_7 = IMG_LoadTexture(parent->renderer, "img/uncovered_7.png");
	IMG_UNCOVERED_8 = IMG_LoadTexture(parent->renderer, "img/uncovered_8.png");
	IMG_UNCOVERED_EXPLODED = IMG_LoadTexture(parent->renderer, "img/uncovered_exploded.png");
	IMG_UNCOVERED_INCORRECT_FLAGGED = IMG_LoadTexture(parent->renderer, "img/uncovered_incorrect_flagged.png");

	IMG_FACE[0] = IMG_LoadTexture(parent->renderer, "img/face_0.png");
	IMG_FACE[1] = IMG_LoadTexture(parent->renderer, "img/face_1.png");
	IMG_FACE[2] = IMG_LoadTexture(parent->renderer, "img/face_2.png");
	IMG_FACE[3] = IMG_LoadTexture(parent->renderer, "img/face_3.png");
	IMG_FACE[4] = IMG_LoadTexture(parent->renderer, "img/face_4.png");

	IMG_HOME = IMG_LoadTexture(parent->renderer, "img/back_round.png");
	IMG_MINE = IMG_LoadTexture(parent->renderer, "img/mine.png");
	IMG_WATCH = IMG_LoadTexture(parent->renderer, "img/stopwatch3.png");

	// resize window
	int gameGUI_height = CELL_WIDTH * height;
	int gameGUI_width = CELL_WIDTH * width;
	parent->setWindowSize(packed_x + gameGUI_width, packed_y + gameGUI_height);
	parent->center();

	// set background
	SDL_SetRenderDrawColor(parent->renderer, game_bg.r, game_bg.g, game_bg.b, game_bg.a);
	SDL_RenderClear(parent->renderer); // clear window

	// setup elements
	SDL_Color text_fg = { 0, 0, 0 };
	
	home_btn = ButtonImage(parent, IMG_HOME, INFO_HEIGHT, INFO_HEIGHT,
	                       packed_x+6, packed_y - LINE3_START_Y - FACE_WIDTH + PADDING);
	home_btn.drawButton();

	// Label level_label(parent, level, "font/consolas.ttf", INFO_HEIGHT, text_fg, game_bg,
	// 	              -1, -1, INFO_HEIGHT + 6, 6);
	// level_label.show();
	//----------------------
	SDL_RenderCopy(parent->renderer, IMG_MINE, NULL, &RECT_MINE);

	remaining_flags = new Label(parent, std::to_string(count_remaining_flags), "font/consolas.ttf", INFO_HEIGHT,
	                            text_fg, game_bg, 50, -1, PADDING+INFO_HEIGHT+PADDING, LINE2_START_Y);
	remaining_flags->show();
	//----------------------
	SDL_RenderCopy(parent->renderer, IMG_WATCH, NULL, &RECT_WATCH);

	watch = new Stopwatch(parent, "font/consolas.ttf", INFO_HEIGHT, text_fg, game_bg, 120, LINE2_START_Y);
	watch->printTime();

	timer_id = SDL_AddTimer(1000, timer_callback, this->watch);
	//----------------------
	face_btn = ButtonImage(parent, IMG_FACE[0], FACE_WIDTH, FACE_WIDTH,
	                       (gameGUI_width - FACE_WIDTH) / 2, LINE3_START_Y);
	face_btn.drawButton();

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
		{
			cells_image[r][c] = Image(parent, IMG_COVERED, CELL_WIDTH, CELL_WIDTH,
			                                packed_x+c*CELL_WIDTH, packed_y+r*CELL_WIDTH);
			cells_image[r][c].view();
		}

	SDL_RenderPresent(parent->renderer);
}

void MinesweeperGUI::setup()
{
	this->setupCore();
	this->setupGUI();
}

void MinesweeperGUI::newGame()
{
	this->setupCore();

	// reset GUI
	remaining_flags->setText(std::to_string(count_remaining_flags));
	remaining_flags->show();
	
	// reset timer
	watch->reset();

	face_btn.setBackground(IMG_FACE[0]);

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
		{
			cells_image[r][c].setBackground(IMG_COVERED, true);
		}

	SDL_RenderPresent(parent->renderer);
}

void MinesweeperGUI::toggleFlag(int r, int c)
{
	if (cells_status[r][c] == FLAGGED)
	{
		count_remaining_flags++;
		remaining_flags->setText(std::to_string(count_remaining_flags));
		remaining_flags->show();

		cells_status[r][c] = COVERED;
		cells_image[r][c].setBackground(IMG_COVERED);
	}
	else if (cells_status[r][c] == COVERED)
	{
		count_remaining_flags--;
		remaining_flags->setText(std::to_string(count_remaining_flags));
		remaining_flags->show();

		cells_status[r][c] = FLAGGED;
		cells_image[r][c].setBackground(IMG_COVERED_FLAGGED);
	}
}

void MinesweeperGUI::openCell(int r, int c)
{
	if (cells_status[r][c] == COVERED)
	{
		count_opened_cells++;

		cells_status[r][c] = OPENED;
		if (cells_uncovered_value[r][c] == BOMB)
			cells_image[r][c].setBackground(IMG_COVERED_MINE, true);
		else if (cells_uncovered_value[r][c] == 0)
			cells_image[r][c].setBackground(IMG_UNCOVERED_0, true);
		else if (cells_uncovered_value[r][c] == 1)
			cells_image[r][c].setBackground(IMG_UNCOVERED_1, true);
		else if (cells_uncovered_value[r][c] == 2)
			cells_image[r][c].setBackground(IMG_UNCOVERED_2, true);
		else if (cells_uncovered_value[r][c] == 3)
			cells_image[r][c].setBackground(IMG_UNCOVERED_3, true);
		else if (cells_uncovered_value[r][c] == 4)
			cells_image[r][c].setBackground(IMG_UNCOVERED_4, true);
		else if (cells_uncovered_value[r][c] == 5)
			cells_image[r][c].setBackground(IMG_UNCOVERED_5, true);
		else if (cells_uncovered_value[r][c] == 6)
			cells_image[r][c].setBackground(IMG_UNCOVERED_6, true);
		else if (cells_uncovered_value[r][c] == 7)
			cells_image[r][c].setBackground(IMG_UNCOVERED_7, true);
		else if (cells_uncovered_value[r][c] == 8)
			cells_image[r][c].setBackground(IMG_UNCOVERED_8, true);
	}
}

void MinesweeperGUI::openABomb(int r, int c)
{
	cells_status[r][c] = OPENED;
	cells_image[r][c].setBackground(IMG_UNCOVERED_EXPLODED, true);
}

void MinesweeperGUI::openCellsFrom(int start_r, int start_c, bool is_middle_clicked)
{
	// zip data: (r, c) -> r * width + r
	std::queue<int>().swap(cells_queue);
	if (is_middle_clicked)
	{
		bool is_caught_bomb = false;

		for (int adj_r = max(0, start_r - 1); adj_r <= min(start_r + 1, height-1); adj_r++)
			for (int adj_c = max(0, start_c - 1); adj_c <= min(start_c + 1, width-1); adj_c++)
			{
				if (cells_status[adj_r][adj_c] == COVERED)
				{
					if (cells_uncovered_value[adj_r][adj_c] == BOMB)
					{
						this->openABomb(adj_r, adj_c);
						is_caught_bomb = true;
					}
					else
					{
						this->openCell(adj_r, adj_c);
						if (cells_uncovered_value[adj_r][adj_c] == 0)
							cells_queue.push(adj_r * width + adj_c);
					}
				}
			}

		if (is_caught_bomb)
		{
			this->gameOver();
		}
	}
	else
	{
		if (cells_status[start_r][start_c] == COVERED)
		{
			if (cells_uncovered_value[start_r][start_c] == BOMB)
			{
				this->openABomb(start_r, start_c);
				this->gameOver();
				return;
			}
			else
			{
				this->openCell(start_r, start_c);
				if (cells_uncovered_value[start_r][start_c] == 0)
					cells_queue.push(start_r * width + start_c);
			}
		}
	}
	while (!cells_queue.empty())
	{
		int top = cells_queue.front();
		cells_queue.pop();
		int r = top / width;
		int c = top % width;

		for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++) // always in range [0, height)
			for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++) // always in range [0, width)
			{
				if (cells_status[adj_r][adj_c] == COVERED && cells_uncovered_value[adj_r][adj_c] != BOMB)
				{
					this->openCell(adj_r, adj_c);
					if (cells_uncovered_value[adj_r][adj_c] == 0)
						cells_queue.push(adj_r * width + adj_c);
				}
			}
	}
	SDL_RenderPresent(parent->renderer);
}

void MinesweeperGUI::gameOver()
{
	is_game_over = true;
	watch->stop();
	face_btn.setBackground(IMG_FACE[3]);

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
		{
			if (cells_status[r][c] == FLAGGED)
			{
				if (cells_uncovered_value[r][c] != BOMB)
					cells_image[r][c].setBackground(IMG_UNCOVERED_INCORRECT_FLAGGED, true);
			}
			else if (cells_status[r][c] == COVERED)
			{
				if (cells_uncovered_value[r][c] == BOMB)
					cells_image[r][c].setBackground(IMG_COVERED_MINE, true);
			}
		}
	SDL_RenderPresent(parent->renderer);
}

void MinesweeperGUI::gameWon()
{
	is_game_won = true;
	watch->stop();
	face_btn.setBackground(IMG_FACE[4]);

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
		{
			if (cells_status[r][c] == COVERED && cells_uncovered_value[r][c] == BOMB)
				cells_image[r][c].setBackground(IMG_COVERED_FLAGGED, true);
		}

	remaining_flags->setText("0");
	remaining_flags->show();

	SDL_RenderPresent(parent->renderer);

	if (level == "easy" || level == "medium" || level == "hard")
	{
		this->showHighScore();
	}
}

bool MinesweeperGUI::isGameQuit()
{
	return is_game_quit;
}

void MinesweeperGUI::askToQuit()
{
	watch->pause();

	const SDL_MessageBoxButtonData buttons[] =
	{
		/*
		FORMAT: .flags, .buttonid, .text
		// NOTE: the value of SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT
		// and SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT is both wrong!
		*/
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "No" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Yes" },
	};
	/*
	FORMAT: .colors (.r, .g, .b)
	// NOTE: Windows can't show color!
	*/
	const SDL_MessageBoxColorScheme colorScheme =
	{
		{ 
			{ 255,   0,   0 }, // [SDL_MESSAGEBOX_COLOR_BACKGROUND]
			{ 0,   255,   0 }, // [SDL_MESSAGEBOX_COLOR_TEXT]
			{ 255, 255,   0 }, // [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]
			{ 0,     0, 255 }, // [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]
			{ 255,   0, 255 }  // [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]
		}
	};

	// FORMAT: .flags, .window, .title, message, .numbuttons, .buttons, .colorScheme
	const SDL_MessageBoxData messageBoxData =
	{
		SDL_MESSAGEBOX_WARNING,
		parent->root,
		"Quit the game",
		"Are you sure you want to quit the game?",
		SDL_arraysize(buttons),
		buttons,
		&colorScheme
	};

	int buttonid;
	SDL_ShowMessageBox(&messageBoxData, &buttonid);

	if (buttonid == 1)
	{
		is_game_quit = true;
		// std::cout << "Request to quit...\n";
	}
	else
	{ // nothing happen
		watch->unpause();
	}
}

void MinesweeperGUI::updateHighScore()
{
	if (level == "easy" || level == "medium" || level == "hard")
	{
		std::ifstream highscore_easy_input("highscore_easy.txt");
		if (!highscore_easy_input.fail())
		{
			highscore_easy_input >> highscore_easy;
			highscore_easy_input.close();
		}
		
		std::ifstream highscore_medium_input("highscore_medium.txt");
		if (!highscore_medium_input.fail())
		{
			highscore_medium_input >> highscore_medium;
			highscore_medium_input.close();
		}
		
		std::ifstream highscore_hard_input("highscore_hard.txt");
		if (!highscore_hard_input.fail())
		{
			highscore_hard_input >> highscore_hard;
			highscore_hard_input.close();
		}
		
		std::string played_score = watch->getTime();
		if (played_score.size() == 5) 
		{ // mm:ss
			if (level == "easy")
			{
				std::ofstream highscore_output("highscore_" + level + ".txt");
				highscore_easy = min(highscore_easy, played_score);
				highscore_output << highscore_easy << "\n";
				highscore_output.close();
			}
			if (level == "medium")
			{
				std::ofstream highscore_output("highscore_" + level + ".txt");
				highscore_medium = min(highscore_medium, played_score);
				highscore_output << highscore_medium << "\n";
				highscore_output.close();
			}
			if (level == "hard")
			{
				std::ofstream highscore_output("highscore_" + level + ".txt");
				highscore_hard = min(highscore_hard, played_score);
				highscore_output << highscore_hard << "\n";
				highscore_output.close();
			}
		}
	}
}

void MinesweeperGUI::showHighScore()
{
	this->updateHighScore();

	const SDL_MessageBoxButtonData buttons[] =
	{
		/*
		FORMAT: .flags, .buttonid, .text
		// NOTE: the value of SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT
		// and SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT is both wrong!
		*/
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" },
	};
	/*
	FORMAT: .colors (.r, .g, .b)
	// NOTE: Windows can't show color!
	*/
	const SDL_MessageBoxColorScheme colorScheme =
	{
		{ 
			{ 255,   0,   0 }, // [SDL_MESSAGEBOX_COLOR_BACKGROUND]
			{ 0,   255,   0 }, // [SDL_MESSAGEBOX_COLOR_TEXT]
			{ 255, 255,   0 }, // [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]
			{ 0,     0, 255 }, // [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]
			{ 255,   0, 255 }  // [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]
		}
	};

	std::string output_prompt = "Congratulation! You have won this game!\n\nThe highscore:";
	output_prompt += "\n\tEasy: " + highscore_easy;
	output_prompt += "\n\tMedium: " + highscore_medium;
	output_prompt += "\n\tHard: " + highscore_hard; 

	// FORMAT: .flags, .window, .title, message, .numbuttons, .buttons, .colorScheme
	const SDL_MessageBoxData messageBoxData =
	{
		SDL_MESSAGEBOX_INFORMATION,
		parent->root,
		"You have won!",
		output_prompt.c_str(),
		SDL_arraysize(buttons),
		buttons,
		&colorScheme
	};

	int buttonid;
	SDL_ShowMessageBox(&messageBoxData, &buttonid);
}

void MinesweeperGUI::captureEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
	{
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		bool is_mouse_inside_gamefield = (packed_x <= mouse_x && mouse_x <= packed_x + CELL_WIDTH*width) &&
		                                 (packed_y <= mouse_y && mouse_y <= packed_y + CELL_WIDTH*height);

		SDL_MouseButtonEvent mouse_event = event.button;

		if (home_btn.isXYInside(mouse_x, mouse_y))
		{
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (!is_game_over && !is_game_won)
				{
					// game is being played
					this->askToQuit();
				}
				else
				{
					// game has been stopped
					is_game_quit = true;
				}
			}
		}
		else if (face_btn.isXYInside(mouse_x, mouse_y))
		{
			if (mouse_event.button == SDL_BUTTON_LEFT)
			{
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					face_btn.setBackground(IMG_FACE[1]);
				}
				else if (event.type == SDL_MOUSEBUTTONUP)
				{
					this->newGame();
				}
			}
		}
		else
		{
			if (is_game_over)
			{
				face_btn.setBackground(IMG_FACE[3]);
			}
			else if (is_game_won)
			{
				face_btn.setBackground(IMG_FACE[4]);
			}
			else
			{
				if (is_mouse_inside_gamefield)
				{
					if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						is_in_game = true;

						if (mouse_event.button != SDL_BUTTON_RIGHT)
							face_btn.setBackground(IMG_FACE[2]);
					}
					else if (event.type == SDL_MOUSEBUTTONUP)
					{
						if (!is_in_game)
						{
							// not a click!
							return;
						}

						if (!watch->isStarted() && !watch->isStopped())
						{
							watch->start();
						}

						face_btn.setBackground(IMG_FACE[0]);

						int r = (mouse_y - packed_y) / CELL_WIDTH;
						int c = (mouse_x - packed_x) / CELL_WIDTH;

						if (mouse_event.button == SDL_BUTTON_LEFT)
						{
							if (cells_status[r][c] == COVERED)
								this->openCellsFrom(r, c, false);
							if (count_opened_cells == height * width - bombs)
							{ // win game
								this->gameWon();
							}
						}
						else if (mouse_event.button == SDL_BUTTON_MIDDLE)
						{
							if (cells_status[r][c] == OPENED)
							{
								int count_adjacent_flags = 0;
								for (int adj_r = max(0, r - 1); adj_r <= min(r + 1, height-1); adj_r++)
									for (int adj_c = max(0, c - 1); adj_c <= min(c + 1, width-1); adj_c++)
									{
										if (cells_status[adj_r][adj_c] == FLAGGED)
											count_adjacent_flags++;
									}

								if (cells_uncovered_value[r][c] == count_adjacent_flags)
								{
									this->openCellsFrom(r, c, true);
									if (count_opened_cells == height * width - bombs)
									{ // win game
										this->gameWon();
									}
								}
							}
						}
						else if (mouse_event.button == SDL_BUTTON_RIGHT)
						{
							this->toggleFlag(r, c);
						}
					}
				}
				else
				{
					face_btn.setBackground(IMG_FACE[0]);
				}
			}
		}
	}
}