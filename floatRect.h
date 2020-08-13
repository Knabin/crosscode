#pragma once
class floatRect final
{
public:
	float left;
	float top;
	float right;
	float bottom;

public:
	floatRect();
	explicit floatRect(const float& left, const float& top, const float& right, const float& bottom);
	explicit floatRect(const int& left, const int& top, const int& right, const int& bottom);
	explicit floatRect(const float& x, const float& y, const float& width, const float& height, const pivot & pivot);
	explicit floatRect(const RECT& rc);

	const RECT getRect();
	float getWidth();
	float getHeight();
	floatPoint getCenter();
	floatPoint getSize();
	
	// floatRect 만드는 함수 (center x, center y, 가로 길이, 세로 길이)
	void set(const float& x, const float& y, const float& width, const float& height);
	void move(const float& moveX, const float& moveY);

	void setLeftTop(float left, float top);
	void setCenter(float centerX, float centerY);

	void render(HDC hdc)
	{
		Rectangle(hdc,
			FLOAT_TO_INT(left),
			FLOAT_TO_INT(top),
			FLOAT_TO_INT(right),
			FLOAT_TO_INT(bottom));
	}

	void render(HDC hdc, int x, int y)
	{
		Rectangle(hdc,
			FLOAT_TO_INT(left) + x,
			FLOAT_TO_INT(top) + y,
			FLOAT_TO_INT(right) + x,
			FLOAT_TO_INT(bottom) + y);
	}

	void renderCircle(HDC hdc)
	{
		Ellipse(hdc,
			FLOAT_TO_INT(left),
			FLOAT_TO_INT(top),
			FLOAT_TO_INT(right),
			FLOAT_TO_INT(bottom));
	}

	const floatRect& operator=(const RECT& rc);
	const bool operator==(const floatRect& rc);
};
inline floatRect RectMakePivot(const floatPoint& position, const floatPoint& size, const pivot& pivot) {
	floatRect result;

	switch (pivot)
	{
	case pivot::LEFTTOP:
		result.left = position.x;
		result.top = position.y;
		result.right = position.x + size.x;
		result.bottom = position.y + size.y;
		return result;
	case pivot::CENTER:
		result.left = position.x - size.x * 0.5f;
		result.top = position.y - size.y * 0.5f;
		result.right = position.x + size.x * 0.5f;
		result.bottom = position.y + size.y * 0.5f;
		return result;
	case pivot::BOTTOM:
		result.left = position.x - size.x * 0.5f;
		result.top = position.y - size.y;
		result.right = position.x + size.x * 0.5f;
		result.bottom = position.y;
		return result;
	}
	return result;
}

