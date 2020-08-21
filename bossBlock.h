#pragma once
#include "gameObject.h"
class bossBlock : public gameObject
{
private:
	image* _img;
	int _frameX;
	int _count;

public:
	~bossBlock() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

