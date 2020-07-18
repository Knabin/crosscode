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
	explicit floatRect(const vector2& position, const vector2& size, const pivot& pivot);
	explicit floatRect(const RECT& rc);

	const RECT getRect();
	float getWidth();
	float getHeight();
	vector2 getCenter();
	vector2 getBottom();
	vector2 getSize();
	void update(const vector2& position, const vector2& size, const pivot& pivot);
	void move(const vector2& moveValue);

	const floatRect& operator=(const RECT& rc);
};

inline floatRect RectMakePivot(const vector2& position, const vector2& size, const pivot& pivot)
{
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

