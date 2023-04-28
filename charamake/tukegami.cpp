#include "DxLib.h"
#include <string>
#include"collitionsquare.h"
#include"tukegami.h"
#include"colors.h"

namespace {
	int r = 255;
	int g = 255;
	int b =255;
	const int gazox = 150, gazoy = 200;
	//�摜��
	const int xnum = 6, ynum = 3;
	//�X�N���[���摜x���W
	int imgx[ynum][xnum] = {};
	//�X�N���[���摜y���W
	int imgy[ynum][xnum] = {};
	//�X�N���[���摜�A��
	int himg[ynum][xnum] = { -1 };
	int hsitaimg[ynum][xnum] = { -1 };
	int himgoriginal = -1;
	int hsitaimgoriginal = -1;
	//�X�N���[���摜flug
	bool himgflug[ynum][xnum] = { false };

	//�}�E�X�z�C�[��(MouseWheel
	int mw = 0;
	//�}�E�X�������ړ�(MouseWheelMove
	int mwm = 0;
	//�}�E�X�J�[�\���ʒu
	int mousex = 0,
		mousey = 0;
	//�߂�{�^������
	bool backflug = false;
	//�߂�{�^��XY
	int backx = 0, backy = 0;

	//�J�E���^
	int counter = 0;

	//��u���肷�邽�߁A������
	bool keystop = false;

	//debug�p
	bool character_C_flug = false;
}

bool tukegamibacktorf() {
	//�߂�{�^�������蔻��
	if (collitionsquare(mousex, mousey, backx, backy, 15, 20, 64, 32) &&
		GetMouseInput() & MOUSE_INPUT_LEFT
		) {
		return true;
	}
	return false;
}
void tukegamiReset() {
	//�}�E�X�z�C�[��(MouseWheel
	mw = 0;
	//�}�E�X�������ړ�(MouseWheelMove
	mwm = 0;
	//�߂�{�^������
	backflug = false;
	counter = 0;
}
int  tukegamigetimg() {
	return himgoriginal;
}
int  tukegamigetsitaimg() {
	return hsitaimgoriginal;
}
int  tukegamigetx(){
	return gazox;
}
int  tukegamigety(){
	return gazoy;
}
void tukegamiInit() {
	himgoriginal = himg[0][0] = -1;
	himg[0][1] = LoadGraph("gazo/8�t����/KGR_�c�C���e�[��.png");
	himg[0][2] = LoadGraph("gazo/8�t����/KGR_�c�C���e�[��_2.png");
	himg[0][3] = LoadGraph("gazo/8�t����/KGR_�n�[�t�A�b�v.png");
	himg[0][4] = LoadGraph("gazo/8�t����/KGR_�n�[�t�A�b�v_2.png");
	himg[0][5] = LoadGraph("gazo/8�t����/KGR_�n�[�t�e�[���E.png");
	himg[1][0] = LoadGraph("gazo/8�t����/KGR_�n�[�t�e�[���E_2.png");
	himg[1][1] = LoadGraph("gazo/8�t����/KGR_�n�[�t�e�[����.png");
	himg[1][2] = LoadGraph("gazo/8�t����/KGR_�n�[�t�e�[����_2.png");
	himg[1][3] = LoadGraph("gazo/8�t����/KGR_�㌋��.png");
	himg[1][4] = LoadGraph("gazo/8�t����/KGR_�㌋��_2.png");
	himg[1][5] = LoadGraph("gazo/8�t����/KGR_�t����_���c�q.png");
	himg[2][0] = LoadGraph("gazo/8�t����/KGR_�t����_���c�q_2.png");
	himg[2][1] = LoadGraph("gazo/8�t����/KGR_�t����_�|�j�[�e�[��.png");
	himg[2][2] = LoadGraph("gazo/8�t����/KGR_�t����_�|�j�[�e�[��_2.png");

	hsitaimgoriginal=hsitaimg[0][0] = -1;
	hsitaimg[0][1] = LoadGraph("gazo/8�t����/KGR_�c�C���e�[��$.png");
	hsitaimg[0][2] = LoadGraph("gazo/8�t����/KGR_�c�C���e�[��_2$.png");
	hsitaimg[0][3] = -1;
	hsitaimg[0][4] = -1;
	hsitaimg[0][5] = LoadGraph("gazo/8�t����/KGR_�n�[�t�e�[���E$.png");
	hsitaimg[1][0] = LoadGraph("gazo/8�t����/KGR_�n�[�t�e�[���E_2$.png");
	hsitaimg[1][1] = LoadGraph("gazo/8�t����/KGR_�n�[�t�e�[����$.png");
	hsitaimg[1][2] = LoadGraph("gazo/8�t����/KGR_�n�[�t�e�[����_2$.png");
	hsitaimg[1][3] = LoadGraph("gazo/8�t����/KGR_�㌋��$.png");
	hsitaimg[1][4] = LoadGraph("gazo/8�t����/KGR_�㌋��_2$.png");
	hsitaimg[1][5] = LoadGraph("gazo/8�t����/KGR_�t����_���c�q$.png");
	hsitaimg[2][0] = LoadGraph("gazo/8�t����/KGR_�t����_���c�q_2$.png");
	hsitaimg[2][1] = LoadGraph("gazo/8�t����/KGR_�t����_�|�j�[�e�[��$.png");
	hsitaimg[2][2] = LoadGraph("gazo/8�t����/KGR_�t����_�|�j�[�e�[��_2$.png");

	himgflug[0][0] = true;
	colorsInit();
}
void tukegamiDisp() {



	int th = 64;//�c��(tate_haba
	int yh = 32;//����//(yoko_haba
	int xz = 356;//��100+4*64__100;//X���W�ix_zahyo
	int yz = 100;//��36+1*64_36?;//Y���W(y_zahyo
	int tah = 32 + th;//�c�A�Ԃ̕�(tate_aida_haba
	int yah = 32 + yh;//���A�Ԃ̕�(yoko_aida_haba
	int rc = 0;//�Վ��F(rinzi_color

	//�}�E�X�̈ړ�����
	if (mw > 0)mw = 0;
	if (mw <= -(ynum - 2))mw = -(ynum - 2); //if (mw <= -8)mw = -8;
	if (mw * th > mwm)mwm += th / 8;
	if (mw * th < mwm)mwm -= th / 8;

	//�߂�{�^��//������Wx,y:xz-32-4*16,yz
	backflug ? rc = 255 : rc = 0;
	DrawBox(backx = xz - 32 - 4 * 16, yz + yh, xz - 32, backy = yz, GetColor(rc, rc, rc), false);//����
	DrawFormatString(xz - 32 - yah + 16, yz + 8, GetColor(0, 0, 0), "�߂�");

	//�I�����ږ{��
	if (character_C_flug == false)
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//��΂��p
				if (j >= 2 && i >= 3)continue;
				//�F�֘A
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)
					&& (GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
					rc = 255;
				}
				else {
					rc = 0;
				}
				if (himgflug[j][i] == true)rc = 255;
				//�������`��&�摜�`��
				if (counter++ >= (i + (j * xnum)) * 90) {
					DrawBox(
						xz + i * yah,
						yz + j * tah + mwm,
						(xz + yh) + i * yah,
						(yz + th) + j * tah + mwm,
						GetColor(rc, rc, rc), false);
					if (j == 0 && i == 0) {
						DrawFormatString(xz + 8, yz + mwm + 8, GetColor(rc, rc, rc), "��\n��\n");
					}
					int xk=1, yk=3;
					DrawRectGraph(imgx[j][i], imgy[j][i], 32 * xk, 64 * yk, 32, 64, hsitaimg[j][i], true);
					DrawRectGraph(imgx[j][i], imgy[j][i], 32 * xk, 64 * yk, 32, 64, himg[j][i], true);

				}

				//���ō���̐����g�����߂̕ۑ�
				imgx[j][i] = xz + i * yah;
				imgy[j][i] = yz + j * tah + mwm;

			}
	colorsDraw();
}
void tukegamiMove() {
	GetMousePoint(&mousex, &mousey);

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//�I�����ړ����蔻��
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)) {
					if (GetMouseInput() & MOUSE_INPUT_LEFT) {
						himgoriginal = himg[j][i];
						hsitaimgoriginal = hsitaimg[j][i];
					}
					//���I�����ڂ�������
					for (int i = 0; i < xnum; i++)
						for (int j = 0; j < ynum; j++) {
							himgflug[j][i] = false;
						}
					//�I�����n�C���C�g
					himgflug[j][i] = true;
				}
			}


	}
	//�߂�{�^���F
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
int tukegamigetR() {
	return r;
}
int tukegamigetG(){
	return g;
	}
int tukegamigetB(){
	return b;
	}
void tukegamiDelete() {
	for (int i = 0; i < xnum; i++)
		for (int j = 0; j < ynum; j++) {
			DeleteGraph(himg[j][i]);
			DeleteGraph(hsitaimg[j][i]);
		}
	DeleteGraph(himgoriginal);
	DeleteGraph(hsitaimgoriginal);
}
