#pragma once

namespace MINTCHOCO_UTIL
{
	//POINT�� �簢�� �ȿ� �ֳ�
	bool checkPointInRect(const RECT& rc, const POINT& pt);
	bool checkPointInRect(const RECT& rc, const floatPoint& pt);
	bool checkPointInRect(const RECT& rc, int x, int y);

	bool checkPointInRect(const floatRect& rc, const POINT& pt);
	bool checkPointInRect(const floatRect& rc, const floatPoint& pt);
	bool checkPointInRect(const floatRect& rc, float x, float y);


	//POINT�� �� �ȿ� �ֳ�
	bool checkPointInCircle(float cX, float cY, float cR, const POINT& pt);
	bool checkPointInCircle(float cX, float cY, float cR, float x, float y);
	bool checkPointInCircle(const floatCircle& rc, float x, float y);
	bool checkPointInCircle(const floatCircle& rc, const floatPoint& pt);


	//�簢���� �簢���̶� �浹�ߴ�?
	bool isCollision(const floatRect& rc1, const floatRect& rc2);
	bool isCollision(const RECT& rc1, const RECT& rc2);

	//���� ���� �浹�ߴ�?
	bool isCollision(const floatRect& cir1, const floatRect& cir2);

	//���� �簢���� �浹�ߴ�?
	bool isCollision(const floatRect& cir, const RECT& rc);
	bool isCollision(const floatRect& cir, const floatRect& rc);

	bool isCollisionReaction(const RECT& rcHold, RECT& rcMove);
	bool isCollisionReaction(const floatRect& mrcHold, floatRect& mrcMove);

	bool isCollisionReactionCircle(const floatCircle& cirHold, floatCircle& cirMove);
}