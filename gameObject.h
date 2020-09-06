#pragma once
#include "gameNode.h"

class gameObject : public gameNode
{
protected:
	string _name;		// ������Ʈ �̸�
	Vector2 _position;	// ������Ʈ ��ġ
	float _width;		// ������Ʈ ���� ũ��
	float _height;		// ������Ʈ ���� ũ��
	floatRect _rc;		// ������Ʈ RECT(float type)
	bool _isActive;		// ������Ʈ Ȱ��ȭ ����, ȭ�鿡 ǥ���� ������
	bool _isAlive;		// ������Ʈ ��� ����, false��� delete ó�� ����
	bool _trigger;		// Ʈ����
	pivot _pivot;		// ������Ʈ RECT ����(pivot)

public:
	gameObject();
	gameObject(float x, float y);
	gameObject(Vector2 position);
	// ������ (������Ʈ �̸�, x, y, ���� ����, ���� ����, ������(pivot:: ġ�� ����))
	gameObject(const string& name, const float& x, const float& y, const float& width, const float& height, const pivot& pivot);
	virtual ~gameObject();
	// ������Ʈ�� ���� ��ǥ �������� ����ϱ� ���� �Լ�
	virtual void renderRelative(float x, float y) {};


	// =========================================================
	// getter / setter
	// =========================================================
	void setName(string name) { _name = name; }
	string getName() const { return _name; }

	void setPosition(Vector2 position) { _position = position; _rc = RectMakePivot(_position, Vector2(_width, _height), _pivot); }
	Vector2 getPosition() const { return _position; }

	void setWidth(float width) { _width = width; _rc = RectMakePivot(_position, Vector2(_width, _height), _pivot); }
	float getWidth() const { return _width; }

	void setHeight(float height) { _height = height; _rc = RectMakePivot(_position, Vector2(_width, _height), _pivot); }
	float getHeight() const { return _height; }

	void setRect(floatRect rect) { _rc = rect; }
	floatRect& getRect() { return _rc; }

	void setIsActive(bool isActive) { _isActive = isActive; }
	bool getIsActive() const { return _isActive; }

	void setIsAlive(bool isAlive) { _isAlive = isAlive; }
	bool getIsAlive() const { return _isAlive; }

	void setTrigger(bool trigger) { _trigger = trigger; }
	bool getTrigger() const { return _trigger; }
};

