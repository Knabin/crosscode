#include "stdafx.h"
#include "iEvent.h"
#include "gameObject.h"
#include "player.h"
#include "dialog.h"

iObjectMove::iObjectMove(gameObject * targetObject, Vector2 targetLocation, float speed)
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
	Vector2 position = _targetObject->getPosition();
	float angle = getAngle(position.x, position.y, _targetLocation.x, _targetLocation.y);

	position.x += cosf(angle) * _speed * timeManager::getInstance()->getElapsedTime();
	position.y -= sinf(angle) * _speed * timeManager::getInstance()->getElapsedTime();

	_targetObject->setPosition(position);
	_targetObject->setRect(floatRect(position, Vector2(_targetObject->getWidth(), _targetObject->getHeight()), pivot::CENTER));

	if (getDistance(position.x, position.y, _targetLocation.x, _targetLocation.y) < 3)
	{
		_targetObject->setPosition(_targetLocation);
		return true;
	}

	return false;
}

iMoveToTarget::iMoveToTarget(gameObject * targetObject, Vector2 targetLocation, float speed)
{
	_targetObject = targetObject;
	_targetLocation = targetLocation;
	_speed = speed;
}

void iMoveToTarget::eventStart()
{
}

bool iMoveToTarget::eventUpdate()
{
	return false;
}

iDialog::iDialog(dialog * dialog)
	: _dialog(dialog)
{
}

void iDialog::eventStart()
{
	_dialog->loadText();
}

bool iDialog::eventUpdate()
{
	if (_dialog->next())
	{
		// true∏È ∏ÿ√„
		SAFE_DELETE(_dialog);
		return true;
	}
	return false;
}

iPlayerMove::iPlayerMove(Vector2 targetLocation)
	: _targetLocation(targetLocation)
{
}

void iPlayerMove::eventStart()
{
	// πÊ«‚ ¿¸»Ø
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	_player->setState(PLAYERSTATE::MOVE);
}

bool iPlayerMove::eventUpdate()
{
	Vector2 position = _player->getPosition();
	float angle = getAngle(position.x, position.y, _targetLocation.x, _targetLocation.y);

	position.x += cosf(angle);
	position.y -= sinf(angle);

	_player->setPosition(position);
	//_targetObject->setRect(floatRect(position, Vector2(_targetObject->getWidth(), _targetObject->getHeight()), pivot::CENTER));

	if (getDistance(position.x, position.y, _targetLocation.x, _targetLocation.y) < 3)
	{
		_player->setState(PLAYERSTATE::MOVESTOP);
		_player->setPosition(_targetLocation);
		return true;
	}

	return false;
}
