#include"house.h"
#include<DxLib.h>

/*
	hhhhhhhhh
	yyyyyyyyy
	ggggggggg
	seeeeeeer
	seeeeeeer
	seeeeeeer
	xdddodddf
*/ 
housedraw::housedraw() {
	housedrawInit();
}
void housedraw::housedrawInit() {
	for (int i = 0; i < 9; i++)
		chip[0][i] = 'h';
	for (int i = 0; i < 9; i++)
		chip[1][i] = 'y';
	for (int i = 0; i < 9; i++)
		chip[2][i] = 'g';
	for (int i = 0; i < 9; i++)
		for (int j = 3; j < 7; j++)
			chip[j][i] = 'e';
	for (int i = 0; i < 9; i++)
		chip[6][i] = 'd';
	for (int i = 3; i < 6; i++)
		chip[i][0] = 's';
	for (int i = 3; i < 6; i++)
		chip[i][8] = 'r';
	chip[6][0] = 'x';
	chip[6][4] = 'o';
	chip[6][8] = 'f';


	//LoadDivGraph("chip/chip_house.png",7*8,7,8,32,32,img);
}
int housedraw::DrawHouse(int x, int y,int imgs[25 * 7],int doaimgs[18 * 8]) {
	int chipNo = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 9; j++) {
			switch (chip[i][j])
			{
			case 'e':
				chipNo = 7 * 3 + 1;
				break;
			case 'r':
				chipNo = 7 * 3 + 2;
				break;
			case 's':
				chipNo = 7 * 3 + 0;
				break;
			case 'x':
				chipNo = 7 * 4 + 0;
				break;
			case 'd':
				chipNo = 7 * 4 + 1;
				break;
			case 'f':
				chipNo = 7 * 4 + 2;
				break;


			case 'o':
				chipNo = 7 * 22 + 6;
				break;

			default:
				chipNo = 0;
				break;
			}
			DrawGraph(j * 32 + x, i * 32 + y, imgs[chipNo], true);

			switch (chip[i][j])
			{
			case'h':
				chipNo = 8 * 9 + 0;
				break;
			case'y':
				chipNo = 8 * 10 + 0;
				break;
			case'g':
				chipNo = 8 * 11 + 0;
				break;

			default:
				chipNo = 0;
				break;
			}
			DrawGraph(j * 32 + x, i * 32 + y, doaimgs[chipNo], true);

			switch (chip[i][j]) {
			case'o':
				chipNo = 8 * 3 + 6;
				break;
			default:
				chipNo = 0;
				break;
			}
			DrawGraph(j * 32 + x, i * 32 + y, doaimgs[chipNo], true);
			if (chip[i][j] == 'o')
				DrawGraph(j * 32 + x, i * 32 + y, doaimgs[8 * 3 + 7], true);

			if (chip[i + 1][j] == 'o')
				DrawGraph(j * 32 + x, i * 32 + y, doaimgs[8 * 2 + 7], true);

		}
	}

	return 0;
}
int housedraw::DrawHouse_yane(int x ,int y ,int doaimgs[18 * 8]) {
	int chipNo = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 9; j++) {
			switch (chip[i][j]){
			case'h':
				chipNo = 8 * 9 + 0;
				break;
			case'y':
				chipNo = 8 * 10 + 0;
				break;
			case'g':
				chipNo = 8 * 11 + 0;
				break;

			default:
				chipNo = 0;
				break;
			}
			DrawGraph(j * 32 + x, i * 32 + y, doaimgs[chipNo], true);
		}
	}
	return 0;
}
housedraw::~housedraw() {
}