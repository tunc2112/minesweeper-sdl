#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cmath>
#define row first
#define col second
using namespace std;
const int TILES_NUM = 4, PIECES_NUM = 10, ROWS_DISPLAYED = 28;
int delay, updates_num, lowscore = -1U/2, high_filled_num;
#define _ ),make_pair(
pair<int, int> piece[PIECES_NUM + 1][TILES_NUM] = { make_pair(0,0 _ 0,0 _ 0,0 _ 0,0

  // o
_ 1,-1 _ 1, 0
					// -
_ 0,-1 _ 0, 0       _ 0,-2 _ 0,-1 _ 0, 0 _ 0, 1


		 // |
	   _ 3, 0

	   _ 2, 0

	   _ 1, 0
							 // ~
	   _ 0, 0              _ 1,-1 _ 1, 0

								  _ 0, 0 _ 0, 1

		 // /
	   _ 2, 0

_ 1,-1 _ 1, 0
									// s
_ 0,-1                            _ 1, 0 _ 1, 1

						   _ 0,-1 _ 0, 0

  // 4
_ 2,-1

_ 1,-1 _ 1, 0
							 // L
	   _ 0, 0              _ 1,-1

						   _ 0,-1 _ 0, 0 _ 0, 1

  // 7
_ 2,-1 _ 2, 0

	   _ 1, 0
							 // +
	   _ 0, 0              _ 2,-1

						   _ 1,-1 _ 1, 0

						   _ 0,-1
) };
#undef _
char     tile[PIECES_NUM + 1] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ','\xB1','\xB1'};
int tet_color[PIECES_NUM + 1] = {0x80,0xE0,0xB0,0xB0,0xC0,0xC0,0xA0,0xA0,0x90,0xCE,0x5D};
vector< vector<int> > board;
vector<bool> filled;
pair<int,int> cur_pos;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
int cur_tet, next_tet, filled_num;

inline int& cell(int i, int offset_r=0, int offset_c=0) {
	return board [ cur_pos.row + piece[cur_tet][i].row + offset_r ]
			     [ cur_pos.col + piece[cur_tet][i].col + offset_c ] ;
}
int width = 10, score;

void shift(int up, int right) {
	for(int i=0; i<TILES_NUM; ++i)
		cell(i) = 0;
	for(int i=0; i<TILES_NUM; ++i)
		cell(i,up,right) = cur_tet;
	cur_pos.row += up;
	cur_pos.col += right;
	return;
}

void place_cursor(short y, short x) {
    SetConsoleCursorPosition( handle, COORD{x, y} );
    return;
}

void set_color(int c) {
    SetConsoleTextAttribute(handle, c);
    return;
}

void modify(char tile, int color) {
	for(int i=0; i<TILES_NUM; ++i) {
		if(cur_pos.row + piece[cur_tet][i].row + 4 <= board.size() &&
		   cur_pos.row + piece[cur_tet][i].row + ROWS_DISPLAYED > board.size() - TILES_NUM) {
			set_color(color);
			place_cursor(board.size() - (cur_pos.row + piece[cur_tet][i].row) - 4 ,
					(cur_pos.col + piece[cur_tet][i].col)*2 + 1);
			cout << tile << tile;
		}
	}
	return;
}

pair<int,int> ghost_pos, real_pos;

void draw_ghost() {
	real_pos = cur_pos;
	while(cur_pos.row > 0) {
		for(int i=0; i<TILES_NUM; ++i)
			if( cell(i,-1,0) < 0 )
				goto Line121;
		shift(-1,0);
	}
	Line121:
	for(int i=0; i<TILES_NUM; ++i)
		cell(i) = 0;
	modify('\xB0', 0x87);
	ghost_pos = cur_pos;
	cur_pos = real_pos;
	for(int i=0; i<TILES_NUM; ++i)
		cell(i) = cur_tet;
	return;
}

void rub_ghost() {
	real_pos = cur_pos;
	cur_pos = ghost_pos;
	modify(' ', tet_color[0]);
	cur_pos = real_pos;
	return;
}

void rub() {
	modify(' ', tet_color[0]);
	rub_ghost();
	return;
}

void draw() {
	draw_ghost();
	modify(tile[cur_tet], tet_color[cur_tet]);
	return;
}

void display() {
    place_cursor(0,0);
	for(int i=board.size()-4; i>=max(0,(int)board.size()-(ROWS_DISPLAYED+TILES_NUM-1)); --i) {
		set_color(0x00);
		cout << '\xDB';
		for(int j=0; j<width; ++j) {
			set_color(tet_color[abs(board[i][j])]);
			cout << tile[abs(board[i][j])] << tile[abs(board[i][j])];
		}
		set_color(filled[i] ? 0x72 : 0x70);
		cout << '\xDB' << '\n';
	}
	set_color(0x70);
	if(board.size() < ROWS_DISPLAYED+TILES_NUM-1)
		for(int i=0; i<(width+1)*2; ++i)
			cout << '\xDF';
	draw_ghost();
	return;
}

int k;

void update() {
	for(int i=0; i<TILES_NUM; ++i) {
		for(int j=0; j<TILES_NUM*2; ++j) {
			place_cursor(i+1, j+2*width+4);
			set_color(0x70);
			cout << ' ';
		}
	}
	place_cursor(8, width*2 + 7);
	cout << score << "    ";
	place_cursor(11, width*2 + 7);
	cout << filled_num << "    ";
	place_cursor(14, width*2 + 7);
	cout << width*8 - k - 1 << ' ';
	if(k < width*8-1) {
		for(int i=0; i<TILES_NUM; ++i) {
			place_cursor( 4 - piece[next_tet][i].row,
						  (width + piece[next_tet][i].col)*2 + 8);
			set_color(tet_color[next_tet]);
			cout << tile[next_tet] << tile[next_tet];
		}
	}
	return;
}

int main() {
    system("COLOR 7F");
	srand(time(0));
	SetConsoleTitle("XEPHINHTHOI");
	rand();
    _CONSOLE_CURSOR_INFO csrInfo = {25, false};
    SetConsoleCursorInfo(handle, &csrInfo);
	for(;;) {
		set_color(0x7F);
		place_cursor(7, width*2 + 2);
		cout << "__  score";
		place_cursor(10, width*2 + 6);
		cout << "filled";
		place_cursor(13, width*2 + 6);
		cout << "left";
		place_cursor(0, width*2 + 6);
		cout << "next";
		next_tet = rand()%PIECES_NUM + 1;
		delay = 512;
		for(k=0; k<width*8; ++k) {
			delay -= 55./width+.5;
			updates_num = delay/32.+.5;
			board.resize(score + 11, vector<int>(width));
			filled.resize(score + 11, false);
			cur_tet = next_tet;
			next_tet = rand()%PIECES_NUM + 1;
			cur_pos = make_pair(score+7, width/2);
			for(int i=0; i<TILES_NUM; ++i)
				cell(i) = cur_tet;
			update();
			display();
			bool blocked;
			for(;;) {
				blocked = false;
				for(int i=0; i<updates_num; ++i) {
					char input;
					if(kbhit() && !blocked) {
						if( (input=getch()) == '\xE0' )
							input = (input=getch()) == '\x48' ? 'w' :
									 input          == '\x4B' ? 'a' :
									 input          == '\x50' ? 's' :
									 input          == '\x4D' ? 'd' :
															  input ;
						switch(input) {
							case 'a':
								for(int i=0; i<TILES_NUM; ++i)
									if(	cur_pos.col + piece[cur_tet][i].col == 0 ||
																 cell(i,0,-1) < 0 )
										goto Line310;
								rub();
								shift(0,-1);
								draw();
								break;
							case 'd':
								for(int i=0; i<TILES_NUM; ++i)
									if( cur_pos.col + piece[cur_tet][i].col == width-1 ||
																		cell(i,0,1) < 0 )
										goto Line310;
								rub();
								shift(0,1);
								draw();
								break;
							case 's':
#define FALL(label,x,y)			if(cur_pos.row > 0) {				\
									for(int i=0; i<TILES_NUM; ++i)	\
										if( cell(i,-1,0) < 0 ) {	\
											x;						\
											goto label;				\
										}							\
									rub();							\
									shift(-1,0);					\
									draw();							\
									y;								\
								}
								FALL(Line310, blocked = true,)
								else
									blocked = true;
								break;
							case 'w':
							case ' ':
								blocked = true;
								rub();
								while(cur_pos.row > 0) {
									for(int i=0; i<TILES_NUM; ++i)
										if( cell(i,-1,0) < 0 )
											goto Line287;
									shift(-1,0);
								}
								Line287:
								draw();
								break;
							case 'r':
								goto Restart;
							case '\e':
							case 'q':
								return 0;
							case 'c':
								set_color(0x70);
								place_cursor(0, width*2+2);
								char c = getch();
								if(c>='1' && c<='9') {
									if(c >= '4')
										width = c-'0';
									else {
										cout << c;
										width = (c-'0')*10 + getch() - '0';
									}
									goto Restart;
								}
						}
					}
					Line310:
					Sleep(delay/updates_num);
				}
				if(!blocked) {
					blocked = true;
					FALL(Line318,, blocked = false);
				}
#undef FALL
				Line318:
				if(blocked) {
					for(int i=cur_pos.row; i < cur_pos.row + TILES_NUM; ++i)
						if(!filled[i]) {
							filled[i] = true;
							for(int j=0; j<width; ++j)
								if(board[i][j] == 0) {
									filled[i] = false;
									break;
								}
							filled_num += filled[i];
						}
					for(int i=0; i<TILES_NUM; ++i)
						cell(i) = -cell(i);
					break;
				}
			}
			while( board[score] != vector<int>(width) )
				++score;
		}
		--k;
		board.resize(score + 11, vector<int>(width));
		update();
		display();
		draw();
		for(char choice;;) {
			switch(choice=getch()) {
				case 'r':
				case ' ':
				break;
				case '\e':
				case 'q':
				case '\x03':
					return 0;
				default:
					continue;
			}
			break;
		}
		set_color(0x70);
		if(score < lowscore)
			lowscore = score;
		place_cursor(8, width*2 + 15);
		cout << lowscore;
		if(filled_num > high_filled_num)
			high_filled_num = filled_num;
		place_cursor(11, width*2 + 15);
		cout << high_filled_num;
		set_color(0x7F);
		place_cursor(7, width*2 + 14);
		cout << "worst";
		place_cursor(10, width*2 + 14);
		cout << "best";
		Restart:
		board.clear();
		filled.clear();
		score = filled_num = 0;
		place_cursor(0,0);
		set_color(0x70);
		for(int i=0; i<ROWS_DISPLAYED+4; ++i) {
			for(int j=0; j < (k<width-1?79:width*2+2); ++j)
				cout << ' ';
			cout << '\n';
		}
	}
}
