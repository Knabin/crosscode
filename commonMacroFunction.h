#pragma once
//=============================
// ## 20.05.27 ## Macro~ ##
//=============================

//선긋기 뿌려줄DC, 선시작좌표X 선시작좌표Y 선의 끝좌표X, 선의 끝좌표Y
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}
//매크로 펑션 헤더 파일입니다 요로분!!!
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };

	return pt;
}

//================= 렉트 관련 함수 ===================
//left, top 기준으로 렉트 탄생(left, top, 가로크기, 세로크기)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

// 중점 X,Y를 기준으로 렉트탄생(중점X, 중점Y, 가로크기, 세로크기)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}



//================= 사각형 관련 함수 ==================

inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}



//left, top 기준으로 사각형그린다(뿌려줄DC, 기준점 X, 기준점 Y, 가로크기, 세로크기)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// 중점 X,Y를 기준으로 사각형탄생(뿌려줄DC, 중점X, 중점Y, 가로크기, 세로크기)
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2));
}

//================== 원 관련 함수 =====================
inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//left, top 기준으로 원 그린다(뿌려줄DC, 기준점 X, 기준점 Y, 가로크기, 세로크기)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// 중점 X,Y를 기준으로 원 탄생(뿌려줄DC, 중점X, 중점Y, 가로크기, 세로크기)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2));
}