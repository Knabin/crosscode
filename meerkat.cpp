#include "stdafx.h"
#include "meerkat.h"
#include "scene.h"
#include "bullets.h"

HRESULT meerkat::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyMeerkat", L"images/enemy/meerkat.png", 10, 12);//�⺻, ��Ʈ, ���ݸ�� �̹���
	_meerkatMoveImage = IMAGEMANAGER->addFrameImage("enemyMeerkatMove", L"images/enemy/meerkatMove.png", 9, 1);//���� �̹���

	_maxHP = 100;
	_currentHP = _maxHP;

	_meerkatSpeed = 10.0f;
	
	_attackPower = RND->getFromIntTo(2, 6);

	_maxAttackDelay = 100;
	_attackDelay = 0;

	_count = 0;
	_attackCount = 0;
	_hitCount = 0;
	_reflectCount = 0;
	_smallDistance = 250;
	_bigDistance = 500;

	_isAttack = false;
	_isMove = false;
	_reflect = false;
	_isBigMove = false;
	_oneAnimation = false;

	//�̾�Ĺ �⺻ �ִϸ��̼�
	_idleMotion_L = new animation;
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_L->setPlayFrame(39, 36, false, true);
	_idleMotion_L->setFPS(1);

	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_R->setPlayFrame(20, 23, false, true);
	_idleMotion_R->setFPS(1);
	//�̾�Ĺ �⺻ �ִϸ��̼�

	//�̾�Ĺ ���� �⺻ �ִϸ��̼�
	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_L->setPlayFrame(19, 16, false, true);
	_idleMotion_U_L->setFPS(1);

	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_R->setPlayFrame(0, 3, false, true);
	_idleMotion_U_R->setFPS(1);
	//�̾�Ĺ ���� �⺻ �ִϸ��̼�

	//�̾�Ĺ �Ʒ��� �⺻ �ִϸ��̼�
	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_L->setPlayFrame(59, 56, false, true);
	_idleMotion_D_L->setFPS(1);

	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_R->setPlayFrame(40, 43, false, true);
	_idleMotion_D_R->setFPS(1);
	//�̾�Ĺ �Ʒ��� �⺻ �ִϸ��̼�

	//�̾�Ĺ ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_L = new animation;
	_hitMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_L->setPlayFrame(31, 30, false, false);
	_hitMotion_L->setFPS(1);

	_hitMotion_R = new animation;
	_hitMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_R->setPlayFrame(29, 28, false, false);
	_hitMotion_R->setFPS(1);
	//�̾�Ĺ ���ݴ��Ҷ� �ִϸ��̼�

	//�̾�Ĺ ���� ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_U_L->setPlayFrame(11, 10, false, false);
	_hitMotion_U_L->setFPS(1);

	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_U_R->setPlayFrame(9, 8, false, false);
	_hitMotion_U_R->setFPS(1);
	//�̾�Ĺ ���� ���ݴ��Ҷ� �ִϸ��̼�

	//�̾�Ĺ �Ʒ��� ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_D_L->setPlayFrame(51, 50, false, false);
	_hitMotion_D_L->setFPS(1);

	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_hitMotion_D_R->setPlayFrame(49, 48, false, false);
	_hitMotion_D_R->setFPS(1);
	//�̾�Ĺ �Ʒ��� ���ݴ��Ҷ� �ִϸ��̼�

	//�̾�Ĺ ���� �ִϸ��̼�
	_attackMotion_L = new animation;
	_attackMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_L->setPlayFrame(35, 32, false, false);
	_attackMotion_L->setFPS(1);

	_attackMotion_R = new animation;
	_attackMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_R->setPlayFrame(24, 27, false, false);
	_attackMotion_R->setFPS(1);
	//�̾�Ĺ ���� �ִϸ��̼�

	//�̾�Ĺ ���� ���� �ִϸ��̼�
	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_U_L->setPlayFrame(15, 12, false, false);
	_attackMotion_U_L->setFPS(1);

	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_U_R->setPlayFrame(4, 7, false, false);
	_attackMotion_U_R->setFPS(1);
	//�̾�Ĺ ���� ���� �ִϸ��̼�

	//�̾�Ĺ �Ʒ��� ���� �ִϸ��̼�
	_attackMotion_D_L = new animation;
	_attackMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_D_L->setPlayFrame(55, 52, false, false);
	_attackMotion_D_L->setFPS(1);

	_attackMotion_D_R = new animation;
	_attackMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackMotion_D_R->setPlayFrame(44, 47, false, false);
	_attackMotion_D_R->setFPS(1);
	//�̾�Ĺ �Ʒ��� ���� �ִϸ��̼�

	//�̾�Ĺ�� �������� ���� �ִϸ��̼�
	_meerkatTunnelDownMotion_L = new animation;
	_meerkatTunnelDownMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_meerkatTunnelDownMotion_L->setPlayFrame(71, 79, false, false);
	_meerkatTunnelDownMotion_L->setFPS(2);

	_meerkatTunnelDownMotion_R = new animation;
	_meerkatTunnelDownMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_meerkatTunnelDownMotion_R->setPlayFrame(68, 60, false, false);
	_meerkatTunnelDownMotion_R->setFPS(2);
	//�̾�Ĺ�� �������� ���� �ִϸ��̼�

	//�̾�Ĺ�� ���ӿ��� ������ �ִϸ��̼�
	_meerkatTunnelUpMotion_L = new animation;
	_meerkatTunnelUpMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_meerkatTunnelUpMotion_L->setPlayFrame(79, 71, false, false);
	_meerkatTunnelUpMotion_L->setFPS(2);

	_meerkatTunnelUpMotion_R = new animation;
	_meerkatTunnelUpMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_meerkatTunnelUpMotion_R->setPlayFrame(60, 68, false, false);
	_meerkatTunnelUpMotion_R->setFPS(2);
	//�̾�Ĺ�� ���ӿ��� ������ �ִϸ��̼�

	//�̾�Ĺ ���� �ִϸ��̼�
	_meerkatMoveMotion = new animation;
	_meerkatMoveMotion->init(_meerkatMoveImage->getWidth(), _meerkatMoveImage->getHeight(), _meerkatMoveImage->getFrameSize().x, _meerkatMoveImage->getFrameSize().y);
	_meerkatMoveMotion->setPlayFrame(0, 8, false, true);
	_meerkatMoveMotion->setFPS(1);
	//�̾�Ĺ ���� �ִϸ��̼�

	_rc.update(_position, Vector2(70, 70), pivot::CENTER);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);
	_nowOrder = 1;

	_bullet = new bullets;
	_bullet->init();

	return S_OK;
}

void meerkat::release()
{
}

void meerkat::update()
{
	tileGet();//���ʹ��� Ÿ����� ��ġ ������Ʈ
	move();//���ʹ� ����
	animationControl();//���ʹ� �ִϸ��̼� ��Ʈ��
	//animationAngleControl();//���ʹ̿� �÷��̾�� �ޱ۰��� ���� �ִϸ��̼� ��Ʈ��
	_enemyMotion->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	angry();//���ʹ��� ü���� ���� ���ϰ� �Ǹ� �ɷ�ġ ���(���ǵ�, ���ݷ�, ���ݵ�����)

	if (_isAttack)//���ݻ��°� Ʈ���
	{
		_bullet->fire(_position.x, _position.y, _angle, _meerkatSpeed);
		_isAttack = false;
	}
	_bullet->update();
}

void meerkat::render()
{
	if (_enemyDirection != ENEMY_TUNNEL_MOVE)
	{
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter()), _enemyMotion, 1.0f);
	}
	else
	{
		_meerkatMoveImage->setSize(Vector2(_meerkatMoveImage->getFrameSize()) * CAMERA->getZoomAmount());
		_meerkatMoveImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter()), _enemyMotion, 1.0f);
	}
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));//���ʹ� ��Ʈ
	for (int i = 0; i < 8; i++)
	{
		D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_t[i]->getRect()));
	}
	_bullet->render();
}

void meerkat::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x;
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y;

	_distance = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);
	_angle = getAngle(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);

	if (_maxHP > _currentHP)//���ʹ��� ���� ü���� �߽�HP���� �۾�����
	{
		if (_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
		{
			if (_distance <= _smallDistance && !_isBigMove)//�÷��̾�� ���ʹ��� �Ÿ��� ������
			{
				if (tileMove())//�̾�Ĺ �ֺ��� ��ֹ��� ������
				{
					if (!_isMove)//�÷��̾��� �ݴ�������� �̵���Ű�� ���� ������ �ѹ��� �ϱ����� ����
					{
						_angleSave = _angle + PI;
						_isMove = true;
					}
				}
				/*
				if (!tileMove() && !_reflect && !_isBigMove)//�̾�Ĺ �ֺ��� ��ֹ��� �ְ� ��ֹ��� �ݴ�������� �̵��ǰ� �ϱ����� ����
				{
					_angleSave += PI;//��ֹ��� �ݴ�������� �̵�
					_reflect = true;
				}
				*/
			}

			if (!tileMove() && !_reflect && !_isBigMove)//�̾�Ĺ �ֺ��� ��ֹ��� �ְ� ��ֹ��� �ݴ�������� �̵��ǰ� �ϱ����� ����
			{
				_angleSave += PI;//��ֹ��� �ݴ�������� �̵�
				_reflect = true;
			}

			if (tileMove() && !_isBigMove)//��ֹ��� �Ⱥε�������
			{
				if (_isMove && _distance <= _smallDistance + _smallDistance / 2)
				{
					if (_playerX < _position.x)
					{
						if (_enemyDirection != ENEMY_DOWN_LEFT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_DOWN_LEFT_TUNNEL;
						}
					}
					else
					{
						if (_enemyDirection != ENEMY_DOWN_RIGHT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_DOWN_RIGHT_TUNNEL;
						}
					}
						
					_reflect = false;

					if (_enemyDirection == ENEMY_TUNNEL_MOVE)
					{
						_position.x += cosf(_angleSave) * _meerkatSpeed;
						_position.y += -sinf(_angleSave) * _meerkatSpeed;
					}
					
				}
				else
				{
					if (_playerX < _position.x)
					{
						if (_enemyDirection == ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL)
						{
							_enemyDirection = ENEMY_UP_LEFT_TUNNEL;
						}
					}
					else
					{
						if (_enemyDirection == ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_UP_RIGHT_TUNNEL;
						}
					}

					_count++;

					if (_enemyDirection == ENEMY_DOWN_LEFT_IDLE && _count >= 50 ||
						_enemyDirection == ENEMY_DOWN_RIGHT_IDLE && _count >= 50 ||
						_enemyDirection == ENEMY_LEFT_IDLE && _count >= 50 ||
						_enemyDirection == ENEMY_RIGHT_IDLE && _count >= 50 ||
						_enemyDirection == ENEMY_UP_LEFT_IDLE && _count >= 50 ||
						_enemyDirection == ENEMY_UP_RIGHT_IDLE && _count >= 50)
					{
						if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//����
						{
							_enemyDirection = ENEMY_LEFT_ATTACK;
						}

						if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//������
						{
							_enemyDirection = ENEMY_UP_LEFT_ATTACK;
						}

						if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//��������
						{
							_enemyDirection = ENEMY_UP_RIGHT_ATTACK;
						}

						if (_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45 || _angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360)//������
						{
							_enemyDirection = ENEMY_RIGHT_ATTACK;
						}

						if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//�Ʒ�������
						{
							_enemyDirection = ENEMY_DOWN_RIGHT_ATTACK;
						}

						if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//�Ʒ�����
						{
							_enemyDirection = ENEMY_DOWN_LEFT_ATTACK;
						}

						_count = 0;
					}
					_isMove = false;
				}
			}

			if (!tileMove() && _reflect && !_isBigMove)//�̾�Ĺ �ֺ��� ��ֹ��� �ְ� ��ֹ��� �ݴ�������� �̵��ǰ� �ϱ����� ����
			{
				if (_playerX < _position.x)
				{
					if (_enemyDirection != ENEMY_DOWN_LEFT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
					{
						_enemyDirection = ENEMY_DOWN_LEFT_TUNNEL;
					}
				}
				else
				{
					if (_enemyDirection != ENEMY_DOWN_RIGHT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
					{
						_enemyDirection = ENEMY_DOWN_RIGHT_TUNNEL;
					}
				}
					
				if (_enemyDirection == ENEMY_TUNNEL_MOVE)
				{
					_position.x += cosf(_angleSave) * _meerkatSpeed;
					_position.y += -sinf(_angleSave) * _meerkatSpeed;
				}
				_reflectCount++;//��ֹ��� �ε������� ��ֹ��� �ε��� Ƚ�� ī��Ʈ����
			}

			if (_reflectCount >= 2 && !_isBigMove)//���� �ε��� Ƚ���� 2�� �̻��̰� �򹫺�� �޽��ΰ��
			{
				_angleSave += PI / RND->getFromIntTo(1, 4);//���� �ε������� �������� 90�� Ʋ���ֱ� ���� ����
				_reflectCount = 0;
			}

			if (_distance > _bigDistance)//�÷��̾�� �̾�Ĺ���� �Ÿ��� �ʹ� �հ��
			{
				_isBigMove = true;//�򹫺긦 �����ض�
			}

			if (_isBigMove)//�򹫺�
			{
				//���̽�Ÿ �̵�
				if (_move.size() != NULL)
				{
					float d = getDistance(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					float an = getAngle(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);

					if (_playerX < _position.x)
					{
						if (_enemyDirection != ENEMY_DOWN_LEFT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_DOWN_LEFT_TUNNEL;
						}
					}
					else
					{
						if (_enemyDirection != ENEMY_DOWN_RIGHT_TUNNEL && _enemyDirection != ENEMY_TUNNEL_MOVE && _enemyDirection != ENEMY_UP_LEFT_TUNNEL && _enemyDirection != ENEMY_UP_RIGHT_TUNNEL)
						{
							_enemyDirection = ENEMY_DOWN_RIGHT_TUNNEL;
						}
					}

					if (_enemyDirection == ENEMY_TUNNEL_MOVE)
					{
						_position.x += cosf(an) * _meerkatSpeed;
						_position.y += -sinf(an) * _meerkatSpeed;
					}
					
					if (d < 5)
					{
						deleteMove();
					}
				}
				//���̽�Ÿ �̵�
			}

			if (_distance <= _smallDistance + _smallDistance / 2)//�÷��̾�� �̾�Ĺ�� �Ÿ��� �����Ÿ� ���̸�
			{
				_isBigMove = false;//�򹫺긦 �����
			}
		}
	}

	_rc.set(_position, pivot::CENTER);
}

void meerkat::animationControl()
{
	switch (_enemyDirection)
	{
	case ENEMY_LEFT_IDLE:
		_enemyMotion = _idleMotion_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_RIGHT_IDLE:
		_enemyMotion = _idleMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_LEFT_IDLE:
		_enemyMotion = _idleMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_RIGHT_IDLE:
		_enemyMotion = _idleMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_IDLE:
		_enemyMotion = _idleMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_RIGHT_IDLE:
		_enemyMotion = _idleMotion_D_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_LEFT_MOVE:
		break;
	case ENEMY_RIGHT_MOVE:
		break;
	case ENEMY_UP_LEFT_MOVE:
		break;
	case ENEMY_UP_RIGHT_MOVE:
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		break;
	case ENEMY_LEFT_HIT:
		_enemyMotion = _hitMotion_L;

		_hitCount++;
		if (_hitCount >= 25)
		{
			_hitCount = 0;
			_enemyDirection = ENEMY_LEFT_IDLE;
		}

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
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

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
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

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
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

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
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

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
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

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_LEFT_ATTACK:
		_enemyMotion = _attackMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_LEFT_IDLE;
		}
		break;
	case ENEMY_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_RIGHT_IDLE;
		}
		break;
	case ENEMY_UP_LEFT_ATTACK:
		_enemyMotion = _attackMotion_U_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_UP_LEFT_IDLE;
		}
		break;
	case ENEMY_UP_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_U_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_UP_RIGHT_IDLE;
		}
		break;
	case ENEMY_DOWN_LEFT_ATTACK:
		_enemyMotion = _attackMotion_D_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
		}
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_D_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_isAttack = true;
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
		}
		break;
	case ENEMY_TUNNEL_MOVE:
		_enemyMotion = _meerkatMoveMotion;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_TUNNEL:
		_enemyMotion = _meerkatTunnelDownMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_enemyDirection = ENEMY_TUNNEL_MOVE;
		}
		break;
	case ENEMY_DOWN_RIGHT_TUNNEL:
		_enemyMotion = _meerkatTunnelDownMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_enemyDirection = ENEMY_TUNNEL_MOVE;
		}
		break;
	case ENEMY_UP_LEFT_TUNNEL:
		_enemyMotion = _meerkatTunnelUpMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
		}
		break;
	case ENEMY_UP_RIGHT_TUNNEL:
		_enemyMotion = _meerkatTunnelUpMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_oneAnimation = false;
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
		}
		break;
	}
}

void meerkat::animationAngleControl()
{
	if (_maxHP > _currentHP)//���ʹ��� ���� ü���� �߽�HP���� �۾�����
	{
		if (_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)//���ʹ̰� ��Ʈ �ִϸ��̼��� �ƴҰ��
		{
			if (!_isAttack)//���ʹ̰� �������� �ƴϸ�
			{
				if (_distance <= _smallDistance)//�÷��̾�� ���ʹ��� �Ÿ��� ������
				{
					_enemyDirection = ENEMY_TUNNEL_MOVE;

				}
				else if (_distance > _smallDistance && _distance < _bigDistance)//�÷��̾�� ���ʹ��� �Ÿ��� �����Ÿ��̻� �ְ� �ʹ����� ������
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

					if (_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45 || _angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360)//������
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
				}
				else//�÷��̾�� ���ʹ��� �Ÿ��� �ʹ� �ָ�
				{
					_enemyDirection = ENEMY_TUNNEL_MOVE;
				}
			}
			else//���ݻ��°��� Ʈ���
			{
				if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//����
				{
					_enemyDirection = ENEMY_LEFT_ATTACK;
				}

				if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//������
				{
					_enemyDirection = ENEMY_UP_LEFT_ATTACK;
				}

				if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//��������
				{
					_enemyDirection = ENEMY_UP_RIGHT_ATTACK;
				}

				if (_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45 || _angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360)//������
				{
					_enemyDirection = ENEMY_RIGHT_ATTACK;
				}

				if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//�Ʒ�������
				{
					_enemyDirection = ENEMY_DOWN_RIGHT_ATTACK;
				}

				if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//�Ʒ�����
				{
					_enemyDirection = ENEMY_DOWN_LEFT_ATTACK;
				}
			}
		}
	}
}

void meerkat::tileGet()
{
	_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);

	int k = 1;
	currentTileIndex = Vector2(_tile.left / SIZE, _tile.top / SIZE);//���翡�ʹ� ��ġ�� Ÿ��

	nextTileIndex[0] = Vector2(currentTileIndex.x - k, currentTileIndex.y);//����
	nextTileIndex[1] = Vector2(currentTileIndex.x - k, currentTileIndex.y + k);//���ʾƷ�
	nextTileIndex[2] = Vector2(currentTileIndex.x, currentTileIndex.y + k);//�Ʒ�
	nextTileIndex[3] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);//������ �Ʒ�
	nextTileIndex[4] = Vector2(currentTileIndex.x + k, currentTileIndex.y);//������
	nextTileIndex[5] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);//��������
	nextTileIndex[6] = Vector2(currentTileIndex.x, currentTileIndex.y - k);//��
	nextTileIndex[7] = Vector2(currentTileIndex.x - k, currentTileIndex.y - k);//������

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

	//���� Ÿ��
	if (nextTileIndex[3].x > maxTileX) nextTileIndex[3].x = maxTileX;
	else if (nextTileIndex[3].x < 0) nextTileIndex[3].x = 0;
	if (nextTileIndex[3].y > maxTileY) nextTileIndex[3].y = maxTileY;
	else if (nextTileIndex[3].y < 0) nextTileIndex[3].y = 0;
	_t[3] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[3].y][nextTileIndex[3].x];

	//���� Ÿ��
	if (nextTileIndex[4].x > maxTileX) nextTileIndex[4].x = maxTileX;
	else if (nextTileIndex[4].x < 0) nextTileIndex[4].x = 0;
	if (nextTileIndex[4].y > maxTileY) nextTileIndex[4].y = maxTileY;
	else if (nextTileIndex[4].y < 0) nextTileIndex[4].y = 0;
	_t[4] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[4].y][nextTileIndex[4].x];

	//���� Ÿ��
	if (nextTileIndex[5].x > maxTileX) nextTileIndex[5].x = maxTileX;
	else if (nextTileIndex[5].x < 0) nextTileIndex[5].x = 0;
	if (nextTileIndex[5].y > maxTileY) nextTileIndex[5].y = maxTileY;
	else if (nextTileIndex[5].y < 0) nextTileIndex[5].y = 0;
	_t[5] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[5].y][nextTileIndex[5].x];

	//���� Ÿ��
	if (nextTileIndex[6].x > maxTileX) nextTileIndex[6].x = maxTileX;
	else if (nextTileIndex[6].x < 0) nextTileIndex[6].x = 0;
	if (nextTileIndex[6].y > maxTileY) nextTileIndex[6].y = maxTileY;
	else if (nextTileIndex[6].y < 0) nextTileIndex[6].y = 0;
	_t[6] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[6].y][nextTileIndex[6].x];

	//���� Ÿ��
	if (nextTileIndex[7].x > maxTileX) nextTileIndex[7].x = maxTileX;
	else if (nextTileIndex[7].x < 0) nextTileIndex[7].x = 0;
	if (nextTileIndex[7].y > maxTileY) nextTileIndex[7].y = maxTileY;
	else if (nextTileIndex[7].y < 0) nextTileIndex[7].y = 0;
	_t[7] = SCENEMANAGER->getCurrentScene()->getTiles()[nextTileIndex[7].y][nextTileIndex[7].x];
}

bool meerkat::tileMove()
{
	//���� ���ٸ�
	if (_t[0]->getOrderIndex() == _nowOrder && _t[1]->getOrderIndex() == _nowOrder && _t[2]->getOrderIndex() == _nowOrder &&
		_t[3]->getOrderIndex() == _nowOrder && _t[4]->getOrderIndex() == _nowOrder && _t[5]->getOrderIndex() == _nowOrder &&
		_t[6]->getOrderIndex() == _nowOrder && _t[7]->getOrderIndex() == _nowOrder)
	{
		return true;
	}
	else
	{
		return false;
	}

}
