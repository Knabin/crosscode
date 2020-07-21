#pragma once
class floatCircle final
{
public:
	float x;
	float y;
	float r;

public:
	floatCircle();
	explicit floatCircle(const float& x, const float& y, const float& r);
	explicit floatCircle(const int& x, const int& y, const int& r);
	explicit floatCircle(const POINT& p, const int& r);
	explicit floatCircle(const floatPoint& p, const float& r);

	void move(float dx, float dy);
	void set(float centerX, float centerY, float radius);
	void setCenterPos(float centerX, float centerY);
	void render(HDC hdc)
	{
		int x1 = FLOAT_TO_INT(x);
		int y1 = FLOAT_TO_INT(y);
		int r1 = FLOAT_TO_INT(r);

		Ellipse(hdc, x1 - r1, y1 - r1, x1 + r1, y1 + r1);
	}
};

