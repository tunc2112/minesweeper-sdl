#ifndef _CORE_H
#define _CORE_H

class BombField {
public:
	BombField(string level="beginner");
	BombField(int _w, int _h, int _bombs);
	~BombField();
	void generate();
	void updateStatus(int x, int y);

private:
	int width;
	int height;
	int bombs;
};

#endif