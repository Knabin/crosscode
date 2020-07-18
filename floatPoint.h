#pragma once
class floatPoint final
{
public:
	float x;
	float y;

public:
	floatPoint();
	explicit floatPoint(const float& x, const float& y);
	explicit floatPoint(const int& x, const int& y);
	explicit floatPoint(const vector2& vector);
};

