#pragma once
#include "gameObject.h"

class foothold : public gameObject
{
private:
	image* _image;
	bool _isOn;				// Ȱ��ȭ�Ǿ�����
	bool _isStepOn;			// ��� �ִ���

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

