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
	floatPoint _targetLocation;
	float _speed;

public:
	iMoveToTarget(class gameObject* targetObject, floatPoint targetLocation, float speed);

	void eventStart() override;
	bool eventUpdate() override;
};

class iObjectMove final : public iEvent
{
	class gameObject* _targetObject;
	floatPoint _targetLocation;
	float _speed;

public:
	iObjectMove(gameObject* targetObject, floatPoint targetLocation, float speed);

	void eventStart() override;
	bool eventUpdate() override;
};