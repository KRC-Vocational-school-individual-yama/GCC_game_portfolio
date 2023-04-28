#pragma once

class housedraw {
	
public:
	housedraw();
	void housedrawInit();
	int DrawHouse(int x, int y, int imgs[25 * 7], int doaimgs[18 * 8]);
	int DrawHouse_yane(int x,int y, int doaimgs[18 * 8]);
	~housedraw();

private:
	char chip[7][9] = {};
	//int img[25 * 7] = { -1 };
	//int doaimg[8*18] = { -1 };

};