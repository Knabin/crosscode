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
	explicit floatRect(const Vector2& pos, const Vector2& size, const pivot& pivot);
	explicit floatRect(const RECT& rc);

	const RECT getRect();
	float GetWidth();
	float GetHeight();
	Vector2 getCenter();
	Vector2 GetBottom();
	Vector2 getSize();
	void update(const Vector2& pos, const Vector2& size, const pivot& pivot);
	void set(const Vector2& pos, const pivot& pivot);
	void Move(const Vector2& moveValue);

	const floatRect& operator=(const RECT& rc);
};

inline floatRect RectMakePivot(const Vector2& pos, const Vector2& size, const pivot& pivot)
{
	
	floatRect result;
	switch (pivot)
	{
	case pivot::LEFTTOP:
		result.left = pos.x	 *GetSystemMetrics(SM_CXSCREEN) / 1920;
		result.top = pos.y	*GetSystemMetrics(SM_CYSCREEN) / 1080;
		result.right = pos.x  *GetSystemMetrics(SM_CXSCREEN) / 1920 + size.x *GetSystemMetrics(SM_CXSCREEN) / 1920;
		result.bottom = pos.y  *GetSystemMetrics(SM_CYSCREEN) / 1080 + size.y *GetSystemMetrics(SM_CYSCREEN) / 1080;
		return result;
	case pivot::CENTER:
		result.left = pos.x *GetSystemMetrics(SM_CXSCREEN) / 1920 - size.x / 2.f *GetSystemMetrics(SM_CXSCREEN) / 1920;
		result.top = pos.y *GetSystemMetrics(SM_CYSCREEN) / 1080 - size.y / 2.f*GetSystemMetrics(SM_CYSCREEN) / 1080;
		result.right = pos.x + size.x / 2.f;
		result.bottom = pos.y *GetSystemMetrics(SM_CYSCREEN) / 1080 + size.y / 2.f*GetSystemMetrics(SM_CYSCREEN) / 1080;
		return result;
	case pivot::BOTTOM:
		result.left = pos.x *GetSystemMetrics(SM_CXSCREEN) / 1920 - size.x / 2.f*GetSystemMetrics(SM_CXSCREEN) / 1920;
		result.top = pos.y*GetSystemMetrics(SM_CYSCREEN) / 1080 - size.y*GetSystemMetrics(SM_CYSCREEN) / 1080;
		result.right = pos.x *GetSystemMetrics(SM_CXSCREEN) / 1920 + size.x / 2.f*GetSystemMetrics(SM_CXSCREEN) / 1920;
		result.bottom = pos.y*GetSystemMetrics(SM_CYSCREEN) / 1080;
		return result;
	}
	return result;
}