#include <DxLib.h>
#include"squarecollition.h"
#include"colors.h"

namespace {
	enum colors {
		Red,
		Green,
		Blue,
		MaxColor
	};

	int mousex = 0;
	int mousey = 0;

	double x[MaxColor] = {};
	int y[MaxColor] = {};
	double num[MaxColor] = {};
	bool flug[MaxColor];
	int colorvalue[MaxColor] = {};
}
void colorsInit() {


	for (int i = 0; i < 3; i++) {
		x[i] = 50;
		y[i] = 400 + i * 30;
		num[i] = 100;
		flug[i] = false;

		x[i] = 86;

		colorvalue[i] = 255 * num[i] / 100;
	}

}
void colorsUpdate() {
	GetMousePoint(&mousex, &mousey);
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		for (int i = 0; i < 3; i++) {


			if (SquareCollition(mousex, mousey, mousex + 1, mousey + 1, x[i], y[i], x[i] + 30, y[i] + 15)) {
				switch (i)
				{
				case Red:
					if (flug[Green] == false && flug[Blue] == false) {
						flug[Red] = true;
					}
					break;
				case Green:
					if (flug[Red] == false && flug[Blue] == false) {
						flug[Green] = true;
					}
					break;
				case Blue:
					if (flug[Green] == false && flug[Red] == false) {
						flug[Blue] = true;
					}
					break;
				default:
					break;
				}
				//			flug[i] = true;
			}



			if (flug[i] == true) {
				x[i] = mousex - 7;
				//y[i] = mousey;
			}
			if (x[i] + 30 > 100) {
				x[i] = 100 - 7 * 2;
			}
			else
				if (x[i] <= 0) {
					x[i] = 0;
				}
			/*
			if (y[i] != 250) {
				y[i] = 250+i*120;
			}
			*/
			num[i] = ((double)x[i] / 86) * 100;
		}


	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		for (int i = 0; i < 3; i++) {
			flug[i] = false;
		}

	}

}
void colorsDraw() {
	for (int i = 0; i < 3; i++) {
		unsigned int color[3] = {};
		switch (i)
		{
		case Red:
			color[Red] = 255;
			break;
		case Green:
			color[Green] = 200;
			break;
		case Blue:
			color[Blue] = 200;
			break;
		default:
			color[i] = 100;
			break;
		}
		DrawBox(x[i], y[i], x[i] + 30, y[i] + 15, GetColor(color[Red], color[Green], color[Blue]), true);
		DrawBox(x[i], y[i], x[i] + 30, y[i] + 15, GetColor(150, 150, 150), false);


		colorvalue[i] = 255 * num[i] / 100;
	}
}
int getcolorvaluesR() {
	int R = (255 * num[Red]) / 100;
	return R;
}
int getcolorvaluesG() {
	int G = (255 * num[Green]) / 100;
	
	return G;
}
int getcolorvaluesB() {
	int B = (255 * num[Blue]) / 100;
	return B;
}