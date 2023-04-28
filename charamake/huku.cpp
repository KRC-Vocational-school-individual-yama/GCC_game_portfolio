#include "DxLib.h"
#include <string>
#include"collitionsquare.h"
#include"huku.h"
#include"colors.h"
 
namespace {
	const int gazox = 150, gazoy = 200;

	//画像数
	const int xnum = 6, ynum = 5;
	//スクロール画像x座標
	int imgx[ynum][xnum] = {};
	//スクロール画像y座標
	int imgy[ynum][xnum] = {};
	//スクロール画像、箱
	int himg[ynum][xnum] = { -1 };
	int himgoriginal = -1;
	//スクロール画像flug
	bool himgflug[ynum][xnum] = { false };

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

	int r = 255,
		g=255,
		b=255;
}

bool hukubacktorf() {
	//戻るボタン当たり判定
	if (collitionsquare(mousex, mousey, backx, backy, 15, 20, 64, 32) &&
		GetMouseInput() & MOUSE_INPUT_LEFT
		) {
		return true;
	}
	return false;
}
int hukugetimg() {

	return himgoriginal;
}
int hukugetx(){
	return gazox;
}
int hukugety(){
	return gazoy;
}
void hukuReset() {
	//マウスホイール(MouseWheel
	mw = 0;
	//マウスゆっくり移動(MouseWheelMove
	mwm = 0;
	//戻るボタン判定
	 backflug = false;
	counter = 0;
}
//データ初期化
void hukuInit() {
	hukuReset();
	himgoriginal = himg[0][0] = LoadGraph("gazo/2服/KGR_シャツスカート＆ベスト.png");
	himg[0][1] = LoadGraph("gazo/2服/KGR_シャツスカート.png");
	himg[0][2] = LoadGraph("gazo/2服/KGR_シャツズボン＆ベスト.png");
	himg[0][3] = LoadGraph("gazo/2服/KGR_シャツズボン.png");
	himg[0][4] = LoadGraph("gazo/2服/KGR_ドレス.png");
	himg[0][5] = LoadGraph("gazo/2服/KGR_ドレス_黒.png");
	himg[1][0] = LoadGraph("gazo/2服/KGR_ドレス_青.png");
	himg[1][1] = LoadGraph("gazo/2服/KGR_ドレス_赤.png");
	himg[1][2] = LoadGraph("gazo/2服/KGR_ドレス_白.png");
	himg[1][3] = LoadGraph("gazo/2服/KGR_ビギナー女.png");
	himg[1][4] = LoadGraph("gazo/2服/KGR_ビギナー男.png");
	himg[1][5] = LoadGraph("gazo/2服/KGR_ワンピ.png");
	himg[2][0] = LoadGraph("gazo/2服/KGR_ワンピ_青.png");
	himg[2][1] = LoadGraph("gazo/2服/KGR_ワンピ_赤.png");
	himg[2][2] = LoadGraph("gazo/2服/KGR_ワンピ_緑.png");
	himg[2][3] = LoadGraph("gazo/2服/KGR_村人女性.png");
	himg[2][4] = LoadGraph("gazo/2服/KGR_旅人の服A.png");
	himg[2][5] = LoadGraph("gazo/2服/KGR_旅人の服A_黄.png");
	himg[3][0] = LoadGraph("gazo/2服/KGR_旅人の服A_青.png");
	himg[3][1] = LoadGraph("gazo/2服/KGR_旅人の服A_緑.png");
	himg[3][2] = LoadGraph("gazo/2服/KGR_旅人の服B.png");
	himg[3][3] = LoadGraph("gazo/2服/KGR_旅人の服B_黄.png");
	himg[3][4] = LoadGraph("gazo/2服/KGR_旅人の服B_青.png");
	himg[3][5] = LoadGraph("gazo/2服/KGR_旅人の服B_赤.png");
	himg[4][0] = LoadGraph("gazo/2服/KGR_旅人の服B_白灰.png");
	himg[4][1] = LoadGraph("gazo/2服/KGR_旅人の服B_緑.png");
	//選択項目
	himgflug[0][0] = true;
	r = 255;
	g = 255;
	b = 255;
}
void hukuDisp() {
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
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//飛ばし用
				if (j >= 4 && i >= 2)continue;
				//色関連
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)
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

					DrawRectGraph(imgx[j][i], imgy[j][i], 32 * 1, 64 * 0, 32, 64, himg[j][i], true);
				}

				//他で左上の数字使うための保存
				imgx[j][i] = xz + i * yah;
				imgy[j][i] = yz + j * tah + mwm;

			}
		colorsDraw();
}
void hukuMove() {
	
	GetMousePoint(&mousex, &mousey);

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//選択項目当たり判定
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)) {
					if (GetMouseInput() & MOUSE_INPUT_LEFT) {
						himgoriginal = himg[j][i];
					}
					//一回選択項目を初期化
					for (int i = 0; i < xnum; i++)
						for (int j = 0; j < ynum; j++) {
							himgflug[j][i] = false;
						}
					//選択をハイライト
					himgflug[j][i] = true;
				}
			}


	}
	hukubacktorf();
	
	//戻るボタン色
	if (collitionsquare(mousex, mousey, backx, backy, 15, 20, 64, 32)) {
		backflug = true;
	}
	else backflug = false;

	mw += GetMouseWheelRotVol();


	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		keystop = false;
	}
	colorsUpdate();
	r = getcolorvaluesR();
	g = getcolorvaluesG();
	b = getcolorvaluesB();
}
int hukugetR(){
	return r;
	}
int hukugetG(){
	return g;
	}
int hukugetB() {
	return b;
}
void hukuDelete() {
	for (int i = 0; i < xnum; i++)
		for (int j = 0; j < ynum; j++)
			DeleteGraph(himg[j][i]);
	DeleteGraph(himgoriginal);
}