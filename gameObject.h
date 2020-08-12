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
	floatRect _bulletRc;// 플레이어 마사일RECT
	bool _isActive;		// 오브젝트 활성화 여부, 화면에 표시할 것인지
	pivot _pivot;		// 오브젝트 RECT 기준(pivot)

public:
	gameObject();
	gameObject(float x, float y);
	// 생성자 (오브젝트 이름, x, y, 가로 길이, 세로 길이, 기준점(pivot:: 치면 나옴))
	gameObject(const string& name, const float& x, const float& y, const float& width, const float& height, const pivot& pivot);
	virtual ~gameObject();
	// 오브젝트를 절대 좌표 기준으로 출력하기 위한 함수
	virtual void renderRelative(float x, float y) {};


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
	floatRect& getRect() { return _rc; }

	void setBulletRect(floatRect bulletRc) { _bulletRc = bulletRc; }
	floatRect& getBulletRect() { return _bulletRc; }

	void setIsActive(bool isActive) { _isActive = isActive; }
	bool getIsActive() const { return _isActive; }
};

