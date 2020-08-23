#include "stdafx.h"
#include "iEvent.h"
#include "gameObject.h"
#include "player.h"
#include "dialog.h"
#include "inventory.h"

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
	_dialog->next();
}

bool iDialog::eventUpdate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_dialog->next())
		{
			// true∏È ∏ÿ√„
			SAFE_DELETE(_dialog);
			return true;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
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

iMoveScene::iMoveScene(wstring sceneName, Vector2 location)
	:_sceneName(sceneName), _location(location)
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
}

void iMoveScene::eventStart()
{
	CAMERA->fadeStart(1.f, 1.3f);
}

bool iMoveScene::eventUpdate()
{
	if (CAMERA->getIsFadeOut())
	{
		SCENEMANAGER->loadScene(_sceneName);
		_player->setPosition(_location);
		//_player->setDirection(PLAYERDIRECTION::BOTTOM);
		_player->setState(PLAYERSTATE::IDLE);
		return true;
	}
	return false;
}

iCameraMove::iCameraMove(gameObject * target, float time)
	:_target(target), _time(time)
{
}

void iCameraMove::eventStart()
{
}

bool iCameraMove::eventUpdate()
{
	CAMERA->changeTarget(_target);
	CAMERA->setCameraMode(CAMERASTATE::TARGET);

	_time -= TIMEMANAGER->getElapsedTime();

	if (_time < 0.f)
	{
		CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
		return true;
	}

	return false;
}

iObjectActive::iObjectActive(gameObject * object, float time)
	: _target(object), _time(time)
{
}

void iObjectActive::eventStart()
{
}

bool iObjectActive::eventUpdate()
{
	_target->setIsActive(true);
	_time -= TIMEMANAGER->getElapsedTime();
	if (_target->getIsActive() && _time <= 0.0f) return true;
	return false;
}

iShake::iShake(float amount, float time)
	: _amount(amount), _time(time)
{
}

void iShake::eventStart()
{
	CAMERA->shakeStart(_amount, _time);
}

bool iShake::eventUpdate()
{
	if (!CAMERA->getIsShake())
	{
		return true;
	}
	return false;
}

iPlayerTurn::iPlayerTurn(int direction)
	: _direction(direction)
{
}

void iPlayerTurn::eventStart()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
	_player->setIdle();
	_player->setDirection((PLAYERDIRECTION)_direction);
}

bool iPlayerTurn::eventUpdate()
{
	return true;
}

iItemAdd::iItemAdd()
{
}

void iItemAdd::eventStart()
{
	_inven = dynamic_cast<inventory*>(OBJECTMANAGER->findObject(objectType::UI, "inven"));
}

bool iItemAdd::eventUpdate()
{
	_inven->getItem(L"∆»", 0);
	_inven->getItem(L"∆»", 0);
	_inven->getItem(L"º“∏", 0);
	_inven->getItem(L"∏”∏Æ", 0);
	_inven->getItem(L"¥Ÿ∏Æ", 0);
	_inven->getItem(L"∏ˆ≈Î", 0);
	_inven->getItem(L"¡ﬂø‰", 0);

	return true;
}

iPlayerDead::iPlayerDead()
{
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));
}

void iPlayerDead::eventStart()
{
	CAMERA->zoomStart(1.4f, 0.9f, true);
	CAMERA->fadeStart(1.f, 3.f);
}

bool iPlayerDead::eventUpdate()
{

	if (CAMERA->getIsFadeOut() && !CAMERA->getIsZoom())
	{
		SOUNDMANAGER->stopAll("");
		SCENEMANAGER->loadScene(L"town");
		_player->setPlayerHP(_player->getPlayerMaxHP());
		_player->setState(PLAYERSTATE::IDLE);
		_player->setDirection(PLAYERDIRECTION::BOTTOM);
		_player->setPosition(Vector2(500, 1600));
		return true;
	}

	return false;
}
