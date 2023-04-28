#include"collitionsquare.h"
//Ž©•ª(move)‚Æ‘ŠŽè(static)‚Ì“–‚½‚è”»’è(Ž©•ª_XY,‘ŠŽè_XY,Ž©•ª‰æ‘œ‘å‚«‚³_XY,‘ŠŽè‰æ‘œ‘å‚«‚³_XY
//true‚©false‚ð•Ô‚·
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