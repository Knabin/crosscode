#pragma once
#include "gameObject.h"
class townBlock : public gameObject
{
private:
	image* _img;
	bool _isOpen;

public:
	~townBlock() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

