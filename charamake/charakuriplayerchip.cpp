#include<DxLib.h>
#include"charakuriplayerchip.h"
#include"colors.h"

charakuriplayerchip::charakuriplayerchip() {
	img = -1;
	x = 0;
	y = 0;
	count = 0;
	handlex = 1;
	handley = 0;
	tcount = 0;
	trunflug = false;
}
charakuriplayerchip::~charakuriplayerchip() {
	DeleteGraph(img);
}
void charakuriplayerchip::_0_1_2_1_0_(int& x) {
	counter();
	x = count / 13 % 4;
	if (x == 3)
		x = 1;

}
int charakuriplayerchip::charakurimoveX2(double speed) {
	return x = speed;
}
int charakuriplayerchip::charakurimoveY2(double speed) {
	return y = speed;
}
void charakuriplayerchip::charakuricharaAnime() {
	if ((CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP)) || (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_W)) ||
		(CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN)) || (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_S)) ||
		(CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP)) || (CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_W)) ||
		(CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN)) || (CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_S))
		) {

		if ((CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP)) ||
			(CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_W))
			) {
			_0_1_2_1_0_(handlex);
			handlex += 3;
			handley = 2;
		}
		else if ((CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN)) ||
			(CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_S))
			) {
			_0_1_2_1_0_(handlex);
			handlex += 3;
			handley = 0;
		}
		else if ((CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP)) ||
			(CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_W))
			) {
			_0_1_2_1_0_(handlex);
			handlex += 3;
			handley = 3;
		}
		else if ((CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN)) ||
			(CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_S))
			) {
			_0_1_2_1_0_(handlex);
			handlex += 3;
			handley = 1;
		}
	}
	else {
		if (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_W)) {

			_0_1_2_1_0_(handlex);
			handley = 3;
		}
		if (CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_S)) {
			_0_1_2_1_0_(handlex);
			handley = 0;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_A)) {
			_0_1_2_1_0_(handlex);
			handley = 1;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || CheckHitKey(KEY_INPUT_D)) {
			_0_1_2_1_0_(handlex);
			handley = 2;
		}
	}
}
void charakuriplayerchip::charakuricharaTrun() {

	if (CheckHitKey(KEY_INPUT_T) && trunflug == false) {
		handlex = 1;
		handley = 0;
		tcount = 0;
		trunflug = true;
	}

	if (tcount >= 66 && CheckHitKey(KEY_INPUT_T) == 0) {
		trunflug = false;
		tcount = 0;
		handlex = 1;
		handley = 0;
	}
	if (tcount >= 66) {
		tcount = 0;
	}

	if (trunflug == true) {
		tcount++;
		if (tcount >= 1 && tcount <= 5) {
			handlex = 1;
			handley = 0;

		}
		else if (handlex == 1 && handley == 0 && tcount >= 2) {
			handlex = 0;
			handley = 0;

		}
		else if (handlex == 0 && handley == 0 && tcount >= 10) {
			handlex = 0;
			handley = 1;

		}
		else if (handlex == 0 && handley == 1 && tcount >= 18) {
			handlex = 3;
			handley = 2;

		}
		else if (handlex == 3 && handley == 2 && tcount >= 26) {
			handlex = 2;
			handley = 3;

		}
		else if (handlex == 2 && handley == 3 && tcount >= 34) {
			handlex = 0;
			handley = 3;

		}
		else if (handlex == 0 && handley == 3 && tcount >= 42) {
			handlex = 5;
			handley = 3;

		}
		else if (handlex == 5 && handley == 3 && tcount >= 50) {
			handlex = 2;
			handley = 2;
		}
		else if (handlex == 2 && handley == 2 && tcount >= 58) {
			handlex = 5;
			handley = 1;

		}

	}

}
void charakuriplayerchip::charakuricharaDraw() {

	//DrawRectGraph(x, y, 32 * handlex, 64 * handley, 32, 64, img, true, false);
	DrawRectExtendGraph(x - 64, y - 64 * 2, x + 64, y + 64 * 2, 32 * handlex, 64 * handley, 32, 64, img, true);

}
