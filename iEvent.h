#pragma once
class iEvent
{
public:
	// 이벤트가 시작될 때 실행할 함수
	virtual void eventStart() = 0;
	// 이벤트 업데이트
	virtual bool eventUpdate() = 0;
};

class iMoveToTarget final : public iEvent
{
	class gameObject* _targetObject;
	Vector2 _targetLocation;
	float _speed;

public:
	iMoveToTarget(class gameObject* targetObject, Vector2 targetLocation, float speed);

	void eventStart() override;
	bool eventUpdate() override;
};

class iObjectMove final : public iEvent
{
	class gameObject* _targetObject;
	Vector2 _targetLocation;
	float _speed;

public:
	iObjectMove(gameObject* targetObject, Vector2 targetLocation, float speed);

	void eventStart() override;
	bool eventUpdate() override;
};

class iPlayerMove final : public iEvent
{
	class player* _player;
	Vector2 _targetLocation;
	float _speed;

public:
	iPlayerMove(Vector2 targetLocation);

	void eventStart() override;
	bool eventUpdate() override;
};

class iDialog final : public iEvent
{
	class dialog* _dialog;

public:
	iDialog(dialog* dialog);

	void eventStart() override;
	bool eventUpdate() override;
};