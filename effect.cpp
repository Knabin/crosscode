#include "stdafx.h"
#include "effect.h"
#include "animation.h"

effect::effect()
	: _effectImage(NULL),
	_effectAnimation(NULL),
	_isRunning(false),
	_x(0), _y(0)
{
}


effect::~effect()
{
}

HRESULT effect::init(image * effectImage, int frameW, int frameH, int fps, float elapsedTime, float scale)
{
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_scale = scale;

	//이펙트 애니메이션이 없으면 생성해라
	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(),
		frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();

	return S_OK;
}

void effect::release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::update()
{
	//이펙트 애니메이션 실행 변수가 false면 실행하지 마라
	if (!_isRunning) return;

	_effectAnimation->frameUpdate(_elapsedTime);

	if (!_effectAnimation->isPlay()) killEffect();
}

void effect::render()
{
	if (!_isRunning) return;

	_effectImage->setAngle(_angle);
	_effectImage->setAlpha(_alpha);
	_effectImage->aniRender(Vector2(_x, _y), _effectAnimation, _scale);
}

void effect::startEffect(int x, int y, float angle, float alpha)
{
	if (!_effectImage || !_effectAnimation) return;

	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);
	_angle = angle;
	_alpha = alpha;

	_isRunning = true;

	_effectAnimation->start();
}

void effect::startEffect(Vector2 pos, float angle, float alpha)
{
	if (!_effectImage || !_effectAnimation) return;

	_x = pos.x - (_effectAnimation->getFrameWidth() / 2);
	_y = pos.y - (_effectAnimation->getFrameHeight() / 2);
	_angle = angle;
	_alpha = alpha;

	_isRunning = true;

	_effectAnimation->start();
}

void effect::killEffect()
{
	_isRunning = false;
}
