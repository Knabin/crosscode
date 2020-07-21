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
	explicit floatRect(const vector2 & position, const vector2 & size, const pivot & pivot);
	explicit floatRect(const RECT& rc);

	const RECT getRect();
	float getWidth();
	float getHeight();
	vector2 getCenter();
	float getCenterX();
	float getCenterY();
	vector2 getBottom();
	vector2 getSize();

	void setLeftTop(float left, float top);
	void setCenter(float centerX, float centerY);

	void update(const vector2 & position, const vector2 & size, const pivot & pivot);

	void move(const vector2& moveValue);
	void move(const float& dx, const float& dy);

	void render(HDC hdc)
	{
		Rectangle(hdc,
			FLOAT_TO_INT(left),
			FLOAT_TO_INT(top),
			FLOAT_TO_INT(right),
			FLOAT_TO_INT(bottom));
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

