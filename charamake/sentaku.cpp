#include<DxLib.h>
#include<string>
#include"collitionsquare.h"
#include"sentaku.h"
#include"charamake.h"

namespace {

	//キャラ位置
	const int gazox = 350, gazoy = 200;
	//キャラ画像箱
	int imgs[10] = { -1 };

	//画像数
	const int xnum = 5, ynum = 2;
	//スクロール画像x座標
	int imgx[ynum][xnum] = {};
	//スクロール画像y座標
	int imgy[ynum][xnum] = {};
	//スクロール画像flug
	bool himgflug[ynum][xnum] = { false };
	//スクロール文字
	std::string textbox[ynum][xnum] = {};

	//マウスホイール(MouseWheel
	int mw = 0;
	//マウスゆっくり移動(MouseWheelMove
	int mwm = 0;
	//マウスカーソル位置
	int mousex = 0,
		mousey = 0;
	//戻るボタン判定
	bool backflug = false;
	//戻るボタンXY
	int backx = 0, backy = 0;

	//カウンタ
	int counter = 0;

	//一瞬判定するため、いつもの
	bool keystop = false;

	//debug用
	bool character_C_flug = false;
}
//決定ボタンボタン当たり判定
bool sentakubacktorf() {

	if (collitionsquare(mousex, mousey, backx, backy, 15, 20, 64, 32) 
		&&GetMouseInput() & MOUSE_INPUT_LEFT
		) {
		return true;
	}
	return false;
}
bool sentakumodechenge(int x, int y) {
	if (collitionsquare(mousex, mousey, imgx[y][x], imgy[y][x], 15, 20, 64, 64)) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			return true;
		}
	}
	return false;
}
int sentakugetx() {
	return gazox;
}
int sentakugety() {
	return gazoy;
}
//データ初期化
void sentakuInit() {

	textbox[0][0] = "肌の色";
	textbox[0][1] = "服";
	textbox[0][2] = "追加服";
	textbox[0][3] = "目";
	textbox[0][4] = "前髪";
	textbox[1][0] = "後ろ髪";
	textbox[1][1] = "横髪";
	textbox[1][2] = "付け毛";
	textbox[1][3] = "装飾";
	textbox[1][4] = "一例";

}
void sentakuDisp() {
	//背景色
	//DrawBox(0, 0, 800, 600, GetColor(248, 184, 98), true);
	//キャラを映す

	int th = 64;//縦幅(tate_haba
	int yh = 64;//横幅//(yoko_haba
	int xz = 150;//X座標（x_zahyo
	int yz = 400;//Y座標(y_zahyo
	int tah = 32 + th;//縦、間の幅(tate_aida_haba
	int yah = 32 + yh;//横、間の幅(yoko_aida_haba
	int rc = 0;//臨時色(rinzi_color

	//マウスの移動制限など
	if (mw > 0)mw = 0;
	if (mw <= -(ynum - 2))mw = -(ynum - 2); //if (mw <= -8)mw = -8;
	if (mw * th > mwm)mwm += th / 8;
	if (mw * th < mwm)mwm -= th / 8;

	//戻るボタン//左上座標x,y:xz-32-4*16,yz
	backflug ? rc = 255 : rc = 0;
	DrawBox(backx = 450, backy = 250, 450 + 64, 250 + 32, GetColor(rc, rc, rc), false);
	DrawFormatString(450 + 16, 250 + 8, GetColor(0, 0, 0), "決定");

	//選択項目本体
	if (character_C_flug == false)
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//飛ばし用
				if (j >= 4 && i >= 2)continue;
				//色関連
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 64, 64)
					&& (GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
					rc = 255;
				}
				else {
					rc = 0;
				}
				if (himgflug[j][i] == true)rc = 255;
				//黒い線描画&画像描画
				if (counter++ >= (i + (j * xnum)) * 90) {
					DrawBox(
						xz + i * yah,
						yz + j * tah + mwm,
						(xz + yh) + i * yah,
						(yz + th) + j * tah + mwm,
						GetColor(rc, rc, rc), false);
					//他で左上の数字使うための保存
					imgx[j][i] = xz + i * yah;
					imgy[j][i] = yz + j * tah + mwm;
					DrawFormatString(imgx[j][i] + 8, imgy[j][i] + th - 16, GetColor(0, 0, 0), textbox[j][i].c_str());
				}



			}

}
void sentakuMove() {
	GetMousePoint(&mousex, &mousey);

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//選択項目当たり判定
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 64, 64)) {
					if (GetMouseInput() & MOUSE_INPUT_LEFT) {
						if (i == 0 && j == 0) {

						}

					}
					//一回選択項目を初期化
					for (int i = 0; i < xnum; i++)
						for (int j = 0; j < ynum; j++) {
							himgflug[j][i] = false;
						}
					//選択をハイライト
					//himgflug[j][i] = true;
				}
			}


	}
	//戻るボタン色
	if (collitionsquare(mousex, mousey, backx, backy, 15, 20, 64, 32)) {
		backflug = true;
	}
	else backflug = false;

	mw += GetMouseWheelRotVol();


	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		keystop = false;
	}
}
void sentakuDelete() {
	for (int i = 0; i < 10; i++)
		DeleteGraph(imgs[i]);
}
