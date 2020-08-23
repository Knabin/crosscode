#pragma once
#include "gameObject.h"

class portrait : public gameObject
{
private:
	image* _img;
	int _type;

public:
	portrait(int type);
	HRESULT init();
	void update();
	void render();

	// type 홀수: 레아, 짝수: 프로그래머
	// 프로그래머 - 0: 일반, 2: 안경, 4: 화남, 6: 웃음, 8: 놀람
	// 레아 - 1: 일반, 3: 고개 들기, 5: 놀람, 7: 웃음, 9: ㅡㅡ
	void setType(int type);
};

