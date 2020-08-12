#pragma once
#include "gameObject.h"

class door : public gameObject
{
	// left top 기준으로 작성하기
	int _type;

public:
	
	void setType(int type) { _type = type; }
};

