#include<DxLib.h>
#include<string>
#include"collitionsquare.h"
#include"sentaku.h"
#include"charamake.h"

namespace {

	//�L�����ʒu
	const int gazox = 350, gazoy = 200;
	//�L�����摜��
	int imgs[10] = { -1 };

	//�摜��
	const int xnum = 5, ynum = 2;
	//�X�N���[���摜x���W
	int imgx[ynum][xnum] = {};
	//�X�N���[���摜y���W
	int imgy[ynum][xnum] = {};
	//�X�N���[���摜flug
	bool himgflug[ynum][xnum] = { false };
	//�X�N���[������
	std::string textbox[ynum][xnum] = {};

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
//����{�^���{�^�������蔻��
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
//�f�[�^������
void sentakuInit() {

	textbox[0][0] = "���̐F";
	textbox[0][1] = "��";
	textbox[0][2] = "�ǉ���";
	textbox[0][3] = "��";
	textbox[0][4] = "�O��";
	textbox[1][0] = "��딯";
	textbox[1][1] = "����";
	textbox[1][2] = "�t����";
	textbox[1][3] = "����";
	textbox[1][4] = "���";

}
void sentakuDisp() {
	//�w�i�F
	//DrawBox(0, 0, 800, 600, GetColor(248, 184, 98), true);
	//�L�������f��

	int th = 64;//�c��(tate_haba
	int yh = 64;//����//(yoko_haba
	int xz = 150;//X���W�ix_zahyo
	int yz = 400;//Y���W(y_zahyo
	int tah = 32 + th;//�c�A�Ԃ̕�(tate_aida_haba
	int yah = 32 + yh;//���A�Ԃ̕�(yoko_aida_haba
	int rc = 0;//�Վ��F(rinzi_color

	//�}�E�X�̈ړ������Ȃ�
	if (mw > 0)mw = 0;
	if (mw <= -(ynum - 2))mw = -(ynum - 2); //if (mw <= -8)mw = -8;
	if (mw * th > mwm)mwm += th / 8;
	if (mw * th < mwm)mwm -= th / 8;

	//�߂�{�^��//������Wx,y:xz-32-4*16,yz
	backflug ? rc = 255 : rc = 0;
	DrawBox(backx = 450, backy = 250, 450 + 64, 250 + 32, GetColor(rc, rc, rc), false);
	DrawFormatString(450 + 16, 250 + 8, GetColor(0, 0, 0), "����");

	//�I�����ږ{��
	if (character_C_flug == false)
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//��΂��p
				if (j >= 4 && i >= 2)continue;
				//�F�֘A
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 64, 64)
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
					//���ō���̐����g�����߂̕ۑ�
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
				//�I�����ړ����蔻��
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 64, 64)) {
					if (GetMouseInput() & MOUSE_INPUT_LEFT) {
						if (i == 0 && j == 0) {

						}

					}
					//���I�����ڂ�������
					for (int i = 0; i < xnum; i++)
						for (int j = 0; j < ynum; j++) {
							himgflug[j][i] = false;
						}
					//�I�����n�C���C�g
					//himgflug[j][i] = true;
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
}
void sentakuDelete() {
	for (int i = 0; i < 10; i++)
		DeleteGraph(imgs[i]);
}
