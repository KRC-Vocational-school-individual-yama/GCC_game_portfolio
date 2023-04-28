#include"mapchip.h"
#include <DxLib.h>
#include <string>
#include"house.h"

void Wood();
void yuka();
void housekabe();
void houseyane();
void kagubed();
void kagubook();
void sotoobject();
void kanban();
void hatake();
void saku();
void gake();
void siba();
void world();
void incavekabe();
void incavetenjou();
void incavetenjou_2();
void incavelava();
void animlight();
void disp_inDraw();
void doayane();
void Songs();
bool collition(char mono, int muki);
namespace {



	housedraw houses;
	std::string mobmesse = "";
	//https://dixq.net/forum/viewtopic.php?t=13272

	const int x_max = 100;
	const int y_max = 50;
	const int height = y_max;
	const int width = x_max + 1;

	bool keystop = false;

	int mozicount = 0;
	int mozisize = false;
	bool moziflug = false;
	bool ugokistop = false;

	//inventory関連
	int cinventory = 0;
	bool finventory = false;

	bool kaiwaflug = false;
	int ckaiwa = 0;
	bool mapflug = false;
	int cmapflug = 0;

	int speed = 1;
	bool cjudge = false;

	tm taketime;
	enum Mode {
		enum_title,
		enum_field,
		enum_stop,
	};
	enum field {
		field_normal,
		house_o,
		house_m,
		house_n,
		house_b,
		house_v,
		under,
		field_world,
		field_cave,
		field_forest,
	};
	struct mapdata {
		float x, y;
	};

	//マップ
	const char map[height][width] = {
		/*
		1234567890^
		qwertyuiop@[	QWE
		 sdfghjkl;:]	ASD
		zxcvbnm   \		ZXC
		*/

		"p[lklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklklkp[",
		"piuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiuiu[",
		"p1                                                                                                2[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwww     wwwwwwwwwwwwwwwwwwwwww890wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwww     wwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwcwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww       wwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww       wwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwww        wwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwhhhhhhhhhwwwwwwwwwwww            wwwz[",
		"pzwwwwwwwwwwwwww        wwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwyyyyyyyyywwwwwwwwwwww            wwwz[",
		"pzwwwwwwwwwwwwww wwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwgggggggggwwwwwwwwwwww            wwwz[",
		"pzwwwwwwwwwwwww  wwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwseeeeeeerwwwwwwwwwwww            wwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwww,hhhhhhhhwwwwwwww567wwwwwwwwwwwwseeeeeeerwwwwwwwwwwww            wwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwyyyyyyyyywwwwwwww567wwwwwwwwwwwwseeeeeeerwwwwwwwwwwww            wwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwgggggggggwwwwwwww567wwwwwwwwwwwwxdddmdddfwwwwwwwwwwww            wwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwseeeeeeerwwww89996669990wwwwwwwwwwwwwwwwwwwwww            wwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwseeeeeeerwwww56666666667wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwseeeeeeerwwww566:::::667wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwxdddodddfwwww567wwwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wQWEw567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wASDw567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wZXCw567wwwwwwwwwwwwhhhhhhhhhwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwww567wwwwwwwwwwwwyyyyyyyyywwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww89999966699999667wwwwwwwwwwwwgggggggggwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww56666666666666667wwwwwwwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwww,hhhhhhhhwww566:::::::::::::]wwwwwwwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwyyyyyyyyywww567wwwwwwwwwwwwwwwwwwwwwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwgggggggggwww567wwwwwwwwwwwwwwwwwwwwwwwwwwxdddndddfwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwseeeeeeerwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwseeeeeeerwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwseeeeeeerwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwxdddodddfwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwhhhhhhhhhwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwyyyyyyyyywwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwgggggggggwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww567wwwwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwww,hhhhhhhhwwwwwwwwwwwwwwwwwwww567wwwwwwwwwxdddbdddfwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwyyyyyyyyywwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwgggggggggwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwseeeeeeerwwwwwwwwwwwwwwwwwwww567wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwxdddodddfwwwwwwwwwwwwwwwwwwww;:]wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwtwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"pzwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwz[",
		"p3                                 2wwwww1                                                        4[",
		"p@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^zwwwwwzw@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^["
	};
	const char map_world[height][width] = {

		"                         ",
		"                         ",
		"        122222223        ",
		"      12wwwwwwwww23      ",
		"     1wwwtftwwwwwww23    ",
		"    1wwwwfFfwwwwwwwww3   ",
		"    8wwwwwwwwwwwwwwww4   ",
		"   1wwwwwwwwwwwwwwwwww3  ",
		"   8wwwwwwwwwwwwwwwwww4  ",
		"   8wwwwwunwwwwwwwwwww5  ",
		"   8wwwwwmowwwwwwhwww4-  ",
		"   8wwwwwwwwwwwwwwwww4   ",
		"   7wwwwwwwwwwwwwwwww5   ",
		"   98wwwwwwwwwwwwww65-   ",
		"    7wwwwwwwwwww6650-    ",
		"    97666666666500-      ",
		"     9000000000-         ",
		"                         ",
		"                         ",
	};
	mapdata mapd;
	mapdata beformapd;
	mapdata smapd;//start
	mapdata kumoidou;
	const char map_house[height][width]{
		"                              ",
		"pwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwttttwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww[",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		" wwwwwwwwwwwwwwwwwwwwwwwwwwww ",
		"           wwwwwwwww          ",
		"           ooooooooo          ",
		"           ooooooooo          ",
		"                              "

	};
	const char map_cave[height][width]{
		/*
			|				|
			| w  t			|
			|asdfghjkl;:]	|        L+*}
			|zxcvbnm,		|       <>?_
		*/
		"       nhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvk       ",
		"       x}+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++f       ",
		"       z_>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>f       ",
		"       xwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       ",
		"       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwf       ",
		"       xwwwwagcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgc:wwwwd       ",
		"       zwwwwf                                                                          xwwwwf       ",
		"       xwwwwd                                                                          zwwwwd       ",
		"       zwwwwf       nhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvk       xwwwwf       ",
		"       xwwwwd       x}+++++++++++++++++++++++++++++++++++++++++++++++++++++++++f       zwwwwd       ",
		"       zwwwwf       z_>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>d       xwwwwf       ",
		"       xwwwwd       xwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwagcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgc:wwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwd                                                xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwf           nhvhvhvhvhvhvhvhvhvhvhvk             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwd           z}+++++++++++++++++++++d             xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwf           x_>>>>>>>>>>>>>>>>>>>>>f             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwd           zwwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwf           xwwwwwwwwwwwwwwwwwwwwwwf             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwd           zwwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwshvhvhvhvhvh]wwwwwwwwwwwwwwwwwwwwwwf             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwL+++++++++++*wwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwww<>>>>>>>>>>>?wwwwwwwwwwwwwwwwwwwwwwf             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd       bgcgcgcgcgcgcgcgc:wwwwwwwwwwwwwwwwwwwwwwf             zwwwwf       zwwwwd       ",
		"       zwwwwf                        zwwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd                        bgcgcgcgcgcgcgcgcgcgcgcj             zwwwwf       zwwwwd       ",
		"       zwwwwf                                                             xwwwwd       xwwwwf       ",
		"       xwwwwd                                                             zwwwwf       zwwwwd       ",
		"       zwwwwshvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvh]wwwwd       xwwwwf       ",
		"       xwwwwL+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*wwwwf       zwwwwd       ",
		"       zwwww<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>?wwwwd       xwwwwf       ",
		"       xwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwf       zwwwwd       ",
		"       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       xwwwwf       ",
		"       xwwwwagcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcj       zwwwwd       ",
		"       zwwwwf                                                                          xwwwwf       ",
		"       xwwwwd                                                                          zwwwwd       ",
		"       zwwwwf      nvhvhvhvhvhvhvhvhk          nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv]wwwwf       ",
		"       xwwwwd      z}+++++++++++++++d          z}++++++++++++++++++++++++++++++++++++++*wwwwd       ",
		"       zwwwwshvhvhv]_>>>>>>>>>>>>>>>f          x_>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>?wwwwf       ",
		"       xwwwwL++++++*wwwwwwwwwwwwwwwwd          zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       ",
		"       zwwww<>>>>>>?wwwwwwwwwwwwwwwwf          xwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       ",
		"       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwf          xwwwwagcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgj       ",
		"       xwwwwwwwwwwwwwwwwwwwwwwwwwwwwd          zwwwwf                                               ",
		"       bgcgcgcgcgcg:wwwwwwwwwwwwwwwwf          xwwwwd                                               ",
		"                   zwwwwwwwwwwwwwwwwd          zwwtwf                                               ",
		"                   bgcgcgcgcgcgcgcgcj          xwwwwd                                               ",
		"                                               zwwwwf                                               ",
		"                                               ]wwwws                                               "
	};
	const char map_forest[height][width]{
		/*
			|				|
			| w  t			|
			|asdfghjkl;:]	|        L+*}
			|zxcvbnm,		|       <>?_
		*/
		"       nhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvk       ",
		"       x}+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++f       ",
		"       z_>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>f       ",
		"       xwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       ",
		"       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwf       ",
		"       xwwwwagcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgc:wwwwd       ",
		"       zwwwwf                                                                          xwwwwf       ",
		"       xwwwwd                                                                          zwwwwd       ",
		"       zwwwwf       nhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvk       xwwwwf       ",
		"       xwwwwd       x}+++++++++++++++++++++++++++++++++++++++++++++++++++++++++f       zwwwwd       ",
		"       zwwwwf       z_>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>d       xwwwwf       ",
		"       xwwwwd       xwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwagcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgc:wwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwd                                                xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwf           nhvhvhvhvhvhvhvhvhvhvhvk             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwd           z}+++++++++++++++++++++d             xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwf           x_>>>>>>>>>>>>>>>>>>>>>f             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwd           zwwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwf           xwwwwwwwwwwwwwwwwwwwwwwf             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwd           zwwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwwwshvhvhvhvhvh]wwwwwwwwwwwwwwwwwwwwwwf             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwL+++++++++++*wwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd       xwwww<>>>>>>>>>>>?wwwwwwwwwwwwwwwwwwwwwwf             zwwwwf       zwwwwd       ",
		"       zwwwwf       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd       bgcgcgcgcgcgcgcgc:wwwwwwwwwwwwwwwwwwwwwwf             zwwwwf       zwwwwd       ",
		"       zwwwwf                        zwwwwwwwwwwwwwwwwwwwwwwd             xwwwwd       xwwwwf       ",
		"       xwwwwd                        bgcgcgcgcgcgcgcgcgcgcgcj             zwwwwf       zwwwwd       ",
		"       zwwwwf                                                             xwwwwd       xwwwwf       ",
		"       xwwwwd                                                             zwwwwf       zwwwwd       ",
		"       zwwwwshvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvhvh]wwwwd       xwwwwf       ",
		"       xwwwwL+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*wwwwf       zwwwwd       ",
		"       zwwww<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>?wwwwd       xwwwwf       ",
		"       xwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwf       zwwwwd       ",
		"       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       xwwwwf       ",
		"       xwwwwagcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcj       zwwwwd       ",
		"       zwwwwf                                                                          xwwwwf       ",
		"       xwwwwd                                                                          zwwwwd       ",
		"       zwwwwf      nvhvhvhvhvhvhvhvhk          nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv]wwwwf       ",
		"       xwwwwd      z}+++++++++++++++d          z}++++++++++++++++++++++++++++++++++++++*wwwwd       ",
		"       zwwwwshvhvhv]_>>>>>>>>>>>>>>>f          x_>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>?wwwwf       ",
		"       xwwwwL++++++*wwwwwwwwwwwwwwwwd          zwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       ",
		"       zwwww<>>>>>>?wwwwwwwwwwwwwwwwf          xwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd       ",
		"       zwwwwwwwwwwwwwwwwwwwwwwwwwwwwf          xwwwwagcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgcgj       ",
		"       xwwwwwwwwwwwwwwwwwwwwwwwwwwwwd          zwwwwf                                               ",
		"       bgcgcgcgcgcg:wwwwwwwwwwwwwwwwf          xwwwwd                                               ",
		"                   zwwwwwwwwwwwwwwwwd          zwwwwf                                               ",
		"                   bgcgcgcgcgcgcgcgcj          xwwtwd                                               ",
		"                                               zwwwwf                                               ",
		"                                               ]wwwws                                               "
	};
	//マップチップ
	int		 MapChip[8 * 54] = {};
	int		 yukanochip[8 * 6] = {};
	int		 midorichip[8 * 9] = {};
	int	 housekabechip[7 * 25] = {};
	int	 houseyanechip[8 * 18] = {};
	int	   kagubedchip[8 * 19] = {};
	int   kagubookchip[8 * 15] = {};
	int sotoobjectchip[8 * 13] = {};
	int		 kanbanchip[7 * 3] = {};
	int		 hatakechip[8 * 4] = {};
	int	       sakuchip[8 * 7] = {};
	int		  gakechip[8 * 11] = {};
	int sibachip[8 * 6] = {};
	int		  worldchip[8 * 4] = {};
	int   incave_kabechip[9 * 34] = {};
	int incave_tenjouchip[2 * 12] = {};
	int   incave_lavachip[2 * 12] = {};//8ppi
	int    anim_lightchip[6 * 5] = {};
	int doaimg [18 * 8] = {};
	int img[25 * 7] = {};
	int kumoimg = -1;

	enum musics {
		music_normal,
		music_world,
		music_cave,
		music_cave2,

		enum_music_max
	};
	const int musicmax = enum_music_max;
	int musics[musicmax] = {};
	int music_c[musicmax] = {};

	enum sounds {
		doa,
		terotero,

		enum_sound_max
	};
	const int soundmax = enum_sound_max;
	int sounds[soundmax] = {};
	int sound_c[soundmax] = {};


	//プレイヤー座標
	double x = 25.0;
	double y = 18.0;
	//ゲームモード
	int mode = 0;
	int modememory = 0;
	int field = 0;
	bool stop = true;
	int Player;

	std::string musictext = "";


	class mobchip {
	public:
		float x, y;//int ならビット調の動き、floatならするする動く
		int img = -1;
		int muki = 0;

		mobchip();
		void reset();
		void mobAnime();
		void mobDraw();
		int moveX(double speed);//直接ｘに入れる
		int moveY(double speed);//直接yに入れる
		~mobchip();

	private:

		void _0_1_2_1_0_(int& x);
		void counter() { count++; };
		void mobmove();
		int count = 0;
		int handlex = 1;
		int handley = 0;
		int movecount = 0;

		bool moveflug = false;
		int movecool = 0;
	};
	mobchip mob[10][2];
	mobchip::mobchip() {
		img = -1;
		x = 0;
		y = 0;
		count = 0;
		handlex = 1;
		handley = 0;
		movecount = 0;
		muki = 0;
		moveflug = false;
		movecool = 0;
		reset();
	}
	mobchip::~mobchip() {
		DeleteGraph(img);
	}
	void mobchip::reset() {
		count = 0;
		handlex = 1;
		handley = 0;
		x = 0;
		y = 0;
		movecount = 0;
		muki = 0;
		moveflug = false;
		movecool = 0;
	}
	void mobchip::_0_1_2_1_0_(int& x) {
		counter();
		x = count / 13 % 4;
		if (x == 3)
			x = 1;
	}
	int mobchip::moveX(double speed) {
		return x = speed;
	}
	int mobchip::moveY(double speed) {
		return y = speed;
	}
	void mobchip::mobAnime() {
		movecount++;
		if (movecount % 30 != 0)
			movecool++;
		if ((GetRand(2) * GetRand(5) * movecool) % 64 >= 32)
			moveflug = true;
		else
			moveflug = false;
		if (moveflug == true) {
			if (movecount % 64 == 0)
				muki = GetRand(3);

			//UP
			if (muki == 0) {
				_0_1_2_1_0_(handlex);
				handley = 3;
			}
			//DOWN
			if (muki == 1) {
				_0_1_2_1_0_(handlex);
				handley = 0;
			}
			//LEFT
			if (muki == 2) {
				_0_1_2_1_0_(handlex);
				handley = 1;
			}
			//RIGHT
			if (muki == 3) {
				_0_1_2_1_0_(handlex);
				handley = 2;
			}
			mobmove();
		}
	}
	void mobchip::mobmove() {
		if (muki == 0) {
			if (y > 0)
				y -= 1;
		}
		//DOWN
		if (muki == 1) {
			y += 1;
		}
		//LEFT
		if (muki == 2) {
			if (x > 0)
				x -= 1;
		}
		//RIGHT
		if (muki == 3) {
			x += 1;
		}
	}
	void mobchip::mobDraw() {
		DrawRectGraph(mapd.x + x, mapd.y + y, 32 * handlex, 64 * handley, 32, 64, img, true, false);
	}


	class playerchip {
	public:
		float x, y;//int ならビット調の動き、floatならするする動く
		int img = -1;

		playerchip();


		void reset();

		void charaAnime();
		void charaTrun();
		void charaDraw();

		void moveX(double disp);//speed 移動値
		void moveY(double disp);//speed 移動値
		int moveX2(double speed);//直接ｘに入れる
		int moveY2(double speed);//直接yに入れる
		void castX();
		void castY();
		bool getmuki(int muki);
		void changemuki(int muki);

		~playerchip();

	private:

		void _0_1_2_1_0_(int& x);
		void counter() { count++; };
		double dispx, dispy;
		int count = 0;
		int handlex = 1;
		int handley = 0;
		int tcount = 0;
		bool trunflug = false;


	};
	playerchip chara;
	playerchip beforchara;
	playerchip schara;//start

	playerchip::playerchip() {
		img = -1;
		x = 0;
		y = 0;
		dispx = 0;
		dispy = 0;
		count = 0;
		handlex = 1;
		handley = 0;
		tcount = 0;
		trunflug = false;

		reset();
	}
	playerchip::~playerchip() {
		DeleteGraph(img);
	}
	void playerchip::reset() {
		dispx = 0;
		dispy = 0;
		count = 0;
		handlex = 1;
		handley = 0;
		tcount = 0;
		trunflug = false;
		x = 0;
		y = 0;
	}
	void playerchip::_0_1_2_1_0_(int& x) {
		counter();
		x = count / 13 % 4;
		if (x == 3)
			x = 1;

	}
	void playerchip::moveX(double disp) {
		dispx += disp;
	}
	void playerchip::moveY(double disp) {
		dispy += disp;
	}
	int playerchip::moveX2(double speed) {
		return x = speed;
	}
	int playerchip::moveY2(double speed) {
		return y = speed;
	}
	void playerchip::castX() {
		x = dispx;
	}
	void playerchip::castY() {
		y = dispy;
	}
	//KEY_INPUT_???(方向）
	bool playerchip::getmuki(int muki) {
		switch (muki) {
		case KEY_INPUT_UP:
			if (handlex == 0 && handley == 3 ||
				handlex == 1 && handley == 3 ||
				handlex == 2 && handley == 3 ||

				handlex == 3 && handley == 3 ||
				handlex == 4 && handley == 3 ||
				handlex == 5 && handley == 3 ||

				handlex == 3 && handley == 2 ||
				handlex == 4 && handley == 2 ||
				handlex == 5 && handley == 2) return true;
			break;
		case KEY_INPUT_DOWN:
			if (handlex == 0 && handley == 0 ||
				handlex == 1 && handley == 0 ||
				handlex == 2 && handley == 0 ||

				handlex == 3 && handley == 0 ||
				handlex == 4 && handley == 0 ||
				handlex == 5 && handley == 0 ||

				handlex == 3 && handley == 1 ||
				handlex == 4 && handley == 1 ||
				handlex == 5 && handley == 1) return true;
			break;
		case KEY_INPUT_LEFT:
			if (handlex == 3 && handley == 0 ||
				handlex == 4 && handley == 0 ||
				handlex == 5 && handley == 0 ||

				handlex == 0 && handley == 1 ||
				handlex == 1 && handley == 1 ||
				handlex == 2 && handley == 1 ||

				handlex == 3 && handley == 2 ||
				handlex == 4 && handley == 2 ||
				handlex == 5 && handley == 2) return true;
			break;
		case KEY_INPUT_RIGHT:
			if (handlex == 3 && handley == 1 ||
				handlex == 4 && handley == 1 ||
				handlex == 5 && handley == 1 ||

				handlex == 0 && handley == 2 ||
				handlex == 1 && handley == 2 ||
				handlex == 2 && handley == 2 ||

				handlex == 3 && handley == 3 ||
				handlex == 4 && handley == 3 ||
				handlex == 5 && handley == 3) return true;
			break;
		default:
			return false;
		}

		return false;
	}
	void playerchip::changemuki(int muki) {
		switch (muki) {
		case KEY_INPUT_UP:
			handlex = 0;
			handley = 3;
			break;

		case KEY_INPUT_LEFT:
			handlex = 3;
			handley = 0;
			break;
		case KEY_INPUT_RIGHT:
			handlex = 3;
			handley = 1;
			break;

		case KEY_INPUT_DOWN:
		default:
			handlex = 0;
			handley = 0;
			break;
		}
	}
	void playerchip::charaAnime() {
		if ((CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP)) || (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_W)) ||
			(CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN)) || (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_S)) ||
			(CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP)) || (CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_W)) ||
			(CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN)) || (CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_S))
			) {

			if ((CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP)) ||
				(CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_W))
				) {
				_0_1_2_1_0_(handlex);
				handlex += 3;
				handley = 2;
			}
			else if ((CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN)) ||
				(CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_S))
				) {
				_0_1_2_1_0_(handlex);
				handlex += 3;
				handley = 0;
			}
			else if ((CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP)) ||
				(CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_W))
				) {
				_0_1_2_1_0_(handlex);
				handlex += 3;
				handley = 3;
			}
			else if ((CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN)) ||
				(CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_S))
				) {
				_0_1_2_1_0_(handlex);
				handlex += 3;
				handley = 1;
			}
		}
		else {
			if (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_W)) {

				_0_1_2_1_0_(handlex);
				handley = 3;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_S)) {
				_0_1_2_1_0_(handlex);
				handley = 0;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_A)) {
				_0_1_2_1_0_(handlex);
				handley = 1;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || CheckHitKey(KEY_INPUT_D)) {
				_0_1_2_1_0_(handlex);
				handley = 2;
			}
		}
	}
	void playerchip::charaTrun() {

		if (CheckHitKey(KEY_INPUT_T) && trunflug == false) {
			handlex = 1;
			handley = 0;
			tcount = 0;
			trunflug = true;
		}

		if (tcount >= 66 && CheckHitKey(KEY_INPUT_T) == 0) {
			trunflug = false;
			tcount = 0;
			handlex = 1;
			handley = 0;
		}
		if (tcount >= 66) {
			tcount = 0;
		}

		if (trunflug == true) {
			tcount++;
			if (tcount >= 1 && tcount <= 5) {
				handlex = 1;
				handley = 0;

			}
			else if (handlex == 1 && handley == 0 && tcount >= 2) {
				handlex = 0;
				handley = 0;

			}
			else if (handlex == 0 && handley == 0 && tcount >= 10) {
				handlex = 0;
				handley = 1;

			}
			else if (handlex == 0 && handley == 1 && tcount >= 18) {
				handlex = 3;
				handley = 2;

			}
			else if (handlex == 3 && handley == 2 && tcount >= 26) {
				handlex = 2;
				handley = 3;

			}
			else if (handlex == 2 && handley == 3 && tcount >= 34) {
				handlex = 0;
				handley = 3;

			}
			else if (handlex == 0 && handley == 3 && tcount >= 42) {
				handlex = 5;
				handley = 3;

			}
			else if (handlex == 5 && handley == 3 && tcount >= 50) {
				handlex = 2;
				handley = 2;
			}
			else if (handlex == 2 && handley == 2 && tcount >= 58) {
				handlex = 5;
				handley = 1;

			}

		}

	}
	void playerchip::charaDraw() {
		DrawRectGraph(mapd.x + x, mapd.y + y, 32 * handlex, 64 * handley, 32, 64, img, true, false);
		//DrawFormatString(10, 10, GetColor(255, 255, 255), "%d %d", handlex, handley);
	}

}

//wstringをstringへ変換
std::string WStringToString(std::wstring oWString)
{
	// wstring → SJIS
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
		, -1, (char*)NULL, 0, NULL, NULL);
	// バッファの取得
	CHAR* cpMultiByte = new CHAR[iBufferSize];
	// wstring → SJIS
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
		, iBufferSize, NULL, NULL);
	// stringの生成
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	// バッファの破棄
	delete[] cpMultiByte;
	// 変換結果を返す
	return(oRet);
}
std::wstring StringToWString(std::string oString)
{
	//  SJIS→wstring
	std::wstring ws;
	int iBufferSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, oString.c_str()
		, -1, (wchar_t*)NULL, 0);

	// バッファの取得
	wchar_t* cpMultiByte = new wchar_t[iBufferSize];
	// wstring → SJIS
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpMultiByte
		, iBufferSize);
	// wstringの生成
	std::wstring oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	// バッファの破棄
	delete[] cpMultiByte;
	// 変換結果を返す
	return(oRet);
}

//タイトル表示
void title() {
	printfDx("\n\n\n\n\n\n");
	printfDx("                  CHINO QUEST\n");
	printfDx("                  PUSH ENTER\n");

	
	/*
	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < 10; ++i) {
			DeleteGraph(mob[i][j].img);
			mob[i][j].img = LoadGraph("mobs.png");
		}
	DeleteGraph(chara.img);
	chara.img = LoadGraph("chara.png");
	*/
}


//ステータス表示
void disp()
{
	if (mode == enum_title) {
		title();
	}
	else if (mode == enum_field) {
		yuka();
		if (field == house_o ||
			field == house_m ||
			field == house_n ||
			field == house_b ||
			field == house_v
			) {
			housekabe();
		}
		if (field == field_world) {
			world();
			gake();
		}
		if (field == field_normal) {
			siba();
			saku();
			doayane();
			sotoobject();
			//マップに置いたマークの位置にキャラ移動
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			for (int i = 0; i < y_max; i++) {
				for (int j = 0; j < x_max; j++) {
					if (map[i][j] == ',') {

						houses.DrawHouse(j * 32 + tempX, i * 32 + tempY,img,doaimg);
					}
					if (map[i][j] == ',') {
						houses.DrawHouse_yane(j * 32 + tempX, i * 32 + tempY,doaimg);
					}
				}
			}
		}
		if (field == field_cave) {
			incavekabe();
			incavelava();
			incavetenjou();
			animlight();
		}
		disp_inDraw();
		if (field == field_cave) {
			incavetenjou_2();
		}
		if (field == field_normal) {
			houseyane();
			//マップに置いたマークの位置にキャラ移動
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			for (int i = 0; i < y_max; i++) {
				for (int j = 0; j < x_max; j++) {
					if (map[i][j] == ',') {
						houses.DrawHouse_yane(j * 32 + tempX, i * 32 + tempY,doaimg);
					}

				}
			}
		}
		if (field == field_normal) {
			Wood();
		}
		//Field();
	}
	if (mapflug == true) {
		DrawBox(100, 100, 700, 500, GetColor(100, 100, 255), true);
		DrawBox(250, 250, 550, 350, GetColor(100, 255, 100), true);
		DrawFormatString(200, 200, GetColor(0, 0, 0), "マップの画面のつもり");
	}

	if (finventory == true) {
		DrawBox(150, 150, 650, 450, GetColor(0xde, 0xb0, 0x68), true);
		DrawFormatString(250, 250, GetColor(0, 0, 0), "これはインベントリ画面のつもり\n\n同じIキーで戻る");
	}


}
void move() {
	if (mode == enum_title && CheckHitKey(KEY_INPUT_RETURN))
		mode = enum_field;
	if (ugokistop == false)
		if (mode == enum_field) {
			chara.charaAnime();
			chara.charaTrun();

			for (int j = 0; j < 2; ++j)
				for (int i = 0; i < 10; ++i)
					mob[i][j].mobAnime();
		}

	//当たり判定本体（下とセット）
	if (cjudge == false)
		switch (field) {
		case field_normal:
			if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_RETURN)) {
				if (map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
					map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'o' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'o'
					) {

					field = house_o;
					cjudge = true;
					beforchara = chara;
					chara = schara;
					beformapd = mapd;
					mapd = smapd;
					sound_c[doa] = 0;
					if (++sound_c[doa] == 1)
						PlaySoundMem(sounds[doa], DX_PLAYTYPE_BACK);

				}

				if (map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'm' ||
					map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'm' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'm' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'm'
					) {
					field = house_m;
					cjudge = true;
					beforchara = chara;
					chara = schara;
					beformapd = mapd;
					mapd = smapd;
					sound_c[doa] = 0;
					if (++sound_c[doa] == 1)
						PlaySoundMem(sounds[doa], DX_PLAYTYPE_BACK);

				}
				if (map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'n' ||
					map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'n' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'n' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'n'
					) {
					field = house_n;
					cjudge = true;
					beforchara = chara;
					chara = schara;
					beformapd = mapd;
					mapd = smapd;
					sound_c[doa] = 0;
					if (++sound_c[doa] == 1)
						PlaySoundMem(sounds[doa], DX_PLAYTYPE_BACK);

				}
				if (map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'b' ||
					map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'b' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'b' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'b'
					) {
					field = house_b;
					cjudge = true;
					beforchara = chara;
					chara = schara;
					beformapd = mapd;
					mapd = smapd;
					sound_c[doa] = 0;
					if (++sound_c[doa] == 1)
						PlaySoundMem(sounds[doa], DX_PLAYTYPE_BACK);

				}
				if (map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'v' ||
					map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'v' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'v' ||
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'v'
					) {
					field = house_v;
					cjudge = true;
					beforchara = chara;
					chara = schara;
					beformapd = mapd;
					mapd = smapd;
					sound_c[doa] = 0;
					if (++sound_c[doa] == 1)
						PlaySoundMem(sounds[doa], DX_PLAYTYPE_BACK);

				}
			}
			if (chara.y > ((y_max - 2) - 1) * 32) {
				beformapd = mapd;
				beforchara = chara;
				chara = schara;
				mapd = smapd;
				//マップに置いたマークの位置にキャラ移動
				for (int i = 0; i < y_max; i++) {
					for (int j = 0; j < x_max; j++) {
						if (map_world[i][j] == 'h') {
							chara.moveX2(j * 32);
							chara.moveY2(i * 32);
						}

					}
				}

				field = field_world;

			}
			break;
		case house_o:
			if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'o'
				) {
				if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_RETURN)) {
					field = field_normal;
					cjudge = true;
					chara = beforchara;
					mapd = beformapd;
				}
			}
			break;
		case house_m:
			if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'o'
				) {
				if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_RETURN)) {
					field = field_normal;
					cjudge = true;
					chara = beforchara;
					mapd = beformapd;
				}
			}
			break;
		case house_n:
			if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'o'
				) {
				if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_RETURN)) {
					field = field_normal;
					cjudge = true;
					chara = beforchara;
					mapd = beformapd;
				}
			}
			break;
		case house_b:
			if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'o'
				) {
				if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_RETURN)) {
					field = field_normal;
					cjudge = true;
					chara = beforchara;
					mapd = beformapd;
				}
			}
			break;
		case house_v:
			if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'o' ||
				map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'o'
				) {
				if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_RETURN)) {
					field = field_normal;
					cjudge = true;
					chara = beforchara;
					mapd = beformapd;

				}
			}
			break;
		case under:
			break;
		case field_world:
			if (map_world[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'h' ||
				map_world[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] == 'h' ||
				map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] == 'h' ||
				map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] == 'h'
				) {
				chara = schara;
				mapd = smapd;
				/*chara = beforchara;
				mapd = beformapd;*/
				//マップに置いたマークの位置にキャラ移動
				for (int i = 0; i < y_max; i++) {
					for (int j = 0; j < x_max; j++) {
						if (map[i][j] == 't') {
							chara.moveX2(j * 32);
							chara.moveY2((i + 1) * 32);
							chara.changemuki(KEY_INPUT_UP);
							if (chara.y >= 300 && chara.y <= y_max * 32 - 300)
								mapd.y = (i * 32 - 300) * -1;
							if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
								mapd.x = (j * 32 - 400) * -1;
							if (chara.y >= y_max * 32 - 300)
								mapd.y = (y_max * 32 - 300 - 300) * -1;
						}
					}
				}
				field = field_normal;
				if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_RETURN)) {

				}
			}
			else
				if (
					map_world[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'u' ||
					map_world[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'n' ||
					map_world[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'm' ||
					map_world[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] == 'o'
					) {

					chara = schara;
					mapd = smapd;
					for (int i = 0; i < y_max; i++) {
						for (int j = 0; j < x_max; j++) {
							if (map_cave[i][j] == 't') {
								chara.moveX2(j * 32);
								chara.moveY2((i + 1) * 32);
								chara.changemuki(KEY_INPUT_UP);
								if (chara.y >= 300 && chara.y <= y_max * 32 - 300)
									mapd.y = (i * 32 - 300) * -1;
								if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
									mapd.x = (j * 32 - 400) * -1;
								if (chara.y >= y_max * 32 - 300)
									mapd.y = (y_max * 32 - 300 - 300) * -1;
							}
						}
					}
					/*for (int i = 0; i < y_max; i++) {
						for (int j = 0; j < x_max; j++) {
							if (map_cave[i][j] == 't') {
								chara.moveX2(j * 32);
								chara.moveY2((i + 1) * 32);
								if (chara.y >= 300 && chara.y <= y_max * 32 - 300)
									mapd.y = (i * 32 - 300) * -1;
								if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
									mapd.x = (j * 32 - 400) * -1;
								if (chara.y >= y_max * 32 - 300)
									mapd.y = (y_max * 32 - 300 - 300) * -1;
							}
						}
					}*/
					field = field_cave;
				}

			break;

		case field_cave:
			if (chara.y > ((y_max - 2) - 1) * 32) {
				beformapd = mapd;
				beforchara = chara;
				chara = schara;
				mapd = smapd;
				//マップに置いたマークの位置にキャラ移動
				for (int i = 0; i < y_max; i++) {
					for (int j = 0; j < x_max; j++) {
						if (map_world[i][j] == 'm') {
							chara.moveX2(j * 32);
							chara.moveY2(i * 32);
						}

					}
				}

				field = field_world;

			}
			break;
		}
	//階段ループ見逃し用（上とセット）
	switch (field) {
	case field_normal:
		if (map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'o' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'o' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'm' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'm' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'm' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'm' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'n' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'n' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'n' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'n' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'b' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'b' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'b' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'b' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'v' &&
			map[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'v' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'v' &&
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'v'
			)cjudge = false;
		break;
	case house_o:
		if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'o'

			)
			cjudge = false;

		break;
	case house_m:
		if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'o'
			)
			cjudge = false;

		break;
	case house_n:
		if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'o'
			)
			cjudge = false;

		break;
	case house_b:
		if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'o'
			)
			cjudge = false;

		break;
	case house_v:
		if (map_house[(int)(chara.y) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x) / 32] != 'o' &&
			map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31) / 32] != 'o'
			)
			cjudge = false;

		break;

	case under:
		break;
	case field_cave:
		break;
	}
	//移動系switch文
	if (ugokistop == false)
		switch (field) {
		case field_normal:
			if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
				if (chara.y > 0 &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != ' ' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != ' ' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'e' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'e' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'd' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'd' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'z' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'z' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != '1' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != '1' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'x' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'x' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 's' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 's' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'g' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'g' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'y' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'y' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'f' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'f' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'r' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'r' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'Z' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'Z' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'X' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'X' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] != 'C' &&
					map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] != 'C'
					) {
					chara.y -= speed;
					if (chara.y >= 300 && chara.y <= y_max * 32 - 300)
						mapd.y += speed;
				}

			if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
				if (chara.y <= (y_max - 2) * 32 &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != ' ' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != ' ' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'e' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'e' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'd' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'd' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'z' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'z' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '1' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '1' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '2' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '2' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'x' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'x' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 's' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 's' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'g' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'g' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'y' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'y' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'f' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'f' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'r' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'r' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'E' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'E' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'W' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'W' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'Q' &&
					map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'Q'
					) {
					chara.y += speed;


					if (chara.y >= 300 && chara.y <= y_max * 32 - 300)
						mapd.y -= speed;
				}
			if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
				if (chara.x > 0 &&
					/*map[(int)(chara.y)/32][(int)(chara.x - speed)/32]!=' '&&*/
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != ' ' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != ' ' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'e' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'e' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'd' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'd' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'z' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'z' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != '1' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != '1' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != '2' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != '2' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'x' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'x' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 's' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 's' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'g' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'g' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'y' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'y' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'f' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'f' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'r' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'r' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'C' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'C' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'D' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'D' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'E' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'E'
					) {
					chara.x -= speed;
					if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
						mapd.x += speed;
				}
			if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) {
				if (chara.x <= (x_max - 1) * 32 &&
					/*map[(int)(chara.y) / 32][(int)(chara.x + 31 + speed) / 32] != ' ' &&*/
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != ' ' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != ' ' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'e' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'e' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'd' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'd' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'z' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'z' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '1' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '1' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '2' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '2' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'x' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'x' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 's' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 's' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'g' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'g' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'y' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'y' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'f' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'f' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'r' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'r' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'Z' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'Z' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'A' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'A' &&
					map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'Q' &&
					map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'Q'
					) {
					chara.x += speed;
					if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
						mapd.x -= speed;
				}
			}
			break;
		case house_o:
		case house_m:
		case house_n:
		case house_b:
		case house_v:
			if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
				if (chara.y - speed > 0 &&
					map_house[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != ' ' &&
					map_house[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != ' '
					) {
					chara.y -= speed;
					if (chara.y >= 300 && chara.y <= y_max * 32 - 300)
						mapd.y += speed;
				}
			if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
				if (chara.y <= (y_max - 2) * 32 &&
					map_house[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != ' ' &&
					map_house[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != ' '
					) {
					chara.y += speed;


					if (chara.y <= y_max * 32 - 300 && chara.y >= 300)
						mapd.y -= speed;
				}
			if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
				if (chara.x > 0 &&
					map_house[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != ' ' &&
					map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != ' '
					) {
					chara.x -= speed;
					if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
						mapd.x += speed;
				}
			if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
				if (chara.x <= (x_max - 1) * 32 &&
					map_house[(int)(chara.y) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != ' ' &&
					map_house[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != ' '
					) {
					chara.x += speed;
					if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
						mapd.x -= speed;
				}
			break;
		case field_world:
			if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
				if (chara.y > 0 &&
					map_world[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != ' ' &&
					map_world[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != ' ' &&
					map_world[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != '0' &&
					map_world[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != '0' &&
					map_world[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != '9' &&
					map_world[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != '9' &&
					map_world[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != '-' &&
					map_world[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != '-'
					) {
					chara.y -= speed;
				}
			if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
				if (chara.y <= 600 - 64 &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != ' ' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != ' ' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '0' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '0' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '9' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '9' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '0' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '0' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '-' &&
					map_world[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '-'
					) {
					chara.y += speed;
				}
			if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
				if (chara.x > 0 &&
					map_world[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != ' ' &&
					map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != ' ' &&
					map_world[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != '0' &&
					map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != '0' &&
					map_world[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != '9' &&
					map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != '9' &&
					map_world[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != '-' &&
					map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != '-'
					) {
					chara.x -= speed;
				}
			if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
				if (chara.x <= 800 - 32 &&
					map_world[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != ' ' &&
					map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != ' ' &&
					map_world[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '0' &&
					map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '0' &&
					map_world[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '9' &&
					map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '9' &&
					map_world[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '-' &&
					map_world[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '-'
					) {
					chara.x += speed;
				}
			break;
		case field_cave:
			if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
				if (chara.y > 0 &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != ' ' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != ' ' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != '_' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != '_' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != '>' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != '>' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != '<' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != '<' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x) / 32] != '?' &&
					map_cave[(int)(chara.y - speed - 3) / 32 + 1][(int)(chara.x + 31) / 32] != '?'
					) {
					chara.y -= speed;
					if (chara.y >= 300 && chara.y <= y_max * 32 - 300)
						mapd.y += speed;
				}
			if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
				if (chara.y <= (y_max - 2) * 32 &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != ' ' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != ' ' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '?' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '?' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '_' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '_' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != '>' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != '>' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'f' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'f' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'x' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'x' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'd' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'd' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] != 'z' &&
					map_cave[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] != 'z'
					) {
					chara.y += speed;
					if (chara.y <= y_max * 32 - 300 && chara.y >= 300)
						mapd.y -= speed;
				}
			if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
				if (chara.x > 0 &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != ' ' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != ' ' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'z' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'z' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'x' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'x' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != '_' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != '_' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != '?' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != '?' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != '*' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != '*' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != ']' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != ']' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] != 'b' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] != 'b'
					) {
					chara.x -= speed;
					if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
						mapd.x += speed;
				}
			if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
				if (chara.x <= (x_max - 1) * 32 &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != ' ' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != ' ' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '_' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '_' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '>' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '>' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '?' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '?' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'f' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'f' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'd' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'd' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != '<' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != '<' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'L' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'L' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 's' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 's' &&
					map_cave[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] != 'j' &&
					map_cave[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] != 'j'
					) {
					chara.x += speed;
					if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
						mapd.x -= speed;
				}
			break;
		}

	if (field == field_normal) {


		if (CheckHitKey(KEY_INPUT_E) && keystop == false) {
			keystop = true;
			mozicount = 0;
			ckaiwa++;
		}
		if (ckaiwa % 2 == 1) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 2; j++) {
					if (mob[i][j].x + 32 >= chara.x &&
						mob[i][j].x <= chara.x + 32 &&
						mob[i][j].y + 64 >= chara.y &&
						mob[i][j].y <= chara.y + 64
						) {
						mobmesse = "会話だよエンターキーで次を読みたい";
						moziflug = false;
						kaiwaflug = true;
						ugokistop = true;
					}

				}
			}

			if (collition('Q', KEY_INPUT_DOWN) == true && chara.getmuki(KEY_INPUT_DOWN) == true ||
				collition('W', KEY_INPUT_DOWN) == true && chara.getmuki(KEY_INPUT_DOWN) == true ||
				collition('E', KEY_INPUT_DOWN) == true && chara.getmuki(KEY_INPUT_DOWN) == true ||
				collition('C', KEY_INPUT_UP) == true && chara.getmuki(KEY_INPUT_UP) == true ||
				collition('X', KEY_INPUT_UP) == true && chara.getmuki(KEY_INPUT_UP) == true ||
				collition('Z', KEY_INPUT_UP) == true && chara.getmuki(KEY_INPUT_UP) == true ||
				collition('E', KEY_INPUT_LEFT) == true && chara.getmuki(KEY_INPUT_LEFT) == true ||
				collition('D', KEY_INPUT_LEFT) == true && chara.getmuki(KEY_INPUT_LEFT) == true ||
				collition('C', KEY_INPUT_LEFT) == true && chara.getmuki(KEY_INPUT_LEFT) == true ||
				collition('Q', KEY_INPUT_RIGHT) == true && chara.getmuki(KEY_INPUT_RIGHT) == true ||
				collition('A', KEY_INPUT_RIGHT) == true && chara.getmuki(KEY_INPUT_RIGHT) == true ||
				collition('Z', KEY_INPUT_RIGHT) == true && chara.getmuki(KEY_INPUT_RIGHT) == true
				) {
				mobmesse = "これは噴水だ\n　この画像を入れるために文字を何回打ったのだろう？";
				moziflug = false;
				kaiwaflug = true;
				ugokistop = true;
			}

		}
		else {
			mobmesse = "";
			moziflug = false;
			kaiwaflug = false;
			ugokistop = false;
			ckaiwa = 0;
		}


		//Iキーを押したときにインベントリ画面が表示される処理を入れる

		if (CheckHitKey(KEY_INPUT_I) && keystop == false &&
			kaiwaflug == false
			) {
			keystop = true;
			ugokistop = true;
			cinventory++;
			if (cinventory % 2 == 0)ugokistop = false;
		}
		//Mキーでマップの処理
		if (CheckHitKey(KEY_INPUT_M) && keystop == false &&
			kaiwaflug == false
			) {
			keystop = true;
			ugokistop = true;
			cmapflug++;
			if (cmapflug % 2 == 0)ugokistop = false;
		}


	}
	if (cinventory % 2 == 1) {
		finventory = true;
	}
	else finventory = false;

	if (cmapflug % 2 == 1) {
		mapflug = true;
	}
	else mapflug = false;

	mozicount++;
	mozisize = mobmesse.size() / 2;
	if (mozicount / 3 >= mozisize) {
		moziflug = true;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) && keystop == false) {
		if (moziflug == false) {
			mozicount = mozisize * 3;
		}
		if (moziflug == true && finventory == false) {
			mozicount = 0;
			//会話の終了に入れるやつ
			mobmesse = "";
			kaiwaflug = false;
			ugokistop = false;
			moziflug = false;
			ckaiwa = 0;
		}
		keystop = true;
	}
	if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
		speed = 4;
	else speed = 1;

	if (CheckHitKey(KEY_INPUT_RETURN) == 0 &&
		CheckHitKey(KEY_INPUT_E) == 0 &&
		CheckHitKey(KEY_INPUT_I) == 0 &&
		CheckHitKey(KEY_INPUT_M) == 0

		)
		keystop = false;

	//会話のメッセージウィンドウ
	if (kaiwaflug == true) {
		DrawBox(50, 450, 750, 550, GetColor(0, 0, 0), true);
		int rt = 5;//rinzitiisaku
		DrawBox(50 + rt, 450 + rt, 750 - rt, 550 - rt, GetColor(255, 255, 255), false);
	}

	//メッセージウィンドウにテキストを表示する
	std::wstring message_e = StringToWString(mobmesse);
	std::string disp_message_e = WStringToString(message_e.substr(0, mozicount / 3));
	DrawFormatString(200, 490, GetColor(255, 255, 255), disp_message_e.c_str());
	//DrawFormatString(200,250,GetColor(255,255,255), disp_message_e.c_str());
}

void disp_inDraw() {
	//if (field == field_world)
		//DrawGraph(0, 0, LoadGraph("world.png"), true);
	if (field == field_normal)
		for (int j = 0; j < 2; ++j)
			for (int i = 0; i < 10; ++i)
				mob[i][j].mobDraw();

	chara.charaDraw();

	if (field == field_world) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawExtendGraph(kumoidou.x, kumoidou.y, kumoidou.x + 800, kumoidou.y + 600, kumoimg, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		kumoidou.x++;
		kumoidou.y--;
		if (kumoidou.x >= 800)
			kumoidou.x = -800;
		if (kumoidou.y <= -600)
			kumoidou.y = 600;
	}
}
void syousaidraw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawFormatString(5 - 1, 600 - 20 - 1, GetColor(255, 255, 255), musictext.c_str());
	DrawFormatString(5 + 1, 600 - 20 + 1, GetColor(255, 255, 255), musictext.c_str());
	DrawFormatString(5 - 1, 600 - 20 + 1, GetColor(255, 255, 255), musictext.c_str());
	DrawFormatString(5 + 1, 600 - 20 - 1, GetColor(255, 255, 255), musictext.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawFormatString(5 - 1, 600 - 20 - 1, GetColor(255, 255, 255), musictext.c_str());
	DrawFormatString(5 + 1, 600 - 20 + 1, GetColor(255, 255, 255), musictext.c_str());
	DrawFormatString(5 - 1, 600 - 20 + 1, GetColor(255, 255, 255), musictext.c_str());
	DrawFormatString(5 + 1, 600 - 20 - 1, GetColor(255, 255, 255), musictext.c_str());
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatString(5, 600 - 20, GetColor(0, 0, 0), musictext.c_str());
	SetFontSize(16);

	if (mode == enum_field && CheckHitKey(KEY_INPUT_SPACE)) {
		if (field == field_world) {
			yuka();
			world();
			gake();
			clsDx();
			clsDx();
			clsDx();
			clsDx();
			clsDx();
			clsDx();
			clsDx();
			clsDx();
			clsDx();//10
		}
	}
	if (mode == enum_field && field == field_cave) {
		if (CheckHitKey(KEY_INPUT_NUMPAD1)) {
			StopSoundMem(musics[music_cave]);
			music_c[music_cave] = 0;


			musictext = "♪　オーケストラ20 / 魔王魂 ";
			music_c[music_cave2]++;
			if (music_c[music_cave2] == 1)
				PlaySoundMem(musics[music_cave2], DX_PLAYTYPE_LOOP);
			if (music_c[music_cave2] >= 10)music_c[music_cave2] = 2;
		}
		else if (CheckHitKey(KEY_INPUT_NUMPAD2)) {

			StopSoundMem(musics[music_cave2]);
			music_c[music_cave2] = 0;


			musictext = "♪　オーケストラ17 / 魔王魂 ";
			music_c[music_cave]++;
			if (music_c[music_cave] == 1)
				PlaySoundMem(musics[music_cave], DX_PLAYTYPE_LOOP);
			if (music_c[music_cave] >= 10)music_c[music_cave] = 2;
		}
	}
}
void debugdraw() {
	printfDx("mode;%d", mode);
	printfDx("\n\ncjudge;%d", cjudge);
	printfDx("\nchara.x;%3.5f\nchara.y;%3.5f", chara.x / 32, chara.y / 32);
	printfDx("\nfield;%d", field);
	printfDx("\nmapd.x;%3.5f", mapd.x);
	printfDx("\nmapd.y;%3.5f", mapd.y);
	printfDx("\nmobx;%3.5f", mob[0][0].x / 32);
	printfDx("\nmoby;%3.5f", mob[0][0].y / 32);
	printfDx("\ncmapflug;%d", cmapflug);
	if (CheckHitKey(KEY_INPUT_SPACE))
		DrawBox(chara.x + mapd.x, chara.y + mapd.y, chara.x + 32 + mapd.x, chara.y + 32 + mapd.y, GetColor(255, 255, 255), false);
	if (CheckHitKey(KEY_INPUT_1)) {
		unsigned int alpha = (CheckHitKey(KEY_INPUT_2)) ? 200 : 100;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, LoadGraph("night.png"), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	SetFontSize(20);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawFormatString(520, 581, GetColor(255, 255, 255), "※ゲーム画面はイメージです。");
	DrawFormatString(518, 579, GetColor(255, 255, 255), "※ゲーム画面はイメージです。");
	DrawFormatString(518, 581, GetColor(255, 255, 255), "※ゲーム画面はイメージです。");
	DrawFormatString(520, 579, GetColor(255, 255, 255), "※ゲーム画面はイメージです。");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawFormatString(520, 581, GetColor(255, 255, 255), "※ゲーム画面はイメージです。");
	DrawFormatString(518, 579, GetColor(255, 255, 255), "※ゲーム画面はイメージです。");
	DrawFormatString(518, 581, GetColor(255, 255, 255), "※ゲーム画面はイメージです。");
	DrawFormatString(520, 579, GetColor(255, 255, 255), "※ゲーム画面はイメージです。");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatString(519, 580, GetColor(0, 0, 0), "※ゲーム画面はイメージです。");


}



void Wood() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				case 'l':
					chipNo = 8 * 4 + 1;
					break;
				case 'k':
					chipNo = 8 * 4 + 0;
					break;
				case 'i':
					chipNo = 8 * 2 + 0;
					break;
				case 'u':
					chipNo = 8 * 2 + 1;
					break;
				case 'p':
					chipNo = 8 * 3 + 1;
					break;
				case '@':
					chipNo = 8 * 1 + 0;
					break;
				case '^':
					chipNo = 8 * 1 + 1;
					break;
				case '[':
					chipNo = 8 * 3 + 0;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;
			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, midorichip[chipNo], true);
		}
	}
}
void yuka() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				default:
					chipNo = 8 * 1 + 0;
					break;
				}
				break;
			case house_o:
			case house_m:
			case house_n:
			case house_b:
			case house_v:
				switch (map_house[i][j]) {
				case ' ':
					chipNo = 0;
					break;
				case 'o':
					chipNo = 8 * 2 + 6;
					break;
				case 'w':
					chipNo = 8 * 4 + 0;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;
			case field_world:
				switch (map_world[i][j]) {
				case'w':
					chipNo = 8 * 1 + 0;
					break;
				case'1':
				case'2':
				case'3':
				case'4':
				case'5':
				case'6':
				case'7':
				case'8':
				case'9':
				case'0':
				case'-':
				case' ':
					chipNo = 8 * 3 + 6;
					break;

				default:
					chipNo = 8 * 1 + 0;
				}
				break;
			case field_cave:
				switch (map_cave[i][j])
				{
				case' ':
					chipNo = 0;
					break;
				default:
					chipNo = 9 * 1 + 4;
					break;
				}
				break;
			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, yukanochip[chipNo], true);
			/*if (field != field_cave) {
				DrawGraph(tempX + j * 32, tempY + i * 32, yukanochip[chipNo], true);
			}else{
				DrawExtendGraph(tempX + j * 32, tempY + i * 32, (tempX + j * 32) + 32, (tempY + i * 32) + 32, incave_kabechip[chipNo], true);
			}*/if (field == field_cave)
				DrawExtendGraph(tempX + j * 32, tempY + i * 32, (tempX + j * 32) + 32, (tempY + i * 32) + 32, incave_kabechip[chipNo], true);
		}
	}
}
void housekabe() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case house_o:
			case house_m:
			case house_n:
			case house_b:
			case house_v:
				switch (map_house[i][j]) {
				case ' ':
					chipNo = 7 * 11 + 1;
					break;
				}
				break;
			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, housekabechip[chipNo], true);
		}
	}
}
void doayane() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = 20*8+18 
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				case'm':
				case'n':
				case'o':
				case'v':
				case'b':
					chipNo = 8 * 3 + 6;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, houseyanechip[chipNo], true);
			if (map[i][j] == 'o' ||
				map[i][j] == 'v' ||
				map[i][j] == 'b' ||
				map[i][j] == 'n' ||
				map[i][j] == 'm'
				) {
				DrawGraph(tempX + j * 32, tempY + i * 32, houseyanechip[8 * 3 + 7], true);
			}
			if (map[i + 1][j] == 'o' ||
				map[i + 1][j] == 'v' ||
				map[i + 1][j] == 'b' ||
				map[i + 1][j] == 'n' ||
				map[i + 1][j] == 'm'
				) {
				DrawGraph(tempX + j * 32, tempY + i * 32, houseyanechip[8 * 2 + 7], true);
			}
		}
	}
}
void houseyane() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = 20*8+18 
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				case'h':
					chipNo = 8 * 9 + 0;
					break;
				case'y':
					chipNo = 8 * 10 + 0;
					break;
				case'g':
					chipNo = 8 * 11 + 0;
					break;

				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, houseyanechip[chipNo], true);

		}
	}
}
void kagubed() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, kagubedchip[chipNo], true);
		}
	}
}
void kagubook() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, kagubookchip[chipNo], true);
		}
	}
}
void sotoobject() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				case'Q':
					chipNo = 8 * 10 + 0;
					break;
				case'W':
					chipNo = 8 * 10 + 1;
					break;
				case'E':
					chipNo = 8 * 10 + 2;
					break;
				case'A':
					chipNo = 8 * 11 + 0;
					break;
				case'S':
					chipNo = 8 * 11 + 1;
					break;
				case'D':
					chipNo = 8 * 11 + 2;
					break;
				case'Z':
					chipNo = 8 * 12 + 0;
					break;
				case'X':
					chipNo = 8 * 12 + 1;
					break;
				case'C':
					chipNo = 8 * 12 + 2;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, sotoobjectchip[chipNo], true);
		}
	}
}
void kanban() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				case' ':
					chipNo = 7 * 1 + 1;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, kanbanchip[chipNo], true);
		}
	}
}
void hatake() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, hatakechip[chipNo], true);
		}
	}
}
void saku() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				case'1':
					chipNo = 8 * 1 + 2;
					break;
				case'2':
					chipNo = 8 * 1 + 3;
					break;
				case'3':
					chipNo = 8 * 2 + 2;
					break;
				case'4':
					chipNo = 8 * 2 + 3;
					break;
				case'z':
					chipNo = 8 * 1 + 0;
					break;
				case' ':
					chipNo = 8 * 2 + 0;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, sakuchip[chipNo], true);
		}
	}
}
void gake() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_world:
				switch (map_world[i][j])
				{
				case'1':
					chipNo = 8 * 1 + 0;
					break;
				case'2':
					chipNo = 8 * 1 + 1;
					break;
				case'3':
					chipNo = 8 * 1 + 2;
					break;
				case'4':
					chipNo = 8 * 2 + 2;
					break;
				case'5':
					chipNo = 8 * 3 + 2;
					break;
				case'6':
					chipNo = 8 * 3 + 1;
					break;
				case'7':
					chipNo = 8 * 3 + 0;
					break;
				case'8':
					chipNo = 8 * 2 + 0;
					break;
				case'9':
					chipNo = 8 * 5 + 0;
					break;
				case'0':
					chipNo = 8 * 5 + 1;
					break;
				case'-':
					chipNo = 8 * 5 + 2;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, gakechip[chipNo], true);
		}
	}
}
void siba() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_normal:
				switch (map[i][j])
				{
				case'8':
					chipNo = 8 * 0 + 5;
					break;
				case'9':
					chipNo = 8 * 0 + 6;
					break;
				case'0':
					chipNo = 8 * 0 + 7;
					break;
				case'5':
					chipNo = 8 * 1 + 5;
					break;
				case'6':
					chipNo = 8 * 1 + 6;
					break;
				case'7':
					chipNo = 8 * 1 + 7;
					break;
				case';':
					chipNo = 8 * 2 + 5;
					break;
				case':':
					chipNo = 8 * 2 + 6;
					break;
				case']':
					chipNo = 8 * 2 + 7;
					break;
				default:
					chipNo = 8 * 5 + 7;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			DrawGraph(tempX + j * 32, tempY + i * 32, sibachip[chipNo], true);
		}
	}
}
void world() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_world:
				switch (map_world[i][j])
				{
				case'w':
					chipNo = 8 * 0 + 0;
					break;
				case' ':
					chipNo = 8 * 0 + 0;
					break;
				case'm':
					chipNo = 8 * 1 + 3;
					break;
				case'o':
					chipNo = 8 * 1 + 4;
					break;
				case'u':
					chipNo = 8 * 1 + 5;
					break;
				case'n':
					chipNo = 8 * 1 + 6;
					break;
				case'F':
					chipNo = 8 * 1 + 2;
					break;
				case'f':
					chipNo = 8 * 1 + 1;
					break;
				case't':
					chipNo = 8 * 1 + 0;
					break;
				case'h':
					chipNo = 8 * 2 + 0;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			//DrawGraph(tempX + j * 32, tempY + i * 32, worldchip[chipNo], true);
			DrawExtendGraph(tempX + j * 32, tempY + i * 32, (tempX + j * 32) + 32, (tempY + i * 32) + 32, worldchip[chipNo], true);
		}
	}
}
void incavekabe() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_cave:
				switch (map_cave[i][j])
				{
					/*
						L+*}
						<>?_
					*/
				case'L':
					chipNo = 9 * 10 + 0;
					break;
				case'+':
					chipNo = 9 * 10 + 1;
					break;
				case'*':
					chipNo = 9 * 10 + 2;
					break;
				case'}':
					chipNo = 9 * 10 + 4;
					break;
				case'<':
					chipNo = 9 * 11 + 0;
					break;
				case'>':
					chipNo = 9 * 11 + 1;
					break;
				case'?':
					chipNo = 9 * 11 + 2;
					break;
				case'_':
					chipNo = 9 * 11 + 4;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			//DrawGraph(tempX + j * 32, tempY + i * 32, worldchip[chipNo], true);
			DrawExtendGraph(tempX + j * 32, tempY + i * 32, (tempX + j * 32) + 32, (tempY + i * 32) + 32, incave_kabechip[chipNo], true);
		}
	}
}
void incavetenjou() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_cave:
				switch (map_cave[i][j])
				{
					/*
					  asdfghjkl;:]
					  zxcvbnm,
					*/
				case'a':
					chipNo = 2 * 2 + 0;
				break; case's':
					chipNo = 2 * 3 + 0;
				break; case'd':
					chipNo = 2 * 4 + 0;
				break; case'f':
					chipNo = 2 * 5 + 0;
				break; case'g':
					chipNo = 2 * 6 + 0;
				break; case'h':
					chipNo = 2 * 7 + 0;
				break; case'j':
					chipNo = 2 * 8 + 0;
				break; case'k':
					chipNo = 2 * 9 + 0;
				break; case'l':
					chipNo = 2 * 10 + 0;
				break; case';':
					chipNo = 2 * 11 + 0;
				break; case':':
					chipNo = 2 * 2 + 1;
				break; case']':
					chipNo = 2 * 3 + 1;
				break; case'z':
					chipNo = 2 * 4 + 1;
				break; case'x':
					chipNo = 2 * 5 + 1;
				break; case'c':
					chipNo = 2 * 6 + 1;
				break; case'v':
					chipNo = 2 * 7 + 1;
				break; case'b':
					chipNo = 2 * 8 + 1;
				break; case'n':
					chipNo = 2 * 9 + 1;
				break; case'm':
					chipNo = 2 * 10 + 1;
				break; case',':
					chipNo = 2 * 11 + 1;
					break;
				default:
					chipNo = 2 * +0 + 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			//DrawGraph(tempX + j * 32, tempY + i * 32, worldchip[chipNo], true);
			DrawExtendGraph(tempX + j * 32, tempY + i * 32, (tempX + j * 32) + 32, (tempY + i * 32) + 32, incave_tenjouchip[chipNo], true);
		}
	}

}
void incavetenjou_2() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_cave:
				switch (map_cave[i][j])
				{
					/*
					  asdfghjkl;:]
					  zxcvbnm,
					*/
				case'a':
					chipNo = 2 * 2 + 0;
				break; case'g':
					chipNo = 2 * 6 + 0;
				break; case':':
					chipNo = 2 * 2 + 1;
				break; case'c':
					chipNo = 2 * 6 + 1;
					break;
				default:
					chipNo = 2 * +0 + 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			//DrawGraph(tempX + j * 32, tempY + i * 32, worldchip[chipNo], true);
			DrawExtendGraph(tempX + j * 32, tempY + i * 32, (tempX + j * 32) + 32, (tempY + i * 32) + 32, incave_tenjouchip[chipNo], true);
		}
	}

}

void incavelava() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_cave:
				switch (map_cave[i][j])
				{
				case'8':
					chipNo = 2 * 4 + 0;
					break;
				case'9':
					chipNo = 2 * 4 + 1;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			//DrawGraph(tempX + j * 32, tempY + i * 32, worldchip[chipNo], true);
			DrawExtendGraph(tempX + j * 32, tempY + i * 32, (tempX + j * 32) + 32, (tempY + i * 32) + 32, incave_lavachip[chipNo], true);
		}
	}
}
void animlight() {
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			//int chipNo = map[i][j] == 'w' ? 20*7+18 : 20*8+2;
			int chipNo = 0;
			switch (field) {
			case field_cave:
				switch (map_cave[i][j])
				{
				case'0':
					chipNo = 6 * 4 + 5;
					break;
				default:
					chipNo = 0;
					break;
				}
				break;

			}
			float tempX = ((int)(mapd.x * 10) / 10.0f);
			float tempY = ((int)(mapd.y * 10) / 10.0f);
			//DrawGraph(tempX + j * 32, tempY + i * 32, worldchip[chipNo], true);
			DrawExtendGraph(tempX + j * 32, tempY + i * 32, (tempX + j * 32) + 32, (tempY + i * 32) + 32, anim_lightchip[chipNo], true);
		}
	}
}



void Songs() {
	if (mode == enum_field)
		switch (field) {
		case field_normal:
			/*for (int i = 0; i < musicmax; i++) {
				StopSoundMem(musics[i]);
				music_c[i] = 0;
			}*/
			StopSoundMem(musics[music_world]);
			music_c[music_world] = 0;

			musictext = "♪　ファンタジー14 / 魔王魂";
			if (++music_c[music_normal] == 1)
				PlaySoundMem(musics[music_normal], DX_PLAYTYPE_LOOP);
			if (music_c[music_normal] >= 10)music_c[music_normal] = 2;

			if (CheckHitKey(KEY_INPUT_RETURN) == 0) {
				if (moziflug == false) {
					if (mozicount % 4 == 0) {
						PlaySoundMem(sounds[terotero], DX_PLAYTYPE_BACK);
					}
				}
			}

			break;
		case field_world:
			for (int i = 0; i < musicmax; i++) {
				if (music_world == i)continue;
				StopSoundMem(musics[i]);
				music_c[i] = 0;
			}

			musictext = "♪　Parade / しゃろう";
			music_c[music_world]++;
			if (music_c[music_world] == 1)
				PlaySoundMem(musics[music_world], DX_PLAYTYPE_LOOP);
			if (music_c[music_world] >= 10)music_c[music_world] = 2;
			break;
		case field_cave:
			StopSoundMem(musics[music_world]);
			music_c[music_world] = 0;


			musictext = "♪　オーケストラ17 / 魔王魂 ";
			music_c[music_cave]++;
			if (music_c[music_cave] == 1)
				PlaySoundMem(musics[music_cave], DX_PLAYTYPE_LOOP);
			if (music_c[music_cave] >= 10)music_c[music_cave] = 2;
			break;
		}
}
/// <summary>
/// 当たり判定
/// </summary>
/// <param name="muki">KEY_INPUT_???</param>
/// <returns></returns>
bool collition(char mono, int muki) {
	switch (muki) {
	case KEY_INPUT_UP:
		//up
		if (map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x) / 32] == mono ||
			map[(int)(chara.y - speed - 1) / 32 + 1][(int)(chara.x + 31) / 32] == mono
			) {
			return true;
		}
		break;
	case KEY_INPUT_DOWN://down
		if (map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x) / 32] == mono ||
			map[(int)(chara.y + 31 + speed) / 32 + 1][(int)(chara.x + 31) / 32] == mono
			) {
			return true;
		}
		break;
	case KEY_INPUT_LEFT://left
		if (map[(int)(chara.y + 31) / 32][(int)(chara.x - speed) / 32] == mono ||
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x - speed) / 32] == mono
			) {
			return true;
		}
		break;
	case KEY_INPUT_RIGHT://right
		if (map[(int)(chara.y + 31) / 32][(int)(chara.x + 31 + speed) / 32] == mono ||
			map[(int)(chara.y + 31) / 32 + 1][(int)(chara.x + 31 + speed) / 32] == mono) {
			return true;
		}
		break;
	default:
		return false;
		break;
	}

	return false;
}

void mapchipInit() {
	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < 10; ++i) {
			mob[i][j].reset();
			mob[i][j].img = LoadGraph("mobs.png");
			mob[i][j].moveX(400 + i * 5 * 32);
			mob[i][j].moveY(300 + j * 20 * 32);
		}


	for (int i = 0; i < musicmax; i++) {
		musics[i] = -1;
		music_c[i] = 0;
	}
	musics[music_normal] = LoadSoundMem("music/魔王魂  ファンタジー14.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, musics[music_normal]);
	musics[music_world] = LoadSoundMem("music/Parade.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, musics[music_world]);
	musics[music_cave] = LoadSoundMem("music/魔王魂  オーケストラ17.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, musics[music_cave2]);
	musics[music_cave2] = LoadSoundMem("music/魔王魂  オーケストラ20.mp3");
	ChangeVolumeSoundMem(255 * 70 / 100, musics[music_cave2]);
	musictext = "";//musictext = "♪　Parade / しゃろう";
	for (int i = 0; i < soundmax; i++) {
		sounds[i] = -1;
		sound_c[i] = 0;
	}
	sounds[doa] = LoadSoundMem("music/ドアを開ける1.mp3");
	sounds[terotero] = LoadSoundMem("music/魔王魂 効果音 システム41.mp3");





	chara.reset();
	chara.img = LoadGraph("chara.png");
	chara.moveX2(400);
	chara.moveY2(300);
	schara = chara;
	smapd = mapd;
	//画像データ読み込み
	LoadDivGraph("0726_chip.png", 8 * 54, 8, 54, 32, 32, MapChip);
	LoadDivGraph("chip/chip_bees.png", 8 * 6, 8, 6, 32, 32, yukanochip);
	LoadDivGraph("chip/chip_midorikei.png", 8 * 9, 8, 9, 32, 32, midorichip);
	LoadDivGraph("chip/chip_house.png", 7 * 25, 7, 25, 32, 32, housekabechip);
	LoadDivGraph("chip/chip_house_sousyoku.png", 8 * 18, 8, 18, 32, 32, houseyanechip);
	LoadDivGraph("chip/chip_kagu.png", 8 * 19, 8, 19, 32, 32, kagubedchip);
	LoadDivGraph("chip/chip_kagu_2.png", 8 * 15, 8, 15, 32, 32, kagubookchip);
	LoadDivGraph("chip/chip_gaisousyoku.png", 8 * 13, 8, 13, 32, 32, sotoobjectchip);
	LoadDivGraph("chip/chip_kanban.png", 7 * 3, 7, 3, 32, 32, kanbanchip);
	LoadDivGraph("chip/chip_nougyou.png", 8 * 4, 8, 4, 32, 32, hatakechip);
	LoadDivGraph("chip/chip_saku.png", 8 * 7, 8, 7, 32, 32, sakuchip);
	LoadDivGraph("chip/chip_cave.png", 8 * 11, 8, 11, 32, 32, gakechip);
	LoadDivGraph("chip/chip_siba.png", 8 * 6, 8, 6, 32, 32, sibachip);
	LoadDivGraph("chip/chip_world.png", 8 * 4, 8, 4, 16, 16, worldchip);
	LoadDivGraph("chip/incave_kabe.png", 9 * 34, 9, 34, 16, 16, incave_kabechip);
	LoadDivGraph("chip/incave_tenjou.png", 2 * 12, 2, 12, 16, 16, incave_tenjouchip);
	LoadDivGraph("chip/incave_lava.png", 2 * 12, 2, 12, 8, 8, incave_lavachip);
	LoadDivGraph("chip/anim_light.png", 6 * 5, 6, 5, 16, 16, anim_lightchip);

	LoadDivGraph("chip/chip_house_sousyoku.png", 8 * 18, 8, 18, 32, 32, doaimg);
	LoadDivGraph("chip/chip_house.png", 7 * 25, 7, 25, 32, 32, img);


	kumoimg = LoadGraph("chip/kumo.png");

	Player = LoadGraph("chino.png");

	//マップに置いたマークの位置にキャラ移動
	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			if (map[i][j] == 'c') {
				chara.moveX2(j * 32);
				chara.moveY2((i + 1) * 32);
				if (chara.y >= 300 && chara.y <= y_max * 32 - 300)
					mapd.y = (i * 32 - 300) * -1;
				if (chara.x <= x_max * 32 - 400 && chara.x >= 400)
					mapd.x = (j * 32 - 400) * -1;
			}

		}
	}

	houses.housedrawInit();
}
void mapchipUpdate(){
	
	DeleteGraph(chara.img);
	chara.img = LoadGraph("chara.png");
	
	Songs();
	move();

	}
void mapchipDraw()	{
	disp();
	syousaidraw();
	houses.~housedraw();
	}
void mapchipDelete(){

	for (int i = 0; i < 8 * 54; i++)
		DeleteGraph(MapChip[i]);
	for (int i = 0; i < 8 * 6; i++) {
		DeleteGraph(yukanochip[i]);
		DeleteGraph(sibachip[i]);
	}
	for (int i = 0; i < 8 * 6; i++)
		DeleteGraph(midorichip[i]);
	for (int i = 0; i < 7 * 25; i++) {
		DeleteGraph(housekabechip[i]);
		DeleteGraph(img[i]);
	}
	for (int i = 0; i < 8 * 18; i++) {
		DeleteGraph(houseyanechip[i]);
		DeleteGraph(doaimg[i]);
	}
	for (int i = 0; i < 8 * 19; i++)
		DeleteGraph(kagubedchip[i]);
	for (int i = 0; i < 8 * 15; i++)
		DeleteGraph(kagubookchip[i]);
	for (int i = 0; i < 8 * 13; i++)
		DeleteGraph(sotoobjectchip[i]);
	for (int i = 0; i < 7 * 3; i++)
		DeleteGraph(kanbanchip[i]);
	for (int i = 0; i < 8 * 4; i++) {
		DeleteGraph(hatakechip[i]);
		DeleteGraph(worldchip[i]);
	}
	for (int i = 0; i < 8 * 7; i++)
		DeleteGraph(sakuchip[i]);
	for (int i = 0; i < 8 * 10; i++)
		DeleteGraph(gakechip[i]);
	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < 10; ++i)
			DeleteGraph(mob[i][j].img);
	DeleteGraph(chara.img);
	DeleteGraph(kumoimg);
	DeleteGraph(Player);
	for (int i = 0; musicmax > i; i++)
		DeleteSoundMem(musics[i]);
	for (int i = 0; i < soundmax; i++)
		DeleteSoundMem(sounds[i]);
	for (int i = 0; i < 9 * 34; i++)
		DeleteGraph(incave_kabechip[i]);
	for (int i = 0; i < 2 * 12; i++)
		DeleteGraph(incave_tenjouchip[i]);
	for (int i = 0; i < 2 * 12; i++)
		DeleteGraph(incave_lavachip[i]);
	for (int i = 0; i < 6 * 5; i++)
		DeleteGraph(anim_lightchip[i]);

	}