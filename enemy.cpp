#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	_oneAngry = false;//�ޱ׸� �Լ��� �ѹ��� ����ǰ� �ϱ� ���� ����

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

void enemy::angry()//���ʹ��� ���� ü���� �������ϰ� �Ǹ� �ɷ�ġ ���
{
	if (!_oneAngry && _maxHP / 2 >= _currentHP)//���ʹ��� ���� HP�� ���������̸�
	{
		_speed *= 2;
		_attackPower *= 2;
		_maxAttackDelay /= 2;
		_oneAngry = true;
	}
}
