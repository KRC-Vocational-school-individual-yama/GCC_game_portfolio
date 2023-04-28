#include "DxLib.h"
//プロトタイプ宣言
void Avoidance_Start();
void Avoidance_Update();
void Avoidance_Draw();
void seigen();
void Checkhitkey();
void ReturnKey();
void Collition();
void MaxScore();
void AtariSquaer();
void debug();
void Update_title();
void Draw_title();
void Update_clearhantei();
void Update_tyuupet();
void Draw_tyuupet();
void Update_setumei();
void Draw_setumei();
void Update_action();
void Draw_action();
void Update_clear();
void Draw_clear();
void Update_end();
void Draw_end();
//変数宣言
namespace {
	bool skip = false;
	int       score=0;
	int    maxscore=0;
	int zenkaiscore=0;
	int   gamecount=0;

	int  diff=0;
	int diffm=0;
	const int boxmax = 35;
	int randpos[boxmax] = {};
	int boxugo[boxmax] = {};
	int randposm[boxmax] = {};
	int boxugom[boxmax] = {};

	float         idouy=0.f;
	float         idoux=0.f;
	float          ugox=0.f;
	float          ugoy=0.f;
	float setumeidassyu=0.f;
	float setumeisinobi=0.f;
	float   setumeiugod=0.f;
	float   setumeiugos=0.f;

	int     white=0;
	int whitedark=0;
	int       ash=0;
	int      dark=0;
	int     black=0;

	int mozicount=0;
	int page=0;
	int time_avo=0;
	bool keystop = false;
	bool kesi = false;
	bool countstop=false;
	//ページの番号
	enum Page {
		
		title,
		clearhantei,
		tyuupet,
		syokika,
		setumei,
		action,
		clear,
		end,
	};
	//円構造体
	struct circle {
		int x=0;
		int y=0;
		int r=0;
	};
	circle PlayerBall;
	//四角構造体
	struct square {
		int left=0;
		int right=0;
		int top=0;
		int bottom=0;
		bool active=0;
	};
	square EnemyBlock[boxmax];
	square setumeibox[2];
}
//-処理系-
bool SCC(circle ball,square block){
	//SquareCircleCollision(四角の当たり判定)
	bool bleft=false;
	bool bright=false;
	bool btop=false;
	bool bbottom=false;
	if (ball.x + ball.r >= block.left)
		bleft = true;
	if (ball.x - ball.r <= block.right)
		bright = true;
	if (ball.y + ball.r >= block.top)
		btop = true;
	if (ball.y - ball.r <= block.bottom)
		bbottom = true;
	if ((bleft && bright && btop && bbottom) == true)
		return true;
	return false;
}
void seigen() {
	if (PlayerBall.x-20 < 0) {
		ugox = 0;
		if ((CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT)) == 1) {
			ugox = 1;
		}
	}
	if (PlayerBall.x+20 > 800) {
		ugox = 0;
		if ((CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT)) == 1) {
			ugox = 1;
		}
	}
	if (PlayerBall.y-20 < 0) {
		ugoy = 0;
		if ((CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN)) == 1) {
			ugoy = 1;
		}
	}
	if (PlayerBall.y+20 > 600) {
		ugoy = 0;
		if ((CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP)) == 1) {
			ugoy = 1;
		}
	}
}
void Checkhitkey() {

	if ((CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP)) == 1) {
		idouy -= ugoy;
		setumeidassyu -= setumeiugod;
		setumeisinobi -= setumeiugos;
	}
	if ((CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT)) == 1) {
		idoux -= ugox;
	}
	if ((CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN)) == 1) {
		idouy += ugoy;
		setumeidassyu += setumeiugod;
		setumeisinobi += setumeiugos;
	}
	if ((CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT)) == 1) {
		idoux += ugox;
	}
	if (CheckHitKey(KEY_INPUT_LSHIFT) == 1 || CheckHitKey(KEY_INPUT_LCONTROL) == 1) {
		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
			ugox = 2;
			ugoy = 2;
		}
		else if (CheckHitKey(KEY_INPUT_LCONTROL) == 1) {
			ugox = 0.5;
			ugoy = 0.5;
		}
	}
	else {
		ugox = 1;
		ugoy = 1;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD1) == 1) {
		ugox = 1;
		ugoy = 1;
	}
}
void ReturnKey()  {
	if (CheckHitKey(KEY_INPUT_RETURN) == 1 && keystop == false) {
		keystop = true;
		if (page == clear) {
			page = title;
		}else page++;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) == 0) {
		keystop = false;
	}
	if (page > end) {
		page = title;
	}
	
	
}
void Collition()  {
	zenkaiscore = 0;
	if (CheckHitKey(KEY_INPUT_C) == 1) {

	}
	else {
		page = end;
		diff = 0;
		diffm = 0;
		
	}
	
}
void MaxScore()  {

	if (score/60 > maxscore) {
		maxscore = score/60;
	}

	DrawFormatString(630,20,GetColor(255,0,255),"最高SCORE：%d\n",maxscore);
	DrawFormatString(630,40,GetColor(255,255,255),"前回SCORE：%d\n",zenkaiscore);
}
void AtariSquaer() {
	DrawBox(PlayerBall.x - PlayerBall.r, PlayerBall.y- PlayerBall.r, PlayerBall.x+ PlayerBall.r,PlayerBall.y+ PlayerBall.r,white,false);
	DrawBox(PlayerBall.x , PlayerBall.y - PlayerBall.r, PlayerBall.x , PlayerBall.y + PlayerBall.r, white, false);
	DrawBox(PlayerBall.x - PlayerBall.r, PlayerBall.y , PlayerBall.x + PlayerBall.r, PlayerBall.y , white, false);
}
void debug() {
	if (CheckHitKey(KEY_INPUT_M) == 1) {
		score = 30*60;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD0) == 1) {
		score = 35 * 60;
		diff = 10;
		diffm = 5;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1) {
		Collition();
	}
}
//Update
void Update_title() {
	score = 0;
	idoux = 0, idouy = 0;
	mozicount = 0;
	countstop = false;
	if (time_avo <= 504)
		if (time_avo <= 80)
			time_avo++;
		else
			time_avo += 8;
	if (time_avo >= 500)
		ReturnKey();
	if (time_avo >= 600)
		score = 100;
	whitedark = GetColor(time_avo / 2, time_avo / 2, time_avo / 2);
	if (skip == true)
		ReturnKey();
}
void Update_clearhantei() {
	setumeidassyu = 0;
	setumeisinobi = 0;
	if (skip == true)
		page = action;
	else
		page++;
}
void Update_tyuupet() {
	if (CheckHitKey(KEY_INPUT_W) == 1 ||
		CheckHitKey(KEY_INPUT_A) == 1 ||
		CheckHitKey(KEY_INPUT_S) == 1 ||
		CheckHitKey(KEY_INPUT_D) == 1 ||
		CheckHitKey(KEY_INPUT_UP) == 1 ||
		CheckHitKey(KEY_INPUT_DOWN) == 1 ||
		CheckHitKey(KEY_INPUT_LEFT) == 1 ||
		CheckHitKey(KEY_INPUT_RIGHT) == 1
		)
		kesi = true;
	if (kesi == true) {
		for (int i = 0; i < 2; i++)
			DrawCircle(PlayerBall.x = 90, PlayerBall.y = 300 + (int)(setumeidassyu * 5), PlayerBall.r = 20, white, false);
		if (PlayerBall.y - PlayerBall.r <= setumeibox[0].top)
			setumeiugod = -setumeiugod;
		if (PlayerBall.y + PlayerBall.r >= setumeibox[0].bottom)
			setumeiugod = -setumeiugod;
		DrawCircle(PlayerBall.x = 690, PlayerBall.y = 300 + (int)(setumeisinobi * 5), PlayerBall.r = 20, white, false);
		if (PlayerBall.y - PlayerBall.r <= setumeibox[1].top)
			setumeiugos = -setumeiugos;
		if (PlayerBall.y + PlayerBall.r >= setumeibox[1].bottom)
			setumeiugos = -setumeiugos;
		mozicount++;
	}
	if (mozicount / 60 >= 3)
		ReturnKey();
	DrawCircle(PlayerBall.x = 500 + (int)(idoux * 5), PlayerBall.y = 500 + (int)(idouy * 5), PlayerBall.r = 20, white, false);
	seigen();
}
void Update_setumei() {
	setumeidassyu = 0;
	setumeisinobi = 0;
	if (PlayerBall.y >= 550) 
		page = action;
	if (SCC(PlayerBall, EnemyBlock[0]) == true) 
		page = title;
	seigen();
	if (CheckHitKey(KEY_INPUT_RSHIFT) == 1) 
		ReturnKey();
}
void Update_action() {
	score++;
	if (score / 60 >= 35 && diff >= 10 && diffm >= 5) 
		page = clear;
	if (score / 60 >= 999) 
		 score = 999 * 60; 
	if (score / 60 >= 5) 
		for (int i = 1; i < 3; i++) {
			boxugo[i]++;
			DrawBox(EnemyBlock[i].left = randpos[i] - 50, EnemyBlock[i].top = -100 + boxugo[i] * (i + 5) / 2, EnemyBlock[i].right = randpos[i] + 50, EnemyBlock[i].bottom = 0 + boxugo[i] * (i + 5) / 2, GetColor(255, 50, 50), true);
			if (SCC(PlayerBall, EnemyBlock[i]) == true)
				Collition();
			if (EnemyBlock[i].top >= 650) {
				randpos[i] = GetRand(800);
				boxugo[i] = -50;
				if (score / 60 >= 5)
					diff++;

			}
		}
	if (diff >= 1) 
		for (int i = 8; i < 12; i++) {
			boxugo[i]++;
			DrawBox(EnemyBlock[i].left = 25 + boxugo[i] * i / 2, EnemyBlock[i].top = randpos[i] - 0, EnemyBlock[i].right = 50 + boxugo[i] * i / 2, EnemyBlock[i].bottom = randpos[i] + 25, GetColor(255, 250, 50), true);
			if (SCC(PlayerBall, EnemyBlock[i]) == true) 
				Collition();
			if (EnemyBlock[i].left >= 850) {
				randpos[i] = GetRand(600);
				boxugo[i] = -50;
				diffm++;
			}
		}
	for (int i = 3; i < 8; i++) {
		boxugo[i]++;
		DrawBox(EnemyBlock[i].left = randpos[i] - 25, EnemyBlock[i].top = 75 + boxugo[i] * i, EnemyBlock[i].right = randpos[i] + 25, EnemyBlock[i].bottom = 125 + boxugo[i] * i, GetColor(255, 50, 250), true);
		if (SCC(PlayerBall, EnemyBlock[i]) == true) 
			Collition();
		if (EnemyBlock[i].top >= 650) {
			randpos[i] = GetRand(800);
			boxugo[i] = -50;
		}
	}
	if (diffm >= 10) 
		for (int i = 12; i < 20; i++) {
			boxugom[i]--;
			DrawBox(EnemyBlock[i].left = 825 + boxugom[i] * i / 3, EnemyBlock[i].top = randposm[i] - 0, EnemyBlock[i].right = 850 + boxugom[i] * i / 3, EnemyBlock[i].bottom = randposm[i] + 25, GetColor(100, 50, 255), true);
			if (SCC(PlayerBall, EnemyBlock[i]) == true) 
				Collition();
			if (EnemyBlock[i].right <= -20) {
				randposm[i] = GetRand(600);
				boxugom[i] = 1;
			}
		}
	if (score / 60 >= 27) 
		for (int i = 20; i < boxmax; i++) {
			boxugom[i]--;
			DrawBox(EnemyBlock[i].left = randposm[i] - 10, EnemyBlock[i].top = 590 + boxugom[i] * i / 5, EnemyBlock[i].right = randposm[i] + 10, EnemyBlock[i].bottom = 610 + boxugom[i] * i / 5, GetColor(100, 250, 70), true);
			if (SCC(PlayerBall, EnemyBlock[i]) == true) 
				Collition();
			if (EnemyBlock[i].bottom <= -20) {
				randposm[i] = GetRand(800);
				boxugom[i] = 1;
			}
		}
	seigen();
	if (CheckHitKey(KEY_INPUT_RETURN) == 1 && keystop == false) 
		keystop = true;
}
void Update_clear() {
	diff = 0;
	diffm = 0;
	kesi = false;
	for (int i = 0; i < boxmax; i++) {
		boxugo[i] = 0;
		boxugom[i] = 0;
		randposm[i] = 0;
	}
	ReturnKey();
	skip = false;
}
void Update_end() {
	zenkaiscore = score / 60;
	idoux = 0;
	idouy = 0;
	for (int i = 0; i < boxmax; i++) {
		boxugo[i] = 0;
		boxugom[i] = 0;
		randposm[i] = 0;
	}
	if (time_avo >= 0)
		if (time_avo >= 80) 
			time_avo -= 4;
		else 
			time_avo--;
	if (CheckHitKey(KEY_INPUT_RETURN) == 1) 
		if (countstop == false) {
			gamecount++;
			countstop = true;
		}
	whitedark = GetColor(time_avo / 2, time_avo / 2, time_avo / 2);
	ReturnKey();
	skip = true;
}
//Draw
void Draw_title() {
	if (time_avo >= 500) {
		DrawFormatString(280, 420, ash, "エンターキーでスタート\n");
		DrawFormatString(10, 10, GetColor(50, 250, 250), "SCORE : %d", score / 60);
		MaxScore();
	}
	SetFontSize(64);
	DrawFormatString(270, 200, whitedark, "avoidance");
	SetFontSize(NULL);
	DrawFormatString(330, 280, whitedark, "～ただひたすらに回避～\n");
}
void Draw_tyuupet() {
	if (kesi == true)
		for (int i = 0; i < 2; i++)
			DrawBox(setumeibox[i].left = 45 + i * 600, setumeibox[i].top = 150, setumeibox[i].right = 135 + i * 600, setumeibox[i].bottom = 450, white, false);
	if (kesi == false)
		if (mozicount < 30) {
			SetFontSize(25);
			DrawFormatString(100, 100, white, "まずは移動してみよう！\n");
			SetFontSize(NULL);
			DrawFormatString(120, 150, white, "W、A、S、D、キーあるいは十字キーを押して移動してね\n");
		}
	if (kesi == true) {
		SetFontSize(20);
		//DrawFormatString(100, 250, white, "エンターキーで次のページへ\n");
		SetFontSize(NULL);
		DrawFormatString(170, 130, white, "「WASDキー」で動く\n「左シフトキー」でダッシュ\n「左コントロールキー」でゆっくり動く\n");
		DrawFormatString(60, 120, white, "左Shift");
		DrawFormatString(660, 120, white, "左Ctrl");
	}
	if (mozicount / 60 >= 3) {
		SetFontSize(30);
		DrawFormatString(180, 500, white, "エンターキーで次のページへ\n");
		SetFontSize(NULL);
	}
	AtariSquaer();
	MaxScore();
}
void Draw_setumei() {
	DrawBox(EnemyBlock[0].left = 100, EnemyBlock[0].top = 100, EnemyBlock[0].right = 200, EnemyBlock[0].bottom = 200, white, true);
	DrawFormatString(250, 150, ash, "←これには当たらないでください\n");
	DrawFormatString(250, 300, white, "目標スコアは【３５】!!!\n");
	DrawCircle(PlayerBall.x = 500 + (int)(idoux * 5), PlayerBall.y = 500 + (int)(idouy * 5), PlayerBall.r = 20, white, false);
	DrawBox(0, 550, 800, 600, white, false);
	DrawLine(0, 570, 800, 570, GetColor(255, 50, 50), true);
	DrawFormatString(100, 570, white, "ここに来たらゲームスタート");
	AtariSquaer();
	DrawFormatString(10, 10, GetColor(50, 250, 250), "SCORE : %d", score / 60);
	MaxScore();
}
void Draw_action() {
	SetFontSize(60);
	DrawFormatString(250, 25, black, "%d回目\n", gamecount);
	SetFontSize(NULL);
	DrawCircle(PlayerBall.x = 500 + (int)(idoux * 5), PlayerBall.y = 500 + (int)(idouy * 5), PlayerBall.r = 20, white, false);
	AtariSquaer();
	DrawFormatString(10, 10, GetColor(50, 250, 250), "SCORE : %d", score / 60);
	MaxScore();
}
void Draw_clear() {
	SetFontSize(120);
	DrawFormatString(150, 100, white, "Clear!!!");
	SetFontSize(NULL);
	MaxScore();
}
void Draw_end() {
	SetFontSize(45);
	DrawFormatString(230, 25, black, "プレイ回数：%d回\n", gamecount);
	SetFontSize(NULL);
	if (time_avo <= 0) {
		SetFontSize(NULL);
		DrawFormatString(250, 400, ash, "continue?\n");
	}
	SetFontSize(60);
	DrawFormatString(350, 300, whitedark, "The end");
	SetFontSize(NULL);
	DrawFormatString(10, 10, GetColor(50, 250, 250), "SCORE : %d", score / 60);
	MaxScore();
}
//Main
void Avoidance_Start() {
	SetWindowText("avoidnce～ただひたすらに回避～");
	skip = false;
	countstop = false;
	idoux = 0;
	idouy = 0;
	setumeidassyu = 0;
	setumeisinobi = 0;
	time_avo = 0;
	mozicount = 0;
	ugox = 1;
	ugoy = 1;
	setumeiugod = 2;
	setumeiugos = 0.5;
	white = GetColor(255, 255, 255);
	whitedark = GetColor(255, 255, 255);
	ash = GetColor(180, 180, 180);
	dark = GetColor(100, 100, 100);
	black = GetColor(50, 50, 50);
	score = 0;
	zenkaiscore = score;
	maxscore = 0;
	gamecount = 1;
	diff = 0;
	diffm = 0;
	page = 0;
	keystop = false;
	kesi = false;

	for (int i = 0; i < boxmax; i++) {
		EnemyBlock[i].active = false;
		randpos[i] = GetRand(800);
		boxugo[i] = -50;
		randposm[i] = 0;
		boxugom[i] = 0;

		EnemyBlock[i].bottom = 0;
		EnemyBlock[i].left = 0;
		EnemyBlock[i].right = 0;
		EnemyBlock[i].top = 0;
	}
	for (int i = 0; i < 2; ++i) {
		setumeibox[i].active=false;
		setumeibox[i].bottom=0;
		setumeibox[i].left=0;
		setumeibox[i].right=0;
		setumeibox[i].top=0;
	}
	PlayerBall.r=0;
	PlayerBall.x=0;
	PlayerBall.y=0;
}
void Avoidance_Update(){
	switch (page) {
	case title:
		Update_title();
		break;
	case clearhantei:
		Update_clearhantei();
		break;
	case tyuupet:
		Update_tyuupet();
		break;
	case syokika:
		page++;
		break;
	case setumei:
		Update_setumei();
		break;
	case action:
		Update_action();
		break;
	case clear:
		Update_clear();
		break;
	case end:
		Update_end();
	}
	Checkhitkey();
	debug();
}
void Avoidance_Draw() {
	switch (page) {
	case title:
		Draw_title();
		break;
	case clearhantei:
		//無し
		break;
	case tyuupet:
		Draw_tyuupet();
		break;
	case syokika:
		//無し
		break;
	case setumei:
		Draw_setumei();
		break;
	case action:
		Draw_action();
		break;
	case clear:
		Draw_clear();
		break;
	case end:
		Draw_end();
		break;
	}
	//DrawFormatString(10, 10, GetColor(255,255,255),"%d", time_avo);
	//DrawFormatString(10,50,GetColor(255,255,255),"%d",page);
}
