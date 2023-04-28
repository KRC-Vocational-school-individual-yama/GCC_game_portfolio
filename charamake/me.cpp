#include "DxLib.h"
#include <string>
#include"collitionsquare.h"
#include"me.h"
#include"colors.h"


namespace {
	int r=255;
	int	g=255;
	int	b=255;
	const int gazox = 150, gazoy = 200;
	//�摜��
	const int xnum = 4, ynum = 1;
	//�X�N���[���摜x���W
	int imgx[ynum][xnum] = {};
	//�X�N���[���摜y���W
	int imgy[ynum][xnum] = {};
	//�X�N���[���摜�A��
	int meimg[ynum][xnum] = { -1 };
	int meimgoriginal = -1;
	//�X�N���[���摜flug
	bool meimgflug[ynum][xnum] = { false };

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

bool mebacktorf() {
	//�߂�{�^�������蔻��
	if (collitionsquare(mousex, mousey, backx, backy, 15, 20, 64, 32) &&
		GetMouseInput() & MOUSE_INPUT_LEFT
		) {
		return true;
	}
	return false;
}
void meReset() {
	//�}�E�X�z�C�[��(MouseWheel
	mw = 0;
	//�}�E�X�������ړ�(MouseWheelMove
	mwm = 0;
	//�߂�{�^������
	backflug = false;
	counter = 0;
}
int  megetimg() {
	return meimgoriginal;
}
int  megetx(){
	return gazox;
}
int  megety(){
	return gazoy;
}
void meInit() {
	meimgoriginal = meimg[0][0] = LoadGraph("gazo/4��/KGR_��.png");
	meimg[0][1] = LoadGraph("gazo/4��/KGR_�ڂ��炫��.png");
	meimg[0][2] = LoadGraph("gazo/4��/KGR_�ڃs���A.png");
	meimg[0][3] = LoadGraph("gazo/4��/KGR_�ڔZ.png");
	//�I������
	meimgflug[0][0] = true;
	colorsInit();
	r = 255;
	g = 255;
	b = 255;
}
void meDisp() {
	


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
				//if (j>=4&&i>=2)continue;
				//�F�֘A
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)
					&& (GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
					rc = 255;
				}
				else {
					rc = 0;
				}
				if (meimgflug[j][i] == true)rc = 255;
				//�������`��&�摜�`��
				if (counter++ >= (i + (j * xnum)) * 90) {
					DrawBox(
						xz + i * yah,
						yz + j * tah + mwm,
						(xz + yh) + i * yah,
						(yz + th) + j * tah + mwm,
						GetColor(rc, rc, rc), false);
					
					DrawRectGraph(imgx[j][i], imgy[j][i], 32 * 1, 64 * 0, 32, 64, meimg[j][i], true);
				}

				//���ō���̐����g�����߂̕ۑ�
				imgx[j][i] = xz + i * yah;
				imgy[j][i] = yz + j * tah + mwm;

			}
	colorsDraw();
}
void meMove() {
	GetMousePoint(&mousex, &mousey);

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//�I�����ړ����蔻��
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)) {
					if (GetMouseInput() & MOUSE_INPUT_LEFT) {
						meimgoriginal = meimg[j][i];
					}
					//���I�����ڂ�������
					for (int i = 0; i < xnum; i++)
						for (int j = 0; j < ynum; j++) {
							meimgflug[j][i] = false;
						}
					//�I�����n�C���C�g
					meimgflug[j][i] = true;
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
int megetR(){
	return r;
	}
int megetG(){
	return g;
	}
int megetB() {
	return b;
}
void meDelete() {
	for (int i = 0; i < xnum; i++)
		for (int j = 0; j < ynum; j++)
			DeleteGraph(meimg[j][i]);
	DeleteGraph(meimgoriginal);
}
