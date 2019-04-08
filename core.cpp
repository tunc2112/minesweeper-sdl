#include "core.h"

BombField::BombField(string level) {
	if (level == "beginner") {
		width = 8;
		height = 8;
		bombs = 10;
	} else if (level == "intermediate") {
		width = 16;
		height = 16;
		bombs = 40;
	} else if (level == "expert") {
		width = 30;
		height = 16;
		bombs = 99;
	}
}

BombField::BombField(int _w, int _h, int _bombs) {
	width = _w;
	height = _h;
	bombs = _bombs;
}

BombField::~BombField() {}

void generate() {}

void BombField::updateStatus(int x, int y) {

}