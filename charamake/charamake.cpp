#include<Dxlib.h>
#include"charamake.h"
#include"sentaku.h"
#include"huku.h"
#include"charakuriplayerchip.h"
#include"doutai.h"
#include"me.h"
#include"maegami.h"
#include"yokogami.h"
#include"omake.h"
#include"tuikahuku.h"
#include"usirogami.h"
#include"tukegami.h"
#include"sousyoku.h"
#include"colors.h"

namespace {
	charakuriplayerchip chara;
	int bunki = 0;
	enum bunki {
		sentaku,
		hadacolor,
		huku,
		tuikahuku,
		me,
		maegami,
		usirogami,
		yokogami,
		tukegami,
		sousyoku,
		omake,

	};
	enum charaimgs {
		sitasousyokucharaimgs,
		sitatukegamicharaimgs,
		sitausirogamicharaimgs,
		sitatuikahukucharaimgs,
		doutaicharaimgs,
		hukucharaimgs,
		tuikahukucharaimgs,
		mecharaimgs,
		maegamicharaimgs,
		yokogamicharaimgs,
		usirogamicharaimgs,
		tukegamicharaimgs,
		sousyokucharaimgs,

		endimg
	};
	int charakuterimgs[endimg] = { -1 };
	int charakuterx = 0;
	int charakutery = 0;
	int r[endimg] = {},
		g[endimg] = {},
		b[endimg] = {};
	bool charakuteromakeflug = false;
	int charakuteromakeimg = -1;

	bool kakidasiflug = false;
	bool charaseisakuEndflug = false;

	bool keystop = false;
}
void charaseisakubunnkiGetkakidasiflug(bool flug) {
	kakidasiflug = flug;
}
bool charaseisakuReturnflug() {
	return charaseisakuEndflug;
}
int charaseisakubunnkigetimg(int num) {
	return charakuterimgs[num];
}
bool charaseisakubonnkiTuginopagehe() {
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		keystop = false;
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && keystop == false) {
		keystop = true;
	return sentakubacktorf();
	}
	return false;
}
void charakuterimgsUpdete() {
	//omakegetimg();は保留
	charakuterimgs[sousyokucharaimgs] = sousyokugetimg();
	charakuterimgs[tukegamicharaimgs] = tukegamigetimg();
	charakuterimgs[yokogamicharaimgs] = yokogamigetimg();
	charakuterimgs[usirogamicharaimgs] = usirogamigetimg();
	charakuterimgs[maegamicharaimgs] = maegamigetimg();
	charakuterimgs[mecharaimgs] = megetimg();
	charakuterimgs[tuikahukucharaimgs] = tuikahukugetimg();
	charakuterimgs[hukucharaimgs] = hukugetimg();
	charakuterimgs[doutaicharaimgs] = doutaigetimg();
	charakuterimgs[sitatuikahukucharaimgs] = tuikahukugetsitaimg();
	charakuterimgs[sitausirogamicharaimgs] = usirogamigetsitaimg();
	charakuterimgs[sitatukegamicharaimgs] = tukegamigetsitaimg();
	charakuterimgs[sitasousyokucharaimgs] = sousyokugetsitaimg();
	charakuteromakeflug = omakegazotorf();
	charakuteromakeimg = omakegetimg();
}
void charakutercolorimg() {
	r[doutaicharaimgs] = doutaigetR();
	g[doutaicharaimgs] = doutaigetG();
	b[doutaicharaimgs] = doutaigetB();
	r[hukucharaimgs] = hukugetR();
	g[hukucharaimgs] = hukugetG();
	b[hukucharaimgs] = hukugetB();
	r[maegamicharaimgs] = maegamigetR();
	g[maegamicharaimgs] = maegamigetG();
	b[maegamicharaimgs] = maegamigetB();
	r[mecharaimgs] = megetR();
	g[mecharaimgs] = megetG();
	b[mecharaimgs] = megetB();
	r[sousyokucharaimgs] = sousyokugetR();
	g[sousyokucharaimgs] = sousyokugetG();
	b[sousyokucharaimgs] = sousyokugetB();
	r[sitasousyokucharaimgs] = sousyokugetR();
	g[sitasousyokucharaimgs] = sousyokugetG();
	b[sitasousyokucharaimgs] = sousyokugetB();
	r[tuikahukucharaimgs] = tuikahukugetR();
	g[tuikahukucharaimgs] = tuikahukugetG();
	b[tuikahukucharaimgs] = tuikahukugetB();
	r[sitatuikahukucharaimgs] = tuikahukugetR();
	g[sitatuikahukucharaimgs] = tuikahukugetG();
	b[sitatuikahukucharaimgs] = tuikahukugetB();
	r[tukegamicharaimgs] = tukegamigetR();
	g[tukegamicharaimgs] = tukegamigetG();
	b[tukegamicharaimgs] = tukegamigetB();
	r[sitatukegamicharaimgs] = tukegamigetR();
	g[sitatukegamicharaimgs] = tukegamigetG();
	b[sitatukegamicharaimgs] = tukegamigetB();
	r[usirogamicharaimgs] = usirogamigetR();
	g[usirogamicharaimgs] = usirogamigetG();
	b[usirogamicharaimgs] = usirogamigetB();
	r[sitausirogamicharaimgs] = usirogamigetR();
	g[sitausirogamicharaimgs] = usirogamigetG();
	b[sitausirogamicharaimgs] = usirogamigetB();
	r[yokogamicharaimgs] = yokogamigetR();
	g[yokogamicharaimgs] = yokogamigetG();
	b[yokogamicharaimgs] = yokogamigetB();
}
/*
真ん中、キャラ画像をどうやって共通させるか、
ページ移行はどうする（managerの中でする)

*/
void charaseisakuMove() {
	chara.charakuricharaAnime();
	chara.charakuricharaTrun();
	//クリックしたときの処理
	if ((GetMouseInput() & MOUSE_INPUT_LEFT )&&keystop==false) {
		keystop = true;
		switch (bunki) {
		case sentaku:
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 2; j++) {
					if (sentakumodechenge(i, j) && i == 0 && j == 0) {
						charakuterx = doutaigetx();
						charakutery = doutaigety();
						doutaiReset();
						bunki = hadacolor;
						//break;
					}
					else if (sentakumodechenge(i, j) && i == 1 && j == 0) {
						charakuterx = hukugetx();
						charakutery = hukugety();
						hukuReset();
						bunki = huku;
						//break;
					}
					else if (sentakumodechenge(i, j) && i == 2 && j == 0) {
						charakuterx = tuikahukugetx();
						charakutery = tuikahukugety();
						tuikahukuReset();
						bunki = tuikahuku;
					}
					else if (sentakumodechenge(i, j) && i == 3 && j == 0) {
						charakuterx = megetx();
						charakutery = megety();
						meReset();
						bunki = me;
					}
					else if (sentakumodechenge(i, j) && i == 4 && j == 0) {
						charakuterx = maegamigetx();
						charakutery = maegamigety();
						maegamiReset();
						bunki = maegami;
					}
					else if (sentakumodechenge(i, j) && i == 0 && j == 1) {
						charakuterx = usirogamigetx();
						charakutery = usirogamigety();
						usirogamiReset();
						bunki = usirogami;
					}
					else if (sentakumodechenge(i, j) && i == 1 && j == 1) {
						charakuterx = yokogamigetx();
						charakutery = yokogamigety();
						yokogamiReset();
						bunki = yokogami;
					}
					else if (sentakumodechenge(i, j) && i == 2 && j == 1) {
						charakuterx = tukegamigetx();
						charakutery = tukegamigety();
						tukegamiReset();
						bunki = tukegami;
					}
					else if (sentakumodechenge(i, j) && i == 3 && j == 1) {
						charakuterx = sousyokugetx();
						charakutery = sousyokugety();
						sousyokuReset();
						bunki = sousyoku;
					}
					else if (sentakumodechenge(i, j) && i == 4 && j == 1) {
						charakuterx = omakegetx();
						charakutery = omakegety();
						omakeReset();
						bunki = omake;
					}
					else {

					}
				}
			{
			bool flug = sentakubacktorf();
			if (flug) {
				kakidasiflug = true;
				bunki = sentaku;
				charaseisakuEndflug = true;
				flug = false;
			}
			else if (flug == false) {
				kakidasiflug = false;
			}
			}

			break;
		case hadacolor:
			if (doutaibacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case huku:

			if (hukubacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case tuikahuku:

			if (tuikahukubacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case me:

			if (mebacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case maegami:

			if (maegamibacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case usirogami:

			if (usirogamibacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case yokogami:

			if (yokogamibacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case tukegami:

			if (tukegamibacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case sousyoku:

			if (sousyokubacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		case omake:

			if (omakebacktorf()) {
				charakuterx = sentakugetx();
				charakutery = sentakugety();
				bunki = sentaku;
			}
			break;
		default:
			break;
		}
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		keystop = false;
	}
	//それぞれの動き処理まとめ
	switch (bunki) {
	case sentaku:
		sentakuMove();
		break;
	case hadacolor:
		doutaiMove();
		break;
	case huku:
		hukuMove();
		break;
	case tuikahuku:
		tuikahukuMove();
		break;
	case me:
		meMove();
		break;
	case maegami:
		maegamiMove();
		break;
	case usirogami:
		usirogamiMove();
		break;
	case yokogami:
		yokogamiMove();
		break;
	case tukegami:
		tukegamiMove();
		break;
	case sousyoku:
		sousyokuMove();
		break;
	case omake:
		omakeMove();
		break;
	}
}
void charaseisakuDraw() {
	if (kakidasiflug == true) {
		for (int i = 0; i < endimg; i++) {
			SetDrawBright(r[i], g[i], b[i]);
			DrawGraph(0, 0, charakuterimgs[i], true);
		}
		DrawGraph(0, 0, charakuteromakeimg, true);
		SaveDrawScreenToPNG(0, 0, 192, 256, "chara.png");
		SetDrawBright(255, 255, 255);
		DrawBox(0,0,800,600,GetColor(248, 184, 98),true);
	}

	if (charakuteromakeflug == false) {
		for (int i = 0; i < endimg; i++) {
			SetDrawBright(r[i], g[i], b[i]);
			DrawRectExtendGraph(charakuterx - 64, charakutery - 64 * 2, charakuterx + 64, charakutery + 64 * 2, 32 * chara.charakurigethandlex(), 64 * chara.charakurigethandley(), 32, 64, charakuterimgs[i], true);
			SetDrawBright(255, 255, 255);
		}
	}
	else {
		DrawRectExtendGraph(charakuterx - 64, charakutery - 64 * 2, charakuterx + 64, charakutery + 64 * 2, 32 * chara.charakurigethandlex(), 64 * chara.charakurigethandley(), 32, 64, charakuteromakeimg, true);
	}
	switch (bunki) {
	case sentaku:
		sentakuDisp();
		break;
	case hadacolor:
		doutaiDisp();
		break;
	case huku:
		hukuDisp();
		break;
	case tuikahuku:
		tuikahukuDisp();
		break;
	case me:
		meDisp();
		break;
	case maegami:
		maegamiDisp();
		break;
	case usirogami:
		usirogamiDisp();
		break;
	case yokogami:
		yokogamiDisp();
		break;
	case tukegami:
		tukegamiDisp();
		break;
	case sousyoku:
		sousyokuDisp();
		break;
	case omake:
		omakeDisp();
		break;
	default:
		break;
	}

	charakuterimgsUpdete();
	charakutercolorimg();
}
void charaseisakubunkiInit() {
	bunki = 0;
	for (int i = 0; i < endimg; i++) {
		r[i] = 255;
		g[i] = 255;
		b[i] = 255;
	}
	sentakuInit();
	hukuInit();
	charakuterimgsUpdete();
	doutaiInit();
	meInit();
	maegamiInit();
	yokogamiInit();
	omakeInit();
	tuikahukuInit();
	usirogamiInit();
	tukegamiInit();
	sousyokuInit();

	charakuterx = sentakugetx();
	charakutery = sentakugety();
	colorsInit();
}


void charaseisakubunnkiUpdete() {
		charaseisakuMove();
		charaseisakuDraw();
		
}
void charaseisakubunnkiDelete() {
	sentakuDelete();
	hukuDelete();
	doutaiDelete();
	meDelete();
	maegamiDelete();
	yokogamiDelete();
	omakeDelete();
	tuikahukuDelete();
	usirogamiDelete();
	tukegamiDelete();
	sousyokuDelete();

	for (int i = 0; i < endimg; i++)
		DeleteGraph(charakuterimgs[i]);
	DeleteGraph(charakuteromakeimg);
}