#include "DxLib.h"
#include <string>
#include"collitionsquare.h"
#include"huku.h"
#include"colors.h"
 
namespace {
	const int gazox = 150, gazoy = 200;

	//�摜��
	const int xnum = 6, ynum = 5;
	//�X�N���[���摜x���W
	int imgx[ynum][xnum] = {};
	//�X�N���[���摜y���W
	int imgy[ynum][xnum] = {};
	//�X�N���[���摜�A��
	int himg[ynum][xnum] = { -1 };
	int himgoriginal = -1;
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

	int r = 255,
		g=255,
		b=255;
}

bool hukubacktorf() {
	//�߂�{�^�������蔻��
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
	//�}�E�X�z�C�[��(MouseWheel
	mw = 0;
	//�}�E�X�������ړ�(MouseWheelMove
	mwm = 0;
	//�߂�{�^������
	 backflug = false;
	counter = 0;
}
//�f�[�^������
void hukuInit() {
	hukuReset();
	himgoriginal = himg[0][0] = LoadGraph("gazo/2��/KGR_�V���c�X�J�[�g���x�X�g.png");
	himg[0][1] = LoadGraph("gazo/2��/KGR_�V���c�X�J�[�g.png");
	himg[0][2] = LoadGraph("gazo/2��/KGR_�V���c�Y�{�����x�X�g.png");
	himg[0][3] = LoadGraph("gazo/2��/KGR_�V���c�Y�{��.png");
	himg[0][4] = LoadGraph("gazo/2��/KGR_�h���X.png");
	himg[0][5] = LoadGraph("gazo/2��/KGR_�h���X_��.png");
	himg[1][0] = LoadGraph("gazo/2��/KGR_�h���X_��.png");
	himg[1][1] = LoadGraph("gazo/2��/KGR_�h���X_��.png");
	himg[1][2] = LoadGraph("gazo/2��/KGR_�h���X_��.png");
	himg[1][3] = LoadGraph("gazo/2��/KGR_�r�M�i�[��.png");
	himg[1][4] = LoadGraph("gazo/2��/KGR_�r�M�i�[�j.png");
	himg[1][5] = LoadGraph("gazo/2��/KGR_�����s.png");
	himg[2][0] = LoadGraph("gazo/2��/KGR_�����s_��.png");
	himg[2][1] = LoadGraph("gazo/2��/KGR_�����s_��.png");
	himg[2][2] = LoadGraph("gazo/2��/KGR_�����s_��.png");
	himg[2][3] = LoadGraph("gazo/2��/KGR_���l����.png");
	himg[2][4] = LoadGraph("gazo/2��/KGR_���l�̕�A.png");
	himg[2][5] = LoadGraph("gazo/2��/KGR_���l�̕�A_��.png");
	himg[3][0] = LoadGraph("gazo/2��/KGR_���l�̕�A_��.png");
	himg[3][1] = LoadGraph("gazo/2��/KGR_���l�̕�A_��.png");
	himg[3][2] = LoadGraph("gazo/2��/KGR_���l�̕�B.png");
	himg[3][3] = LoadGraph("gazo/2��/KGR_���l�̕�B_��.png");
	himg[3][4] = LoadGraph("gazo/2��/KGR_���l�̕�B_��.png");
	himg[3][5] = LoadGraph("gazo/2��/KGR_���l�̕�B_��.png");
	himg[4][0] = LoadGraph("gazo/2��/KGR_���l�̕�B_���D.png");
	himg[4][1] = LoadGraph("gazo/2��/KGR_���l�̕�B_��.png");
	//�I������
	himgflug[0][0] = true;
	r = 255;
	g = 255;
	b = 255;
}
void hukuDisp() {
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
		for (int i = 0; i < xnum; i++)
			for (int j = 0; j < ynum; j++) {
				//��΂��p
				if (j >= 4 && i >= 2)continue;
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

					DrawRectGraph(imgx[j][i], imgy[j][i], 32 * 1, 64 * 0, 32, 64, himg[j][i], true);
				}

				//���ō���̐����g�����߂̕ۑ�
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
				//�I�����ړ����蔻��
				if (collitionsquare(mousex, mousey, imgx[j][i], imgy[j][i], 15, 20, 32, 64)) {
					if (GetMouseInput() & MOUSE_INPUT_LEFT) {
						himgoriginal = himg[j][i];
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
	hukubacktorf();
	
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