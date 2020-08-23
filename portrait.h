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

	// type Ȧ��: ����, ¦��: ���α׷���
	// ���α׷��� - 0: �Ϲ�, 2: �Ȱ�, 4: ȭ��, 6: ����, 8: ���
	// ���� - 1: �Ϲ�, 3: �� ���, 5: ���, 7: ����, 9: �Ѥ�
	void setType(int type);
};

