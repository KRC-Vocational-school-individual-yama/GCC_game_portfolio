#include "DxLib.h"
#include <string>
#include"collitionsquare.h"
#include"doutai.h"
#include"colors.h"

namespace {
	const int gazox = 150, gazoy = 200;
	//画像数
	const int xnum = 2, ynum = 1;
	//スクロール画像x座標
	int imgx[ynum][xnum] = {};
	//スクロール画像y座標
	int imgy[ynum][xnum] = {};
	//スクロール画像、箱
	int dimg[ynum][xnum] = { -1 };
	int dimgoriginal = -1;
	//スクロール画像flug
	bool dimgflug[ynum][xnum] = { false };

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

	int r=255,
		g=255, 
		b=255;
}

//データ初期化
//ステータス表示
void doutaiDisp() {
	
	int th = 64;//縦幅(tate_haba
	int yh = 32;//横幅//(yoko_haba
	int xz = 356;//←100+4*64__100;//X座標（x_zahyo
	int yz = 100;//←36+1*64_36?;//Y座標(y_zahyo
	int tah = 32 + th;//縦、間の幅(tate_aida_haba
	int yah = 32 + yh;//横、間の幅(yoko_aida_haba
	int rc = 0;//臨時色(rinzi_color

	//マウスの移動制限
	if (mw > 0)mw = 0;
	if (mw <= -(ynum - 2))mw = -(ynum - 2); //if (mw <= -8)mw = -8;
	if (mw * th > mwm)mwm += th / 8;
	if (mw * th < mwm)mwm -= th / 8;

	//戻るボタン//左上座標x,y:xz-32-4*16,yz
	backflug ? rc = 255 : rc = 0;
	DrawBox(backx = xz - 32 - 4 * 16, yz + yh, xz - 32, backy = yz, GetColor(rc, rc, rc), false);//左下
	DrawFormatString(xz - 32 - yah + 16, yz + 8, GetColor(0, 0, 0), "戻る");

	//選択項目本体
	if (character_C_flug == false)
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//飛ばし用
				//if (j>=4&&i>=2)continue;
				//色関連
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)
					&& (GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
					rc = 255;
				}
				else {
					rc = 0;
				}
				if (dimgflug[j][i] == true)rc = 255;
				//黒い線描画&画像描画
				if (counter++ >= (i + (j * xnum)) * 90) {
					DrawBox(
						xz + i * yah,
						yz + j * tah + mwm,
						(xz + yh) + i * yah,
						(yz + th) + j * tah + mwm,
						GetColor(rc, rc, rc), false);

					DrawRectGraph(imgx[j][i], imgy[j][i], 32 * 1, 64 * 0, 32, 64, dimg[j][i], true);
				}

				//他で左上の数字使うための保存
				imgx[j][i] = xz + i * yah;
				imgy[j][i] = yz + j * tah + mwm;

			}

	colorsDraw();
}
void doutaiMove() {
	colorsUpdate();
	GetMousePoint(&mousex, &mousey);

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//選択項目当たり判定
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)) {
					if (GetMouseInput() & MOUSE_INPUT_LEFT) {
						dimgoriginal = dimg[j][i];
					}
					//一回選択項目を初期化
					for (int i = 0; i < xnum; i++)
						for (int j = 0; j < ynum; j++) {
							dimgflug[j][i] = false;
						}
					//選択をハイライト
					dimgflug[j][i] = true;
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

	r=getcolorvaluesR();
	g=getcolorvaluesG();
	b=getcolorvaluesB();
}
void doutaiReset() {
	//マウスホイール(MouseWheel
	mw = 0;
	//マウスゆっくり移動(MouseWheelMove
	mwm = 0;
	//戻るボタン判定
	backflug = false;
	counter = 0;
}
int  doutaigetimg() {
	return dimgoriginal;

}
int  doutaigetx() {
	return gazox;

}
int  doutaigety() {
	return gazoy;

}
bool doutaibacktorf() {
	//戻るボタン当たり判定
	if (collitionsquare(mousex, mousey, backx, backy, 15, 20, 64, 32) &&
		GetMouseInput() & MOUSE_INPUT_LEFT
		) {
		return true;
	}
	return false;
}
int doutaigetR(){
	return r;
	}
int doutaigetB(){
	return b;
	}
int doutaigetG() {
	return g;
}
void doutaiInit() {
	dimgoriginal = dimg[0][0] = LoadGraph("gazo/1胴体/KGR_胴体_ピーチ.png");
	dimg[0][1] = LoadGraph("gazo/1胴体/KGR_胴体_ライトピーチ.png");
	//選択項目
	dimgflug[0][0] = true;
	r=255;
	g=255;
	b=255;
	colorsInit();
}
void doutaiDelete() {
	for (int i = 0; i < xnum; i++)
		for (int j = 0; j < ynum; j++)
			DeleteGraph(dimg[j][i]);
	DeleteGraph(dimgoriginal);
}
