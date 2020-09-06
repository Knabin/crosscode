#pragma once
#include "gameNode.h"

class gameObject : public gameNode
{
protected:
	string _name;		// 오브젝트 이름
	Vector2 _position;	// 오브젝트 위치
	float _width;		// 오브젝트 가로 크기
	float _height;		// 오브젝트 세로 크기
	floatRect _rc;		// 오브젝트 RECT(float type)
	bool _isActive;		// 오브젝트 활성화 여부, 화면에 표시할 것인지
	bool _isAlive;		// 오브젝트 사용 여부, false라면 delete 처리 진행
	bool _trigger;		// 트리거
	pivot _pivot;		// 오브젝트 RECT 기준(pivot)

public:
	gameObject();
	gameObject(float x, float y);
	gameObject(Vector2 position);
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

