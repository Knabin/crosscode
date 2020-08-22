#pragma once
#include "gameObject.h"

class foothold : public gameObject
{
private:
	image* _image;
	bool _isOn;				// Ȱ��ȭ�Ǿ�����
	bool _isStepOn;			// ��� �ִ���
	int _count;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setIsOn(bool isOn) { _isOn = isOn; }
	bool getIsOn() { return _isOn; }

	bool canChangeScene() { return _isOn && _isStepOn && (_count > 50); }
};

