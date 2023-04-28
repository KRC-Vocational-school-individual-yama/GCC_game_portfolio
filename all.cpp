#include "DxLib.h"
#include<string>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"winmain.h"
#include"mingame.h"
#include"charamake/charamake.h"
#include"mapchip_soce/mapchip.h"





namespace {
	int hokanmode;
	int mode;
	enum mode {
		title,
		choice,
		choiceend,
		field,
		mingame,
		option,
		OneStop,
		OneStopend,

		modeEnd
	};
	bool keyStop = false;
	bool ENDFLUG = false;
	int count;
	bool countstop;
	const int textmax = 5;
	std::string selectText[textmax] = {};
	int selectNoX = 0;
	int selectNoY = 0;
	int selectcolor = 0;

	bool mingameflug = false;
	float mingcount = 0;
	std::string mingcountdisp = "";

	bool maingameflag = false;
}

void HitkeyRetrun(int& plus) {
	if (CheckHitKey(KEY_INPUT_RETURN) == 1 && keyStop == false)
	{
		plus = plus + 1;
		keyStop = true;
	}
	else if (CheckHitKey(KEY_INPUT_RETURN) == 0) {
		keyStop = false;
	}
}


void MysterySquare() {
	if (CheckHitKey(KEY_INPUT_NUMPAD1) && countstop == false) {
		count++;
		countstop = true;
	}
	else if (CheckHitKey(KEY_INPUT_NUMPAD1) == 0) {
	countstop = false;
	}
	if (count % 2 == 1) {
		DrawBox(500, 400, 550, 450, GetColor(0x7f, 0xff, 0xb4), true);
	}
}

void EscContinew() {
	if (hokanmode == choiceend)
		hokanmode = choice;
	mode = hokanmode;

}




void MainInit() {
	Mingame_Init();
	charaseisakubunkiInit();
	mapchipInit();
	hokanmode = 0;
	mode = 0;//0ページ目からストーリーを進める
	keyStop = 0;//0は止めない、1は止める
	count = 0;
	countstop = false;
	maingameflag = false;
}
void Main_reset() {
	mapchipInit();
	charaseisakubunkiInit();
	Mingame_Init();
}
void MainUpdate()
{
	

	MysterySquare();
	if (mode > modeEnd)
		mode = 0;



	if (mode == title) {
		HitkeyRetrun(mode);
		selectNoX = 0;
		selectNoY = 0;
	}
	if (mode == choice) {
		selectText[0] = "ストーリーへ";
		selectText[1] = "待機";
		selectText[2] = "ミニゲーム";
		selectText[3] = "何しよう";
		selectText[4] = "設定";
		mode++;
	}
	if (mode == choiceend) {

		if (CheckHitKey(KEY_INPUT_RETURN) && keyStop == false) {
			/*
			//gameReset
			if (selectNoX != 0&&
				selectNoX!=4) {
				Main_reset();
				maingameflag = false;
			}
			*/
			//選択項目
			switch (selectNoX) {
			case 0:
				mode = field;
				break;
			case 1:
				if (CheckHitKey(KEY_INPUT_RETURN))
					DrawFormatString(250, 100, GetColor(0x7f, 0xff, 0xb4), "うん。");
				break;
			case 2:
				mode = mingame;
				break;
			case 3:
				if (countstop == false) {
					count++;
					countstop = true;
				}
				else if (CheckHitKey(KEY_INPUT_RETURN) == 0) {
					countstop = false;
				}
				if (count % 2 == 1) {
					DrawBox(500, 400, 550, 450, GetColor(0x7f, 0xff, 0xb4), true);
				}
				break;
			case 4:
				mode = option;
				break;
			}
			keyStop = true;
		}

	}
	if (mode == field) {
		/* charamakeでdorawboxを置いた */
		SetBackgroundColor(248, 184, 98);//背景色設定
		if (maingameflag == false) {
			charaseisakubunnkiUpdete();
		}


		
			if (
				charaseisakubonnkiTuginopagehe() == true
				) {
				maingameflag = true;
			}
		


		if (maingameflag == true) {
			SetBackgroundColor(0, 0, 0);//背景色設定
			mapchipDraw();
			mapchipUpdate();
			charaseisakubunnkiGetkakidasiflug();
		}

	}
	if (mode == mingame) {
		Mingame_Update();
	}
	if (mode == OneStop) {
		selectText[0] = "続ける";
		selectText[1] = "選択に行く";
		selectText[2] = "オプション";
		selectText[3] = "タイトルへ";
		selectText[4] = "やめる。";

		mode++;
	}
	if (mode == OneStopend) {

		if (CheckHitKey(KEY_INPUT_RETURN) && keyStop == false) {
			switch (selectNoY) {
			case 0:
				EscContinew();//mode = hokanmode;
				break;
			case 1:
				Main_reset();
				mode = choice;
				break;
			case 2:
				mode = option;
				break;
			case 3:
				Main_reset();
				mode = title;
				break;
			case 4:
				EndFulg_trueorfalse(true);
				break;
			}
			keyStop = true;
		}
	}


	if (CheckHitKey(KEY_INPUT_UP) && keyStop == false) {
		if (mode == OneStopend && selectNoY > 0)selectNoY--;
		keyStop = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) && keyStop == false) {
		if (mode == OneStopend && selectNoY < 4)selectNoY++;
		keyStop = true;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && keyStop == false) {
		if (mode == choiceend && selectNoX > 0)selectNoX--;
		keyStop = true;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) && keyStop == false) {
		if (mode == choiceend && selectNoX < 4)selectNoX++;
		keyStop = true;
	}
	if (CheckHitKey(KEY_INPUT_UP) == 0 &&
		CheckHitKey(KEY_INPUT_DOWN) == 0 &&
		CheckHitKey(KEY_INPUT_LEFT) == 0 &&
		CheckHitKey(KEY_INPUT_RIGHT) == 0 &&
		CheckHitKey(KEY_INPUT_RETURN) == 0&&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0
		) keyStop = false;

	//一時停止画面のつもり
	if (CheckHitKey(KEY_INPUT_ESCAPE)&&keyStop==false&&
		mode!=OneStopend&&
		mode!=title
		) {
		selectNoY = 0;
		selectNoX = 0;
		hokanmode = mode;
		mode = OneStop;
		keyStop = true;
	}
}

void MainDraw() {
	//page確認用の数字
	for (int i = 0; i < 16; ++i) {
		if (mode == i) {
			DrawFormatString(200, 10 + (i * 10), GetColor(255, 255, 255), "%d", i);
		}
	}
	
	SetFontSize(64);
	if (mode == title)DrawFormatString(200, 250, GetColor(20, 250, 60), "Title");
	SetFontSize(16);
	if (mode == choiceend) {
		for (int i = 0; i < textmax; ++i) {
			if (selectNoX == i) {
				selectcolor = 255;
			}
			else {
				selectcolor = 100;
			}
			DrawFormatString(50 + (i * 150), 300, GetColor(selectcolor, selectcolor, selectcolor), selectText[i].c_str());
		}
		//DrawFormatString(30 + (selectNoX * 150), 300, GetColor(255, 255, 255), "⇒");
	}
	if (mode == mingame) {
		Mingame_Draw();
	}
	if (mode == OneStopend) {
		for (int i = 0; i < textmax; ++i) {
			if (selectNoY == i) {
				selectcolor = 255;
			}
			else {
				selectcolor = 100;
			}
			(selectNoY == 4) ?
				DrawFormatString(250, 200 + (i * 40), GetColor(selectcolor, selectcolor, 100), selectText[i].c_str())
				:
				DrawFormatString(250, 200 + (i * 40), GetColor(selectcolor, selectcolor, selectcolor), selectText[i].c_str());
		}
		//DrawFormatString(230, 200 + (selectNoY * 40), GetColor(255, 255, 255), "⇒");
	}


}


void MainDelete() {
	/*DeleteGraph();*/
	charaseisakubunnkiDelete();
	mapchipDelete();
}
