#include"collitionsquare.h"
//����(move)�Ƒ���(static)�̓����蔻��(����_XY,����_XY,�����摜�傫��_XY,����摜�傫��_XY
//true��false��Ԃ�
bool collitionsquare(int zibun_x, int zibun_y,
	int aite_x, int aite_y,
	int zibunimgsizex, int zibunimgsizey,
	int aiteimgsizex , int aiteimgsizey
) {
	//x=Left,x2=Right,y=Up,y2=Down,z,a,
	int zx = zibun_x, zy = zibun_y, zx2 = zibun_x + zibunimgsizex, zy2 = zibun_y + zibunimgsizey, ax = aite_x, ay = aite_y, ax2 = aite_x + aiteimgsizex, ay2 = aite_y + aiteimgsizey;
	/*
	zx,zy,zx2,zy2,
	ax,ay,ax2,ay2*/
	bool up = false, down = false, left = false, right = false;
	if (ay <= zy2)up = true;
	if (ay2 >= zy)down = true;
	if (ax <= zx2)left = true;
	if (ax2 >= zx)right = true;

	if (up == true &&
		down == true &&
		left == true &&
		right == true
		)return true;

	return false;
}