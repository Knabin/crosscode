#pragma once
class vector2 final
{
public:
	float x;
	float y;

public:
	explicit vector2();
	explicit vector2(const float& x, const float& y);
	explicit vector2(const int& x, const int& y);
	explicit vector2(const POINT& point);

	const int getIntX();
	const int getIntY();
	const POINT getPoint();

	vector2 operator+ (const vector2& v);
	vector2 operator- (const vector2& v);
	void operator+= (const vector2& v);
	void operator-= (const vector2& v);
	vector2 operator* (const float& scalar);
	vector2 operator/ (const float& scalar);
	const bool operator== (const vector2& v);
	const bool operator!= (const vector2& v);

public:
	static vector2 normalize(const vector2* const pVector2);
	static float toRadian(const vector2* const pVector2);
	static float length(const vector2* const pVector2);
	static float dot(const vector2* const pVector2A, const vector2* const pVector2B);
	static float cross(const vector2* const pVector2A, const vector2* const pVector2B);
};

