#pragma once
class iEvent
{
public:
	// �̺�Ʈ�� ���۵� �� ������ �Լ�
	virtual void eventStart() = 0;
	// �̺�Ʈ ������Ʈ
	virtual bool eventUpdate() = 0;
};

class iObjectMove final : public iEvent
{
	class gameObject* _targetObject;
	vector2 _targetLocation;
	float _speed;

public:
	iObjectMove(gameObject* targetObject, vector2 targetLocation, float speed);

	void eventStart() override;
	bool eventUpdate() override;
};