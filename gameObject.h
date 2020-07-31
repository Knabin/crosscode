#pragma once
#include "gameNode.h"

class gameObject : public gameNode
{
protected:
	string _name;		// 오브젝트 이름
	float _x;			// 오브젝트 좌표 X
	float _y;			// 오브젝트 좌표 Y
	float _width;		// 오브젝트 가로 크기
	float _height;		// 오브젝트 세로 크기
	floatRect _rc;		// 오브젝트 RECT(float type)
	bool _isActive;		// 오브젝트 활성화 여부
	pivot _pivot;		// 오브젝트 RECT 기준(pivot)

public:
	gameObject();
	gameObject(float x, float y);
	gameObject(const string& name, const float& x, const float& y, const float& width, const float& height, const pivot& pivot);
	virtual ~gameObject();


	// =========================================================
	// getter / setter
	// =========================================================
	void setName(string name) { _name = name; }
	string getName() const { return _name; }

	void setX(float x) { _x = x; _rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot); }
	float getX() const { return _x; }

	void setY(float y) { _y = y; _rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot); }
	float getY() const { return _y; }

	void setPosition(floatPoint position) { _x = position.x; _y = position.y; _rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot); }
	floatPoint getPosition() const { return floatPoint(_x, _y); }

	void setWidth(float width) { _width = width; _rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot); }
	float getWidth() const { return _width; }

	void setHeight(float height) { _height = height; _rc = RectMakePivot(floatPoint(_x, _y), floatPoint(_width, _height), _pivot); }
	float getHeight() const { return _height; }

	void setRect(floatRect rect) { _rc = rect; }
	floatRect getRect() const { return _rc; }

	void setIsActive(bool isActive) { _isActive = isActive; }
	bool getIsActive() const { return _isActive; }
};

