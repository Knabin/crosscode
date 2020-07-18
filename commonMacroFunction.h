#pragma once
//=============================
// ## 20.05.27 ## Macro~ ##
//=============================

//���߱� �ѷ���DC, ��������ǥX ��������ǥY ���� ����ǥX, ���� ����ǥY
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}
//��ũ�� ��� ��� �����Դϴ� ��κ�!!!
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };

	return pt;
}

//================= ��Ʈ ���� �Լ� ===================
//left, top �������� ��Ʈ ź��(left, top, ����ũ��, ����ũ��)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

// ���� X,Y�� �������� ��Ʈź��(����X, ����Y, ����ũ��, ����ũ��)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}



//================= �簢�� ���� �Լ� ==================

inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}



//left, top �������� �簢���׸���(�ѷ���DC, ������ X, ������ Y, ����ũ��, ����ũ��)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// ���� X,Y�� �������� �簢��ź��(�ѷ���DC, ����X, ����Y, ����ũ��, ����ũ��)
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2));
}

//================== �� ���� �Լ� =====================
inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//left, top �������� �� �׸���(�ѷ���DC, ������ X, ������ Y, ����ũ��, ����ũ��)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// ���� X,Y�� �������� �� ź��(�ѷ���DC, ����X, ����Y, ����ũ��, ����ũ��)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2));
}