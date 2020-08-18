#include "stdafx.h"
#include "hedgehag.h"
#include "scene.h"

HRESULT hedgehag::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyHedgehog", L"images/enemy/hedgehog.png", 10, 7);//���ʹ� �̹���
	EFFECTMANAGER->addEffect("enemyHedgehogDust", "images/enemy/hedgehogDust.png", 240, 102, 48, 102, 1.0f, 0.5f, 200, 1.0f);//���ݻ��¿��� ���ڸ��� ������ ���� ����Ʈ
	EFFECTMANAGER->addEffect("enemyHedgehogMoveDust", "images/enemy/hedgehogMoveDust.png", 240, 51, 48, 51, 1.0f, 0.5f, 200, 1.0f);//���ݻ��¿��� �����̴��߿� ������ ���� ����Ʈ

	_name = "hedgehag";

	_maxHP = 100;
	_currentHP = _maxHP;

	_speed = 5.0f;
	_noHitSpeed = 1.0f;
	_attackSpeed = 10.0f;

	_attackPower = RND->getFromIntTo(2, 6);

	_maxAttackDelay = 100;
	_attackDelay = 0;

	_count = 0;
	_attackCount = 0;
	_hitCount = 0;

	_isAttack = false;
	_distanceChange = false;
	_effect = false;
	_idleMove = false;

	//����ġ �⺻ �ִϸ��̼�
	_idleMotion_L = new animation;
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_L->setPlayFrame(49, 46, false, true);
	_idleMotion_L->setFPS(1);

	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_R->setPlayFrame(53, 50, false, true);
	_idleMotion_R->setFPS(1);
	//����ġ �⺻ �ִϸ��̼�

	//����ġ ���� �⺻ �ִϸ��̼�
	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_L->setPlayFrame(9, 6, false, true);
	_idleMotion_U_L->setFPS(1);

	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_R->setPlayFrame(13, 10, false, true);
	_idleMotion_U_R->setFPS(1);
	//����ġ ���� �⺻ �ִϸ��̼�

	//����ġ �Ʒ��� �⺻ �ִϸ��̼�
	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_L->setPlayFrame(29, 26, false, true);
	_idleMotion_D_L->setFPS(1);

	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_R->setPlayFrame(33, 30, false, true);
	_idleMotion_D_R->setFPS(1);
	//����ġ �Ʒ��� �⺻ �ִϸ��̼�

	//����ġ ���� �ִϸ��̼�
	_moveMotion_L = new animation;
	_moveMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_L->setPlayFrame(45, 42, false, true);
	_moveMotion_L->setFPS(1);

	_moveMotion_R = new animation;
	_moveMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_R->setPlayFrame(57, 54, false, true);
	_moveMotion_R->setFPS(1);
	//����ġ ���� �ִϸ��̼�

	//����ġ ���� ���� �ִϸ��̼�
	_moveMotion_U_L = new animation;
	_moveMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_U_L->setPlayFrame(5, 2, false, true);
	_moveMotion_U_L->setFPS(1);

	_moveMotion_U_R = new animation;
	_moveMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_U_R->setPlayFrame(17, 14, false, true);
	_moveMotion_U_R->setFPS(1);
	//����ġ ���� ���� �ִϸ��̼�

	//����ġ �Ʒ��� ���� �ִϸ��̼�
	_moveMotion_D_L = new animation;
	_moveMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_D_L->setPlayFrame(25, 22, false, true);
	_moveMotion_D_L->setFPS(1);

	_moveMotion_D_R = new animation;
	_moveMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_D_R->setPlayFrame(37, 34, false, true);
	_moveMotion_D_R->setFPS(1);
	//����ġ �Ʒ��� ���� �ִϸ��̼�

	//����ġ ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_L = new animation;
	_hitMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_L->setPlayFrame(41, 40, false, false);
	_hitMotion_L->setFPS(1);

	_hitMotion_R = new animation;
	_hitMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_R->setPlayFrame(59, 58, false, false);
	_hitMotion_R->setFPS(1);
	//����ġ ���ݴ��Ҷ� �ִϸ��̼�

	//����ġ ���� ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_U_L->setPlayFrame(1, 0, false, false);
	_hitMotion_U_L->setFPS(1);

	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_U_R->setPlayFrame(19, 18, false, false);
	_hitMotion_U_R->setFPS(1);
	//����ġ ���� ���ݴ��Ҷ� �ִϸ��̼�

	//����ġ �Ʒ��� ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_D_L->setPlayFrame(21, 20, false, false);
	_hitMotion_D_L->setFPS(1);

	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_D_R->setPlayFrame(39, 38, false, false);
	_hitMotion_D_R->setFPS(1);
	//����ġ �Ʒ��� ���ݴ��Ҷ� �ִϸ��̼�

	//����ġ ���� �ִϸ��̼�
	_attackMotion_L = new animation;
	_attackMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_L->setPlayFrame(63, 62, false, true);
	_attackMotion_L->setFPS(1);

	_attackMotion_R = new animation;
	_attackMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_R->setPlayFrame(65, 64, false, true);
	_attackMotion_R->setFPS(1);
	//����ġ ���� �ִϸ��̼�

	//����ġ ���Ʒ� ���� �ִϸ��̼�
	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_U_L->setPlayFrame(61, 60, false, true);
	_attackMotion_U_L->setFPS(1);

	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_U_R->setPlayFrame(67, 66, false, true);
	_attackMotion_U_R->setFPS(1);
	//����ġ ���Ʒ� ���� �ִϸ��̼�

	_rc.update(_position, Vector2(70, 70), pivot::CENTER);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);
	
	_nowOrder = 1;
	//_angleCount = 0;

	return S_OK;
}

void hedgehag::release()
{
}

void hedgehag::update()
{
	tileGet();//���ʹ��� Ÿ�ϰ��� ��ġ ��������
	move();//���ʹ� ����
	animationControl();//���ʹ� �ִϸ��̼� ��Ʈ��
	animationAngleControl();//���ʹ̿� �÷��̾�� �ޱ۰��� ���� �ִϸ��̼� ��Ʈ��
	_enemyMotion->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);//���ʹ� �ִϸ��̼� ������Ʈ
	angry();//���ʹ��� ü���� ���� ���ϰ� �Ǹ� �ɷ�ġ ���(���ݷ�, ���ǵ�, ���ݵ�����)
	if (_effect)//���ʹ̰� ���ݻ��¿��� �������� �������
	{
		EFFECTMANAGER->play("enemyHedgehogDust", _rc.getCenter().x - 25, _rc.getCenter().y);
		EFFECTMANAGER->play("enemyHedgehogDust", _rc.getCenter().x + 25, _rc.getCenter().y);
	}
	if (!_effect && _isAttack)//���ʹ̰� ���ݻ����̰� �����������
	{
		EFFECTMANAGER->play("enemyHedgehogMoveDust", _rc.getCenter().x, _rc.getCenter().y);
	}
}

void hedgehag::render()
{
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_attackRC), D2DRenderer::DefaultBrush::Black, 2.f);//���ʹ� ���ݷ�Ʈ
	_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
	_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ʹ� �ִϸ��̼� ���
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));//���ʹ� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_t[i]->getRect()));
	}

	for (int i = 0; i < _move.size(); ++i)
	{
		D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_move[i]->getRect()));
	}
	//RectangleMakeCenter(getMemDC(), _rc.getCenter().x, _rc.getCenter().y, 10, 10);
	//RectangleMakeCenter(getMemDC(), _playerX, _playerY, 10, 10);
}

void hedgehag::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x;
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y;

	_distance = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);
	_angle = getAngle(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);

	if (_maxHP > _currentHP)//���ʹ��� ���� ü���� �߽�hp���� �۾�����
	{
		_idleMove = false;

		if (_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
		{
			if (!_distanceChange && !_isAttack)//�÷��̾�� ���ʹ��� �Ÿ��� 250���� ũ��
			{
				if (_move.size() != NULL)
				{
					float d = getDistance(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					float an = getAngle(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					_position.x += cosf(an) * _speed;
					_position.y += -sinf(an) * _speed;


					if (d < 5)
					{
						deleteMove();
					}

				}

			}
			else if (_distanceChange)
			{
				if (_move.size() != NULL)
				{
					clearMove();
				}

				_attackDelay++;//���ݵ�����
				if (_attackDelay >= _maxAttackDelay && !_isAttack)
				{
					_angleSave = _angle;//���ʹ̿� �÷��̾�� �������� �ӽ������� �����س��� ����
					_playerSaveX = _playerX;//�÷��̾��� ��ǥ�� �Ͻ������� �����س��� ����
					_playerSaveY = _playerY;//�÷��̾��� ��ǥ�� �Ͻ������� �����س��� ����
					_isAttack = true;//���ʹ� ���ݽ���
				}
			}

			if (_isAttack)//���ʹ� ���ݽ���
			{
				_effect = true;
				_attackCount++;//���ʹ� ���ݻ��¿��� �÷��̾�� �����ϱ������ ������
				_distanceSave = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerSaveX, _playerSaveY) + 200;//�Ͻ������� �����س��� �÷��̾� ��ǥ�� ���ʹ̰��� �Ÿ����� ������Ʈ �ϴ� ����
				_attackRC.update(Vector2(0, 0), Vector2(70, 70), pivot::CENTER);//���ʹ� ���ݷ�Ʈ

				if (_distanceSave > 10 && _distanceSave < 450)//���ʹ̿� �÷��̾�� �ӽ������� �����س��� �Ÿ����� 10���� ũ�� ��� �̵�
				{
					if (_attackCount >= 25)//���ʹ� ���ݻ��¿��� �÷��̾�� �����ϱ������ ������
					{
						if (tileMove())
						{
							_position.x += cosf(_angleSave) * _attackSpeed;
							_position.y -= sinf(_angleSave) * _attackSpeed;
							_effect = false;
						}
						else
						{
							//_angleSave += PI;
							//_angleCount++;
							//if (_angleCount % 10 == 0)
							//{
							_effect = false;
							_isAttack = false;
							_attackDelay = 0;//���ݵ�����
							_attackCount = 0;//���ʹ� ���ݻ��¿��� �÷��̾�� �����ϱ������ ������
							//_angleCount = 0;
						//}
						}
					}
				}
				else if (_distanceSave < 10 || _distanceSave > 450)
				{
					_effect = false;
					_isAttack = false;
					_attackDelay = 0;//���ݵ�����
					_attackCount = 0;//���ʹ� ���ݻ��¿��� �÷��̾�� �����ϱ������ ������
				}
			}

			if (_distance > 250)//�÷��̾�� ���ʹ��� �Ÿ��� 250���� ũ��
			{
				_distanceChange = false;
			}
			else
			{
				_distanceChange = true;
			}
		}

		if (!_isAttack)//���ʹ��� ���ݻ��°��� �޽���
		{
			_attackRC.update(Vector2(0, 0), Vector2(0, 0), pivot::CENTER);//���ʹ��� ���� ��Ʈũ�� 0
		}

		if (!tileMove())
		{
			_position.x += cosf(_angle) * _speed;
			_position.y += -sinf(_angle) * _speed;
		}
	}
	else//�������� ���� �ʾ�����
	{
		if (!_idleMove)
		{
			_playerSaveX = _position.x + RND->getFromIntTo(-50, 50);
			_playerSaveY = _position.y + RND->getFromIntTo(-50, 50);
			_idleMove = true;
		}

		_distanceSave = getDistance(_position.x, _position.y, _playerSaveX, _playerSaveY);
		_angleSave = getAngle(_position.x, _position.y, _playerSaveX, _playerSaveY);

		if (_distanceSave > 10 && tileMove())
		{
			_position.x += cosf(_angleSave) * _noHitSpeed;
			_position.y += -sinf(_angleSave) * _noHitSpeed;
		}
		else
		{
			_position.x += cosf(_angleSave + PI) * _noHitSpeed;
			_position.y += -sinf(_angleSave + PI) * _noHitSpeed;
			_idleMove = false;
		}
	}

	_rc.set(_position, pivot::CENTER);//���ʹ� ��Ʈ ��ġ ������Ʈ
	_attackRC.set(_position, pivot::CENTER);//���ʹ� ���� ��Ʈ ��ġ ������Ʈ
}

void hedgehag::tileGet()
{
	_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);

	int k = 1;
	currentTileIndex = Vector2(_tile.left / SIZE, _tile.top / SIZE);//���翡�ʹ� ��ġ�� Ÿ��

	if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//����
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x - k, currentTileIndex.y);
		nextTileIndex[1] = Vector2(currentTileIndex.x - k, currentTileIndex.y + k);
		nextTileIndex[2] = Vector2(currentTileIndex.x - k, currentTileIndex.y - k);
	}

	if (_angleSave * (180 / PI) >= 90 && _angleSave * (180 / PI) <= 135)//������
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x - k, currentTileIndex.y - k);
		nextTileIndex[1] = Vector2(currentTileIndex.x, currentTileIndex.y - k);
		nextTileIndex[2] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);
	}

	if (_angleSave * (180 / PI) >= 45 && _angleSave * (180 / PI) <= 90)//��������
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);
		nextTileIndex[1] = Vector2(currentTileIndex.x, currentTileIndex.y - k);
		nextTileIndex[2] = Vector2(currentTileIndex.x - k, currentTileIndex.y - k);
	}

	if ((_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45) || (_angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360))//������
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x + k, currentTileIndex.y);
		nextTileIndex[1] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);
		nextTileIndex[2] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);
	}

	if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//�Ʒ�������
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);
		nextTileIndex[1] = Vector2(currentTileIndex.x, currentTileIndex.y + k);
		nextTileIndex[2] = Vector2(currentTileIndex.x - k, currentTileIndex.y + k);
	}

	if (_angleSave * (180 / PI) >= 225 && _angleSave * (180 / PI) <= 270)//�Ʒ�����
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x - k, currentTileIndex.y + k);
		nextTileIndex[1] = Vector2(currentTileIndex.x, currentTileIndex.y + k);
		nextTileIndex[2] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);
	}

	int maxTileX = SCENEMANAGER->getCurrentSceneMapXSize();
	int maxTileY = SCENEMANAGER->getCurrentSceneMapYSize();

	//���� Ÿ��
	if (nextTileIndex[0].x > maxTileX) nextTileIndex[0].x = maxTileX;
	else if (nextTileIndex[0].x < 0) nextTileIndex[0].x = 0;
	if (nextTileIndex[0].y > maxTileY) nextTileIndex[0].y = maxTileY;
	else if (nextTileIndex[0].y < 0) nextTileIndex[0].y = 0;
	_t[0] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[0].y][nextTileIndex[0].x];

	//���� Ÿ��
	if (nextTileIndex[1].x > maxTileX) nextTileIndex[1].x = maxTileX;
	else if (nextTileIndex[1].x < 0) nextTileIndex[1].x = 0;
	if (nextTileIndex[1].y > maxTileY) nextTileIndex[1].y = maxTileY;
	else if (nextTileIndex[1].y < 0) nextTileIndex[1].y = 0;
	_t[1] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[1].y][nextTileIndex[1].x];

	//���� Ÿ��
	if (nextTileIndex[2].x > maxTileX) nextTileIndex[2].x = maxTileX;
	else if (nextTileIndex[2].x < 0) nextTileIndex[2].x = 0;
	if (nextTileIndex[2].y > maxTileY) nextTileIndex[2].y = maxTileY;
	else if (nextTileIndex[2].y < 0) nextTileIndex[2].y = 0;
	_t[2] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[2].y][nextTileIndex[2].x];
}

bool hedgehag::tileMove()
{
	//���� ���ٸ�
	if (_t[0]->getOrderIndex() == _nowOrder && _t[1]->getOrderIndex() == _nowOrder && _t[2]->getOrderIndex() == _nowOrder)
	{
		return true;
	}
	else
	{
		//_x = currentTileIndex.x * SIZE;
		//_y = currentTileIndex.y * SIZE;
		return false;
	}

	////���� �÷��̾�� ���ٸ�
	//else if (_t[0]->getOrderIndex() > _nowOrder)
	//{
	//	//�� �� ���̶��
	//	if (_t[0]->getOrderIndex() - _nowOrder == 1)
	//	{
	//		return false;
	//	}
	//	return false;
	//}
	////���� �÷��̾�� ���ٸ�
	//else
	//{
	//	if (_nowOrder == 0) return false;
	//}

}

void hedgehag::animationControl()
{
	_attackRC.update(Vector2(0, 0), Vector2(0, 0), pivot::CENTER);
	switch (_enemyDirection)
	{
	case ENEMY_LEFT_IDLE:
		_enemyMotion = _idleMotion_L;
		break;
	case ENEMY_RIGHT_IDLE:
		_enemyMotion = _idleMotion_R;
		break;
	case ENEMY_UP_LEFT_IDLE:
		_enemyMotion = _idleMotion_U_L;
		break;
	case ENEMY_UP_RIGHT_IDLE:
		_enemyMotion = _idleMotion_U_R;
		break;
	case ENEMY_DOWN_LEFT_IDLE:
		_enemyMotion = _idleMotion_D_L;
		break;
	case ENEMY_DOWN_RIGHT_IDLE:
		_enemyMotion = _idleMotion_D_R;
		break;
	case ENEMY_LEFT_MOVE:
		_enemyMotion = _moveMotion_L;
		break;
	case ENEMY_RIGHT_MOVE:
		_enemyMotion = _moveMotion_R;
		break;
	case ENEMY_UP_LEFT_MOVE:
		_enemyMotion = _moveMotion_U_L;
		break;
	case ENEMY_UP_RIGHT_MOVE:
		_enemyMotion = _moveMotion_U_R;
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		_enemyMotion = _moveMotion_D_L;
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		_enemyMotion = _moveMotion_D_R;
		break;
	case ENEMY_LEFT_HIT:
		_enemyMotion = _hitMotion_L;
		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_LEFT_IDLE;
		}
		break;
	case ENEMY_RIGHT_HIT:
		_enemyMotion = _hitMotion_R;
		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_RIGHT_IDLE;
		}
		break;
	case ENEMY_UP_LEFT_HIT:
		_enemyMotion = _hitMotion_U_L;
		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_UP_LEFT_IDLE;
		}
		break;
	case ENEMY_UP_RIGHT_HIT:
		_enemyMotion = _hitMotion_U_R;
		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_UP_RIGHT_IDLE;
		}
		break;
	case ENEMY_DOWN_LEFT_HIT:
		_enemyMotion = _hitMotion_D_L;
		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
		}
		break;
	case ENEMY_DOWN_RIGHT_HIT:
		_enemyMotion = _hitMotion_D_R;
		_hitCount++;

		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
		}
		break;
	case ENEMY_LEFT_ATTACK:
		_enemyMotion = _attackMotion_L;
		break;
	case ENEMY_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_R;
		break;
	case ENEMY_UP_LEFT_ATTACK:
		_enemyMotion = _attackMotion_U_L;
		break;
	case ENEMY_UP_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_U_R;
		break;
	case ENEMY_DOWN_LEFT_ATTACK:
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		break;
	}

	if (!_enemyMotion->isPlay())
	{
		_enemyMotion->start();
	}
}

void hedgehag::animationAngleControl()
{
	if (_maxHP > _currentHP)//���ʹ��� ���� ü���� �߽�HP���� �۾�����
	{
		if (!_distanceChange && !_isAttack)//�÷��̾�� ���ʹ��� �Ÿ��� 250���� ũ��
		{
			if (_enemyDirection != ENEMY_LEFT_HIT &&
				_enemyDirection != ENEMY_UP_LEFT_HIT &&
				_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
				_enemyDirection != ENEMY_RIGHT_HIT &&
				_enemyDirection != ENEMY_UP_RIGHT_HIT &&
				_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
			{
				if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//����
				{
					_enemyDirection = ENEMY_LEFT_MOVE;
				}

				if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//������
				{
					_enemyDirection = ENEMY_UP_LEFT_MOVE;
				}

				if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//��������
				{
					_enemyDirection = ENEMY_UP_RIGHT_MOVE;
				}

				if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45) || (_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360))//������
				{
					_enemyDirection = ENEMY_RIGHT_MOVE;
				}

				if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//�Ʒ�������
				{
					_enemyDirection = ENEMY_DOWN_RIGHT_MOVE;
				}

				if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//�Ʒ�����
				{
					_enemyDirection = ENEMY_DOWN_LEFT_MOVE;
				}
			}
		}
		else
		{
			if (_enemyDirection != ENEMY_LEFT_HIT &&
				_enemyDirection != ENEMY_UP_LEFT_HIT &&
				_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
				_enemyDirection != ENEMY_RIGHT_HIT &&
				_enemyDirection != ENEMY_UP_RIGHT_HIT &&
				_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
			{
				if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//����
				{
					_enemyDirection = ENEMY_LEFT_IDLE;
				}

				if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//������
				{
					_enemyDirection = ENEMY_UP_LEFT_IDLE;
				}

				if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//��������
				{
					_enemyDirection = ENEMY_UP_RIGHT_IDLE;
				}

				if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45) || (_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360))//������
				{
					_enemyDirection = ENEMY_RIGHT_IDLE;
				}

				if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//�Ʒ�������
				{
					_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
				}

				if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//�Ʒ�����
				{
					_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
				}

				if (_isAttack)//���ʹ� ���ݽ���
				{
					if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225 &&
						_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_RIGHT_ATTACK ||
						_enemyDirection != ENEMY_RIGHT_ATTACK)//����
					{
						_enemyDirection = ENEMY_LEFT_ATTACK;
					}

					if ((_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135 &&
						_enemyDirection != ENEMY_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_RIGHT_ATTACK ||
						_enemyDirection != ENEMY_RIGHT_ATTACK) ||
						(_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270 &&
							_enemyDirection != ENEMY_LEFT_ATTACK ||
							_enemyDirection != ENEMY_UP_RIGHT_ATTACK ||
							_enemyDirection != ENEMY_RIGHT_ATTACK))//�������� ���ʾƷ�
					{
						_enemyDirection = ENEMY_UP_LEFT_ATTACK;
					}

					if ((_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90 &&
						_enemyDirection != ENEMY_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
						_enemyDirection != ENEMY_RIGHT_ATTACK) ||
						(_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315 &&
							_enemyDirection != ENEMY_LEFT_ATTACK ||
							_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
							_enemyDirection != ENEMY_RIGHT_ATTACK))//���������� �����ʾƷ�
					{
						_enemyDirection = ENEMY_UP_RIGHT_ATTACK;
					}

					if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45 &&
						_enemyDirection != ENEMY_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
						_enemyDirection != ENEMY_UP_RIGHT_ATTACK) ||//������ 
						(_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360 &&
							_enemyDirection != ENEMY_LEFT_ATTACK ||
							_enemyDirection != ENEMY_UP_LEFT_ATTACK ||
							_enemyDirection != ENEMY_UP_RIGHT_ATTACK))
					{
						_enemyDirection = ENEMY_RIGHT_ATTACK;
					}
				}
			}
		}
	}
	else//�������� ���� �ʾ�����
	{
		if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//����
		{
			_enemyDirection = ENEMY_LEFT_MOVE;
		}

		if (_angleSave * (180 / PI) >= 90 && _angleSave * (180 / PI) <= 135)//������
		{
			_enemyDirection = ENEMY_UP_LEFT_MOVE;
		}

		if (_angleSave * (180 / PI) >= 45 && _angleSave * (180 / PI) <= 90)//��������
		{
			_enemyDirection = ENEMY_UP_RIGHT_MOVE;
		}

		if ((_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45) || (_angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360))//������
		{
			_enemyDirection = ENEMY_RIGHT_MOVE;
		}

		if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//�Ʒ�������
		{
			_enemyDirection = ENEMY_DOWN_RIGHT_MOVE;
		}

		if (_angleSave * (180 / PI) >= 225 && _angleSave * (180 / PI) <= 270)//�Ʒ�����
		{
			_enemyDirection = ENEMY_DOWN_LEFT_MOVE;
		}
	}
}


