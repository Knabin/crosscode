#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	_oneAngry = false;//앵그리 함수를 한번만 실행되게 하기 위한 변수

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}

void enemy::angry()//에너미의 현재 체력이 절반이하가 되면 능력치 상승
{
	if (!_oneAngry && _maxHP / 2 >= _currentHP)//에너미의 현재 HP가 절반이하이면
	{
		_speed *= 2;
		_attackPower *= 2;
		_maxAttackDelay /= 2;
		_oneAngry = true;
	}
}
