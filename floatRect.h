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
	floatPoint getBottom();
	floatPoint getSize();
	void update(const float& x, const float& y, const float& width, const float& height, const pivot & pivot);
	void move(const float& moveX, const float& moveY);

	const floatRect& operator=(const RECT& rc);
};
inline floatRect RectMakePivot(const floatPoint& position, const floatPoint& size, const pivot& pivot){
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

