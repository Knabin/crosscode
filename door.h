#pragma once
#include "gameObject.h"

class door : public gameObject
{
	// left top �������� �ۼ��ϱ�
	int _type;

public:
	
	void setType(int type) { _type = type; }
};

