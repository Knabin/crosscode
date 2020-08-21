#include "stdafx.h"
#include "bossBlock.h"

bossBlock::~bossBlock()
{
}

HRESULT bossBlock::init()
{
	_img = IMAGEMANAGER->addFrameImage("boss block", L"images/object/bossblock.png", 3, 1);
	_frameX = 0;
	_count = 0;

	return S_OK;
}

void bossBlock::release()
{
}

void bossBlock::update()
{
	_count++;
	if (_count % 5 == 0)
	{
		_frameX++;
		if (_frameX >= _img->getMaxFrameX())
			_frameX = 0;
		_count = 0;
	}
}

void bossBlock::render()
{
	_img->frameRender(CAMERA->getRelativeVector2(_position), _frameX, 0);
}
