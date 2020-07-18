#include "stdafx.h"
#include "playGround.h"

void playGround::collision()
{
	for (int i = 0; i < _ship->getJumo()->getVJumo().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->getVMinion()[j]->getRect(), &_ship->getJumo()->getVJumo()[i].rc))
			{
				_ship->getJumo()->removeJumo(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}