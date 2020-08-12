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

bool MINTCHOCO_UTIL::checkPointInCircle(float cX, float cY, float cR, const POINT & pt)
{
	float deltaX = pt.x - cX;
	float deltaY = pt.y - cY;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radiusSquare = cR * cR;

	if (radiusSquare < distSquare) return false;

	return true;
}

bool MINTCHOCO_UTIL::checkPointInCircle(float cX, float cY, float cR, float x, float y)
{
	float deltaX = x - cX;
	float deltaY = y - cY;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radiusSquare = cR * cR;

	if (radiusSquare < distSquare) return false;

	return true;
}

bool MINTCHOCO_UTIL::checkPointInCircle(const floatCircle & rc, float x, float y)
{
	float deltaX = x - rc.x;
	float deltaY = y - rc.y;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radiusSquare = rc.r * rc.r;

	if (radiusSquare < distSquare) return false;

	return true;
}

bool MINTCHOCO_UTIL::checkPointInCircle(const floatCircle & rc, const floatPoint & pt)
{
	float deltaX = pt.x - rc.x;
	float deltaY = pt.y - rc.y;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radiusSquare = rc.r * rc.r;

	if (radiusSquare < distSquare) return false;
}

bool MINTCHOCO_UTIL::isCollision(const floatRect & rc1, const RECT & rc2)
{
	if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
		(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;

	return false;
}

bool MINTCHOCO_UTIL::isCollision(const floatRect & rc1, const floatRect & rc2)
{
	if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
		(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;

	return false;
}

bool MINTCHOCO_UTIL::isCollision(const RECT & rc1, const RECT & rc2)
{
	if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
		(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;

	return false;
}

bool MINTCHOCO_UTIL::isCollisionReaction(const RECT & rcHold, RECT & rcMove)
{
	RECT rcInter;

	if (!IntersectRect(&rcInter, &rcHold, &rcMove)) return false;

	//겹친 부분에 생긴 렉트 정보를 받아와서
	//겹친 부분에 생긴 작은 렉트의 가로크기, 세로크기
	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	//수직충돌
	if (interW > interH)
	{
		//위에서 부딪혔을때
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
		//좌 충돌
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

	//겹친 부분에 생긴 렉트 정보를 받아와서
	//겹친 부분에 생긴 작은 렉트의 가로크기, 세로크기
	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	//수직충돌
	if (interW > interH)
	{
		//위에서 부딪혔을때
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
		//좌 충돌
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