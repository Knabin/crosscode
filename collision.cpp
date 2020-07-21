#include "stdafx.h"
#include "collision.h"

bool MINTCHOCO_UTIL::checkPointInRect(const RECT & rc, const POINT & pt)
{
	if ((rc.left <= pt.x && pt.x <= rc.right) &&
		(rc.top <= pt.y && pt.y <= rc.bottom)) return true;
	return false;
}

bool MINTCHOCO_UTIL::checkPointInRect(const RECT & rc, const floatPoint & pt)
{
	if ((rc.left <= pt.x && pt.x <= rc.right) &&
		(rc.top <= pt.y && pt.y <= rc.bottom)) return true;
	return false;
}

bool MINTCHOCO_UTIL::checkPointInRect(const RECT & rc, int x, int y)
{
	if ((rc.left <= x && x <= rc.right) &&
		(rc.top <= y && y <= rc.bottom)) return true;
	return false;
}

bool MINTCHOCO_UTIL::checkPointInRect(const RECT & rc, const vector2 & vector)
{
	if ((rc.left <= vector.x && vector.x <= rc.right) &&
		(rc.top <= vector.y && vector.y <= rc.bottom)) return true;
	return false;
}

bool MINTCHOCO_UTIL::checkPointInRect(const floatRect& rc, const POINT & pt)
{
	if ((rc.left <= pt.x && pt.x <= rc.right) &&
		(rc.top <= pt.y && pt.y <= rc.bottom)) return true;
	return false;
}

bool MINTCHOCO_UTIL::checkPointInRect(const floatRect & rc, const floatPoint & pt)
{
	if ((rc.left <= pt.x && pt.x <= rc.right) &&
		(rc.top <= pt.y && pt.y <= rc.bottom)) return true;
	return false;
}

bool MINTCHOCO_UTIL::checkPointInRect(const floatRect & rc, float x, float y)
{
	if ((rc.left <= x && x <= rc.right) &&
		(rc.top <= y && y <= rc.bottom)) return true;
	return false;
}

bool MINTCHOCO_UTIL::checkPointInRect(const floatRect & rc, const vector2 & vector)
{
	if ((rc.left <= vector.x && vector.x <= rc.right) &&
		(rc.top <= vector.y && vector.y <= rc.bottom)) return true;
	return false;
}

bool MINTCHOCO_UTIL::checkPointInCircle(float cX, float cY, float cR, const POINT & pt)
{
	return false;
}

bool MINTCHOCO_UTIL::checkPointInCircle(float cX, float cY, float cR, float x, float y)
{
	return false;
}

bool MINTCHOCO_UTIL::checkPointInCircle(float cX, float cY, float cR, const vector2 & vector)
{
	return false;
}

bool MINTCHOCO_UTIL::checkPointInCircle(const floatRect & rc, float x, float y)
{
	return false;
}

bool MINTCHOCO_UTIL::checkPointInCircle(const floatRect & rc, const floatPoint & pt)
{
	return false;
}

bool MINTCHOCO_UTIL::isCollision(const floatRect & cir, const RECT & rc)
{
	return false;
}

bool MINTCHOCO_UTIL::isCollision(const floatRect & rc1, const floatRect & rc2)
{
	return false;
}

bool MINTCHOCO_UTIL::isCollisionReaction(const RECT & rcHold, RECT & rcMove)
{
	RECT rcInter;

	if (!IntersectRect(&rcInter, &rcHold, &rcMove)) return false;

	//��ģ �κп� ���� ��Ʈ ������ �޾ƿͼ�
	//��ģ �κп� ���� ���� ��Ʈ�� ����ũ��, ����ũ��
	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	//�����浹
	if (interW > interH)
	{
		//������ �ε�������
		if (rcInter.top == rcHold.top)
		{
			OffsetRect(&rcMove, 0, -interH);
		}
		else if (rcInter.bottom == rcHold.bottom)
		{
			OffsetRect(&rcMove, 0, interH);
		}
	}
	else
	{
		//�� �浹
		if (rcInter.left == rcHold.left)
		{
			OffsetRect(&rcMove, -interW, 0);
		}
		else if (rcInter.right == rcHold.right)
		{
			OffsetRect(&rcMove, interW, 0);
		}
	}

	return true;
}

bool MINTCHOCO_UTIL::isCollisionReaction(const floatRect & mrcHold, floatRect & mrcMove)
{
	RECT rcInter;

	RECT rcHold;
	rcHold.left = FLOAT_TO_INT(mrcHold.left);
	rcHold.top = FLOAT_TO_INT(mrcHold.top);
	rcHold.right = FLOAT_TO_INT(mrcHold.right);
	rcHold.bottom = FLOAT_TO_INT(mrcHold.bottom);

	RECT rcMove;
	rcMove.left = FLOAT_TO_INT(mrcMove.left);
	rcMove.top = FLOAT_TO_INT(mrcMove.top);
	rcMove.right = FLOAT_TO_INT(mrcMove.right);
	rcMove.bottom = FLOAT_TO_INT(mrcMove.bottom);

	if (!IntersectRect(&rcInter, &rcHold, &rcMove)) return false;

	//��ģ �κп� ���� ��Ʈ ������ �޾ƿͼ�
	//��ģ �κп� ���� ���� ��Ʈ�� ����ũ��, ����ũ��
	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	//�����浹
	if (interW > interH)
	{
		//������ �ε�������
		if (rcInter.top == rcHold.top)
		{
			OffsetRect(&rcMove, 0, -interH);
		}
		else if (rcInter.bottom == rcHold.bottom)
		{
			OffsetRect(&rcMove, 0, interH);
		}
	}
	else
	{
		//�� �浹
		if (rcInter.left == rcHold.left)
		{
			OffsetRect(&rcMove, -interW, 0);
		}
		else if (rcInter.right == rcHold.right)
		{
			OffsetRect(&rcMove, interW, 0);
		}
	}


	mrcMove.left = static_cast<float>(rcMove.left);
	mrcMove.top = static_cast<float>(rcMove.top);
	mrcMove.right = static_cast<float>(rcMove.right);
	mrcMove.bottom = static_cast<float>(rcMove.bottom);

	return true;
}

bool MINTCHOCO_UTIL::isCollisionReactionCircle(const floatCircle & cirHold, floatCircle & cirMove)
{
	float deltaX = cirMove.x - cirHold.x;
	float deltaY = cirMove.y - cirHold.y;
	float distSquare = sqrtf(deltaX * deltaX + deltaY * deltaY);

	float radius = cirHold.r + cirMove.r;

	if (distSquare < radius)
	{
		float angle = getAngle(cirHold.x, cirHold.y, cirMove.x, cirMove.y);

		float moveDelta = radius - distSquare;
		float moveX = cos(angle) * moveDelta;
		float moveY = -sin(angle) * moveDelta;

		cirMove.move(moveX, moveY);

		return true;
	}

	return false;
}

bool MINTCHOCO_UTIL::isCollision(const RECT & rc1, const RECT & rc2)
{
	return false;
}
