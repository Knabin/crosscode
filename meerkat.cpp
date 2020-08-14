#include "stdafx.h"
#include "meerkat.h"
#include "scene.h"

HRESULT meerkat::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyMeerkat", "images/enemy/meerkat.bmp", 960, 1440, 10, 12, true, RGB(255, 0, 255));//�⺻, ��Ʈ, ���ݸ�� �̹���
	_meerkatMoveImage = IMAGEMANAGER->addFrameImage("enemyMeerkatMove", "images/enemy/meerkatMove.bmp", 576, 65, 9, 1, true, RGB(255, 0, 255));//���� �̹���

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
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_L->setPlayFrame(39, 36, false, true);
	_idleMotion_L->setFPS(1);

	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_R->setPlayFrame(20, 23, false, true);
	_idleMotion_R->setFPS(1);
	//�̾�Ĺ �⺻ �ִϸ��̼�

	//�̾�Ĺ ���� �⺻ �ִϸ��̼�
	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_U_L->setPlayFrame(19, 16, false, true);
	_idleMotion_U_L->setFPS(1);

	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_U_R->setPlayFrame(0, 3, false, true);
	_idleMotion_U_R->setFPS(1);
	//�̾�Ĺ ���� �⺻ �ִϸ��̼�

	//�̾�Ĺ �Ʒ��� �⺻ �ִϸ��̼�
	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_D_L->setPlayFrame(59, 56, false, true);
	_idleMotion_D_L->setFPS(1);

	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_idleMotion_D_R->setPlayFrame(40, 43, false, true);
	_idleMotion_D_R->setFPS(1);
	//�̾�Ĺ �Ʒ��� �⺻ �ִϸ��̼�

	//�̾�Ĺ ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_L = new animation;
	_hitMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_L->setPlayFrame(31, 30, false, false);
	_hitMotion_L->setFPS(1);

	_hitMotion_R = new animation;
	_hitMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_R->setPlayFrame(29, 28, false, false);
	_hitMotion_R->setFPS(1);
	//�̾�Ĺ ���ݴ��Ҷ� �ִϸ��̼�

	//�̾�Ĺ ���� ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_U_L->setPlayFrame(11, 10, false, false);
	_hitMotion_U_L->setFPS(1);

	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_U_R->setPlayFrame(9, 8, false, false);
	_hitMotion_U_R->setFPS(1);
	//�̾�Ĺ ���� ���ݴ��Ҷ� �ִϸ��̼�

	//�̾�Ĺ �Ʒ��� ���ݴ��Ҷ� �ִϸ��̼�
	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_D_L->setPlayFrame(51, 50, false, false);
	_hitMotion_D_L->setFPS(1);

	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_hitMotion_D_R->setPlayFrame(49, 48, false, false);
	_hitMotion_D_R->setFPS(1);
	//�̾�Ĺ �Ʒ��� ���ݴ��Ҷ� �ִϸ��̼�

	//�̾�Ĺ ���� �ִϸ��̼�
	_attackMotion_L = new animation;
	_attackMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_L->setPlayFrame(35, 32, false, false);
	_attackMotion_L->setFPS(1);

	_attackMotion_R = new animation;
	_attackMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_R->setPlayFrame(24, 27, false, false);
	_attackMotion_R->setFPS(1);
	//�̾�Ĺ ���� �ִϸ��̼�

	//�̾�Ĺ ���� ���� �ִϸ��̼�
	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_U_L->setPlayFrame(15, 12, false, false);
	_attackMotion_U_L->setFPS(1);

	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_U_R->setPlayFrame(4, 7, false, false);
	_attackMotion_U_R->setFPS(1);
	//�̾�Ĺ ���� ���� �ִϸ��̼�

	//�̾�Ĺ �Ʒ��� ���� �ִϸ��̼�
	_attackMotion_D_L = new animation;
	_attackMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_D_L->setPlayFrame(55, 52, false, false);
	_attackMotion_D_L->setFPS(1);

	_attackMotion_D_R = new animation;
	_attackMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_attackMotion_D_R->setPlayFrame(44, 47, false, false);
	_attackMotion_D_R->setFPS(1);
	//�̾�Ĺ �Ʒ��� ���� �ִϸ��̼�

	//�̾�Ĺ�� �������� ���� �ִϸ��̼�
	_meerkatTunnelDownMotion_L = new animation;
	_meerkatTunnelDownMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_meerkatTunnelDownMotion_L->setPlayFrame(71, 79, false, false);
	_meerkatTunnelDownMotion_L->setFPS(1);

	_meerkatTunnelDownMotion_R = new animation;
	_meerkatTunnelDownMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_meerkatTunnelDownMotion_R->setPlayFrame(68, 60, false, false);
	_meerkatTunnelDownMotion_R->setFPS(1);
	//�̾�Ĺ�� �������� ���� �ִϸ��̼�

	//�̾�Ĺ�� ���ӿ��� ������ �ִϸ��̼�
	_meerkatTunnelUpMotion_L = new animation;
	_meerkatTunnelUpMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_meerkatTunnelUpMotion_L->setPlayFrame(79, 71, false, false);
	_meerkatTunnelUpMotion_L->setFPS(1);

	_meerkatTunnelUpMotion_R = new animation;
	_meerkatTunnelUpMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight());
	_meerkatTunnelUpMotion_R->setPlayFrame(60, 68, false, false);
	_meerkatTunnelUpMotion_R->setFPS(1);
	//�̾�Ĺ�� ���ӿ��� ������ �ִϸ��̼�

	//�̾�Ĺ ���� �ִϸ��̼�
	_meerkatMoveMotion = new animation;
	_meerkatMoveMotion->init(_meerkatMoveImage->getWidth(), _meerkatMoveImage->getHeight(), _meerkatMoveImage->getFrameWidth(), _meerkatMoveImage->getFrameHeight());
	_meerkatMoveMotion->setPlayFrame(0, 8, false, true);
	_meerkatMoveMotion->setFPS(1);
	//�̾�Ĺ ���� �ִϸ��̼�

	_rc.set(0, 0, 70, 70);
	_rc.setCenter(_x, _y);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	_tile.set(0, 0, 48, 48);
	_nowOrder = 1;

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
}

void meerkat::render()
{
	_attackRC.render(getMemDC());//���ʹ� ���ݷ�Ʈ
	if (_enemyDirection != ENEMY_TUNNEL_MOVE)
	{
		_enemyImage->aniRender(getMemDC(), _rc.getCenter().x - (_enemyImage->getFrameWidth() / 2), _rc.getCenter().y - (_enemyImage->getFrameHeight() / 2), _enemyMotion);
	}
	else
	{
		_meerkatMoveImage->aniRender(getMemDC(), _rc.getCenter().x - (_meerkatMoveImage->getFrameWidth() / 2), _rc.getCenter().y - (_meerkatMoveImage->getFrameHeight() / 2), _enemyMotion);
	}
	//_rc.render(getMemDC());//���ʹ� ��Ʈ
	for (int i = 0; i < 8; i++)
	{
		//RectangleMake(getMemDC(), _t[i]->getRect().getCenter().x, _t[i]->getRect().getCenter().y, SIZE, SIZE);
	}
}

void meerkat::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getX();
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getY();

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

				if (!tileMove() && !_reflect && !_isBigMove)//�̾�Ĺ �ֺ��� ��ֹ��� �ְ� ��ֹ��� �ݴ�������� �̵��ǰ� �ϱ����� ����
				{
					_angleSave += PI;//��ֹ��� �ݴ�������� �̵�
					_reflect = true;
				}
			}

			if (tileMove() && !_isBigMove)//��ֹ��� �Ⱥε�������
			{
				if (_isMove && _distance <= _smallDistance + _smallDistance / 2)
				{
					if (_playerX < _x)
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
						_x += cosf(_angleSave) * _meerkatSpeed;
						_y += -sinf(_angleSave) * _meerkatSpeed;
					}
					
				}
				else
				{
					cout << "2" << endl;

					if (_playerX < _x)
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
					_isMove = false;
				}
			}

			if (!tileMove() && _reflect && !_isBigMove)//�̾�Ĺ �ֺ��� ��ֹ��� �ְ� ��ֹ��� �ݴ�������� �̵��ǰ� �ϱ����� ����
			{
				if (_playerX < _x)
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
					_x += cosf(_angleSave) * _meerkatSpeed;
					_y += -sinf(_angleSave) * _meerkatSpeed;
				}
				_reflectCount++;//��ֹ��� �ε������� ��ֹ��� �ε��� Ƚ�� ī��Ʈ����
			}

			if (_reflectCount >= 2 && !_isBigMove)//���� �ε��� Ƚ���� 2�� �̻��̰� �򹫺�� �޽��ΰ��
			{
				_angleSave += PI / 2;//���� �ε������� �������� 90�� Ʋ���ֱ� ���� ����
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
					float d = getDistance(_x, _y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					float an = getAngle(_x, _y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);

					if (_playerX < _x)
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
						_x += cosf(an) * _meerkatSpeed;
						_y += -sinf(an) * _meerkatSpeed;
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

	_rc.setCenter(_x, _y);
}

void meerkat::animationControl()
{
	switch (_enemyDirection)
	{
	case ENEMY_LEFT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_RIGHT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_LEFT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_RIGHT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_IDLE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _idleMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_RIGHT_IDLE:
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_LEFT_ATTACK:
		_enemyMotion = _attackMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_ATTACK:
		_enemyMotion = _attackMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		_enemyMotion = _attackMotion_D_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_TUNNEL_MOVE:
		_attackRC.set(0, 0, 0, 0);
		_enemyMotion = _meerkatMoveMotion;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_TUNNEL:
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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
		_attackRC.set(0, 0, 0, 0);
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
	_tile.setLeftTop(((int)_x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE);

	int k = 1;
	currentTileIndex = { _tile.left / SIZE, _tile.top / SIZE };//���翡�ʹ� ��ġ�� Ÿ��

	nextTileIndex[0] = { currentTileIndex.x - k, currentTileIndex.y };//����
	nextTileIndex[1] = { currentTileIndex.x - k, currentTileIndex.y + k };//���ʾƷ�
	nextTileIndex[2] = { currentTileIndex.x, currentTileIndex.y + k };//�Ʒ�
	nextTileIndex[3] = { currentTileIndex.x + k, currentTileIndex.y + k };//������ �Ʒ�
	nextTileIndex[4] = { currentTileIndex.x + k, currentTileIndex.y };//������
	nextTileIndex[5] = { currentTileIndex.x + k, currentTileIndex.y - k };//��������
	nextTileIndex[6] = { currentTileIndex.x, currentTileIndex.y - k };//��
	nextTileIndex[7] = { currentTileIndex.x - k, currentTileIndex.y - k };//������

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
