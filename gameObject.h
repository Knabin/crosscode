#pragma once
#include "gameNode.h"

class gameObject : public gameNode
{
protected:
	string _name;		// ������Ʈ �̸�
	float _x;			// ������Ʈ ��ǥ X
	float _y;			// ������Ʈ ��ǥ Y
	float _width;		// ������Ʈ ���� ũ��
	float _height;		// ������Ʈ ���� ũ��
	floatRect _rc;		// ������Ʈ RECT(float type)
	bool _isActive;		// ������Ʈ Ȱ��ȭ ����
	pivot _pivot;		// ������Ʈ RECT ����(pivot)

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

