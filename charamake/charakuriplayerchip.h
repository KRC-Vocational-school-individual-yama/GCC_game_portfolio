#pragma once

class charakuriplayerchip {
public:
	float x, y;
	int img = -1;

	charakuriplayerchip();
	void charakuricharaAnime();
	void charakuricharaTrun();
	void charakuricharaDraw();

	int charakurimoveX2(double speed);//���ڂ��ɓ����
	int charakurimoveY2(double speed);//����y�ɓ����
	int charakurigethandlex() { return handlex; }
	int charakurigethandley() { return handley; }
	~charakuriplayerchip();

private:

	void _0_1_2_1_0_(int& x);
	void counter() { count++; };
	int count = 0;
	int handlex = 1;
	int handley = 0;
	int tcount = 0;
	bool trunflug = false;


};
