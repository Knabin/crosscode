#pragma once
class iEvent
{
public:
	// 이벤트가 시작될 때 실행할 함수
	virtual void eventStart() = 0;
	// 이벤트 업데이트
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