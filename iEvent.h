#pragma once
class iEvent
{
public:
	// �̺�Ʈ�� ���۵� �� ������ �Լ�
	virtual void eventStart() = 0;
	// �̺�Ʈ ������Ʈ
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