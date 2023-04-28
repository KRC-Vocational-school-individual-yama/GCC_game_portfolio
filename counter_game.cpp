#include "DxLib.h"
#include<string>
#include"counter_game.h"

namespace {
	bool keyStop = false;
	int count_ter= 0;
	bool mingameflug = false;
	float mingcount = 0;
	std::string mingcountdisp = "";
}

void Counter_Init() {
	keyStop = 0;//0は止めない、1は止める
	count_ter= 0;
}

void Counter_Update() {
	if (CheckHitKey(KEY_INPUT_RETURN) && keyStop == false) {
		count_ter++;
		mingameflug = true;
		keyStop = true;
		mingcount = 0;
	}
	if (count_ter% 2 == 1)
		mingameflug = true;

	else if (count_ter% 2 == 0)
		mingameflug = false;

	if (mingameflug == true) {
		mingcount++;
		int tmp = mingcount / 60;
		float syou = mingcount / 60 - tmp;
		int stmp = syou * 100;
		mingcountdisp = std::to_string(tmp) + "." + std::to_string(stmp);
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD2))
		DrawFormatString(20, 550, GetColor(100, 100, 100), mingcountdisp.c_str());

	if (CheckHitKey(KEY_INPUT_RETURN) == 0)
		keyStop = false;
}

void Counter_Draw() {
	if (mingameflug == false) {
		SetFontSize(32);
		DrawFormatString(150, 100, GetColor(255, 255, 255), "三秒　数えるゲーム\n");
		SetFontSize(16);
		DrawFormatString(150, 100, GetColor(255, 255, 255), "\n\nエンターを押したらゲーム開始");
		SetFontSize(70);
		DrawFormatString(380, 300, GetColor(255, 255, 255), mingcountdisp.c_str());
		SetFontSize(16);
	}
	if (mingameflug == true)
		DrawFormatString(350, 300, GetColor(255, 255, 255), "3秒だと思ったらエンターキー");

}

void Counter_Delete() {
	/*DeleteGraph();*/
}
