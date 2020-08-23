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

class iPlayerTurn final : public iEvent
{
	class player* _player;
	int _direction;

public:
	//	0: TOP, 1: LEFT_TOP, 2: LEFT, 3: LEFT_BOTTOM, 4: BOTTOM, 5: RIGHT_BOTTOM, 6: RIGHT, 7: RIGHT_TOP,
	iPlayerTurn(int direction);

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

class iMoveScene final : public iEvent
{
private:
	class player* _player;
	wstring _sceneName;
	Vector2 _location;

public:
	iMoveScene(wstring sceneName, Vector2 location);

	void eventStart() override;
	bool eventUpdate() override;
};

class iCameraMove final : public iEvent
{
private:
	class gameObject* _target;
	float _time;
	float _speed;
	float _angle;

public:
	iCameraMove(gameObject* target, float time);

	void eventStart() override;
	bool eventUpdate() override;
};

class iObjectActive final : public iEvent
{
private:
	class gameObject* _target;
	float _time;

public:
	iObjectActive(gameObject* object, float time);

	void eventStart() override;
	bool eventUpdate() override;
};

class iShake final : public iEvent
{
private:
	float _amount;
	float _time;

public:
	iShake(float amount, float time);

	void eventStart() override;
	bool eventUpdate() override;
};

class iItemAdd final : public iEvent
{
private:
	class inventory* _inven;

public:
	iItemAdd();

	void eventStart() override;
	bool eventUpdate() override;
};

class iPlayerDead final : public iEvent
{
private:
	class player* _player;

public:
	iPlayerDead();
	void eventStart() override;
	bool eventUpdate() override;
};