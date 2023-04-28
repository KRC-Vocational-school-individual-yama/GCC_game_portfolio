#include "DxLib.h"
#include"all.h"

static bool ENDFLUG=false;

void EndFulg_trueorfalse(bool flug) {
	ENDFLUG = flug;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);	//ウィンドウモードにする
	SetGraphMode(800, 600, 32);	//ウィンドウサイズを設定する
	SetBackgroundColor(0,0,0);//背景色設定
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

	MainInit();//最初に１回呼ぶ

	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_DECIMAL) == 0) {
		clsDx();
		SetBackgroundColor(0,0,0);//背景色設定

		MainUpdate();//毎回呼ぶ

		MainDraw();


		if (ENDFLUG == true)break;
		ScreenFlip();		//裏画面と表画面の入替
		ClearDrawScreen();	//裏画面の描画を全て消去
	}

	MainDelete();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
