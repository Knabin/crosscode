#pragma once
#include "gameObject.h"

class dialogText : public gameObject
{
private:
	wstring _str;
	int _type;

public:
	dialogText(wstring str, int type);

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

