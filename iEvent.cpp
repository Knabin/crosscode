#include "stdafx.h"
#include "iEvent.h"
#include "gameObject.h"

iObjectMove::iObjectMove(gameObject * targetObject, vector2 targetLocation, float speed)
{
	_targetObject = targetObject;
	_targetLocation = targetLocation;
	_speed = speed;
}

void iObjectMove::eventStart()
{
}

bool iObjectMove::eventUpdate()
{
	vector2 position = _targetObject->getPosition();
	float angle = getAngle(position.x, position.y, _targetLocation.x, _targetLocation.y);

	position.x += cosf(angle) * _speed * timeManager::getInstance()->getElapsedTime();
	position.y -= sinf(angle) * _speed * timeManager::getInstance()->getElapsedTime();

	_targetObject->setPosition(position);
	_targetObject->setRect(floatRect(position, _targetObject->getSize(), pivot::CENTER));

	if (getDistance(position.x, position.y, _targetLocation.x, _targetLocation.y) < 3)
	{
		_targetObject->setPosition(_targetLocation);
		return true;
	}

	return false;
}
