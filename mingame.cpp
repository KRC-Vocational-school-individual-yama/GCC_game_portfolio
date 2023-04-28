#include<DxLib.h>
#include<string>
#include"mingame.h"
#include"avoidance.h"
#include"counter_game.h"

//void Avoidance_Start();
//void Avoidance_Update();
//void Avoidance_Draw();
void Mingame_Choice();
void Mingame_Draw();

namespace {
	int gameselect = 0;
	

	std::string selecttext[3] = {};
	int selectno=0;
	int selectcolor = 0;
	bool keystop = false;

}
void Mingame_Choice() {
	selecttext[0] = "gameをselectしてね";
	selecttext[1] = "\n\n\n・avoidance";
	selecttext[2] = "\n\n\n・counter";

	if (CheckHitKey(KEY_INPUT_UP) && keystop == false) {
		if (selectno > 0)
			selectno--;
		keystop = true;
	}
	else
		if (CheckHitKey(KEY_INPUT_DOWN) && keystop == false) {
			if (selectno < 1)
				selectno++;
			keystop = true;
		}

	if (CheckHitKey(KEY_INPUT_RIGHT)&& keystop == false) {
		gameselect++;
		keystop = true;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		selectno = 0;
		//gameselect = 0;
	}
	
	if (CheckHitKey(KEY_INPUT_DOWN) == 0 &&
		CheckHitKey(KEY_INPUT_UP) == 0&&
		CheckHitKey(KEY_INPUT_RIGHT) == 0
		) {
		keystop = false;
	}

	
}
void Mingame_ChoiceEnd() {
	for (int i = 0; i < 3; ++i)
		selecttext[i] = "";
	switch (selectno){
	case 0:
		gameselect = 2;
		break;
	case 1:
		gameselect = 3;
		break;
	}
}
void Mingame_draw() {
	SetFontSize(32);
	DrawFormatString(230, 50, GetColor(255, 255, 255), selecttext[0].c_str());
	SetFontSize(NULL);
	DrawFormatString(250,100,GetColor(255,255,255),"右キーで選択\nゲームから戻るときはバックスペースキー");
	for (int i = 1; i < 3; ++i) {
		selectcolor = (selectno + 1 == i) ? 255 : 100;
		DrawFormatString(100, 150 + (i * 64), GetColor(selectcolor, selectcolor, selectcolor), selecttext[i].c_str());
	}
	DrawFormatString(100, 214+(selectno*64), GetColor(255, 255, 255), "\n\n\n         　　⇒");
	SetFontSize(27);
}
void Mingame_Init() {
	Avoidance_Start();
	Counter_Init();
	gameselect = 0;
	selectno = 0;
	selectcolor = 0;

	for (int i = 0; i < 3; ++i)
		selecttext[i] = "";
}
void Mingame_Update() {
	
	switch (gameselect) {
	case 0:
		Mingame_Choice();
		break;
	case 1:
		Mingame_ChoiceEnd();
		break;
	case 2:
		Avoidance_Update();
		break;
	case 3:
		Counter_Update();
		break;
	}
	if (CheckHitKey(KEY_INPUT_BACK))
		gameselect = 0;
}
void Mingame_Draw() {
		switch (gameselect) {
		case 0:
			Mingame_draw();
			break;
		case 1:
			//無し
			break;
		case 2:
			Avoidance_Draw();
			break;
		case 3:
			Counter_Draw();
			break;
		}
}
void Mingame_Relece() {

}