#include "stdafx.h"
#include "buffalo.h"
#include "scene.h"

HRESULT buffalo::init()
{
	_enemyImage = IMAGEMANAGER->addFrameImage("enemyIdleMoveAttackPrepare", L"images/enemy/buffalo_idle_move_attackPrepare.png", 6, 18);
	_attackImage = IMAGEMANAGER->addFrameImage("enemyAttack", L"images/enemy/buffalo_attack.png", 6, 12);
	_hitImage = IMAGEMANAGER->addFrameImage("enemyHit", L"images/enemy/buffalo_hit.png", 5, 6);

	_maxHP = 100;
	_currentHP = _maxHP;

	_speed = 5.0f;
	_noHitSpeed = 1.0f;
	_attackSpeed = 10.0f;

	_attackPower = RND->getFromIntTo(10, 20);

	_maxAttackDelay = 100;
	_attackDelay = 0;

	_count = 0;
	_attackCount = 0;
	_hitCount = 0;

	_isAttack = false;
	_distanceChange = false;
	_idleMove = false;
	_oneAnimation = false;

	//���ȷ� ���� �⺻ �ִϸ��̼�
	_idleMotion_U_R = new animation;
	_idleMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_R->setPlayFrame(0, 3, false, true);
	_idleMotion_U_R->setFPS(1);

	_idleMotion_U_L = new animation;
	_idleMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_U_L->setPlayFrame(21, 18, false, true);
	_idleMotion_U_L->setFPS(1);
	//���ȷ� ���� �⺻ �ִϸ��̼�

	//���ȷ� �⺻ �ִϸ��̼�
	_idleMotion_R = new animation;
	_idleMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_R->setPlayFrame(6, 9, false, true);
	_idleMotion_R->setFPS(1);

	_idleMotion_L = new animation;
	_idleMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_L->setPlayFrame(27, 24, false, true);
	_idleMotion_L->setFPS(1);
	//���ȷ� �⺻ �ִϸ��̼�

	//���ȷ� �Ʒ��� �⺻ �ִϸ��̼�
	_idleMotion_D_R = new animation;
	_idleMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_R->setPlayFrame(12, 15, false, true);
	_idleMotion_D_R->setFPS(1);

	_idleMotion_D_L = new animation;
	_idleMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_idleMotion_D_L->setPlayFrame(27, 24, false, true);
	_idleMotion_D_L->setFPS(1);
	//���ȷ� �Ʒ��� �⺻ �ִϸ��̼�

	//���ȷ� ���� ���� �ִϸ��̼�
	_moveMotion_U_R = new animation;
	_moveMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_U_R->setPlayFrame(36, 39, false, true);
	_moveMotion_U_R->setFPS(1);

	_moveMotion_U_L = new animation;
	_moveMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_U_L->setPlayFrame(57, 54, false, true);
	_moveMotion_U_L->setFPS(1);
	//���ȷ� ���� ���� �ִϸ��̼�

	//���ȷ� ���� �ִϸ��̼�
	_moveMotion_R = new animation;
	_moveMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_R->setPlayFrame(42, 45, false, true);
	_moveMotion_R->setFPS(1);

	_moveMotion_L = new animation;
	_moveMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_L->setPlayFrame(63, 60, false, true);
	_moveMotion_L->setFPS(1);
	//���ȷ� ���� �ִϸ��̼�

	//���ȷ� �Ʒ��� ���� �ִϸ��̼�
	_moveMotion_D_R = new animation;
	_moveMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_D_R->setPlayFrame(48, 51, false, true);
	_moveMotion_D_R->setFPS(1);

	_moveMotion_D_L = new animation;
	_moveMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_moveMotion_D_L->setPlayFrame(69, 66, false, true);
	_moveMotion_D_L->setFPS(1);
	//���ȷ� �Ʒ��� ���� �ִϸ��̼�

	//���ȷ� ���� ���������غ� �ִϸ��̼�
	_attackPrepareMotion_U_R = new animation;
	_attackPrepareMotion_U_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_U_R->setPlayFrame(72, 77, false, false);
	_attackPrepareMotion_U_R->setFPS(1);

	_attackPrepareMotion_U_L = new animation;
	_attackPrepareMotion_U_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_U_L->setPlayFrame(90, 85, false, false);
	_attackPrepareMotion_U_L->setFPS(1);
	//���ȷ� ���� ���������غ� �ִϸ��̼�

	//���ȷ� ���������غ� �ִϸ��̼�
	_attackPrepareMotion_R = new animation;
	_attackPrepareMotion_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_R->setPlayFrame(78, 83, false, false);
	_attackPrepareMotion_R->setFPS(1);

	_attackPrepareMotion_L = new animation;
	_attackPrepareMotion_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_L->setPlayFrame(101, 96, false, false);
	_attackPrepareMotion_L->setFPS(1);
	//���ȷ� ���������غ� �ִϸ��̼�

	//���ȷ� �Ʒ��� ���������غ� �ִϸ��̼�
	_attackPrepareMotion_D_R = new animation;
	_attackPrepareMotion_D_R->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_D_R->setPlayFrame(84, 89, false, false);
	_attackPrepareMotion_D_R->setFPS(1);

	_attackPrepareMotion_D_L = new animation;
	_attackPrepareMotion_D_L->init(_enemyImage->getWidth(), _enemyImage->getHeight(), _enemyImage->getFrameSize().x, _enemyImage->getFrameSize().y);
	_attackPrepareMotion_D_L->setPlayFrame(107, 102, false, false);
	_attackPrepareMotion_D_L->setFPS(1);
	//���ȷ� �Ʒ��� ���������غ� �ִϸ��̼�

	//���ȷ� ���� �������� �ִϸ��̼�
	_meleeAttackMotion_U_R = new animation;
	_meleeAttackMotion_U_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_U_R->setPlayFrame(0, 3, false, false);
	_meleeAttackMotion_U_R->setFPS(1);

	_meleeAttackMotion_U_L = new animation;
	_meleeAttackMotion_U_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_U_L->setPlayFrame(21, 18, false, false);
	_meleeAttackMotion_U_L->setFPS(1);
	//���ȷ� ���� �������� �ִϸ��̼�

	//���ȷ� �������� �ִϸ��̼�
	_meleeAttackMotion_R = new animation;
	_meleeAttackMotion_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_R->setPlayFrame(6, 9, false, false);
	_meleeAttackMotion_R->setFPS(1);

	_meleeAttackMotion_L = new animation;
	_meleeAttackMotion_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_L->setPlayFrame(27, 24, false, false);
	_meleeAttackMotion_L->setFPS(1);
	//���ȷ� �������� �ִϸ��̼�

	//���ȷ� �Ʒ��� �������� �ִϸ��̼�
	_meleeAttackMotion_D_R = new animation;
	_meleeAttackMotion_D_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_D_R->setPlayFrame(12, 15, false, false);
	_meleeAttackMotion_D_R->setFPS(1);

	_meleeAttackMotion_D_L = new animation;
	_meleeAttackMotion_D_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_meleeAttackMotion_D_L->setPlayFrame(33, 30, false, false);
	//���ȷ� �Ʒ��� �������� �ִϸ��̼�

	//���ȷ� ���� �������� �ִϸ��̼�
	_attackMotion_U_R = new animation;
	_attackMotion_U_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_U_R->setPlayFrame(36, 41, false, true);
	_attackMotion_U_R->setFPS(1);

	_attackMotion_U_L = new animation;
	_attackMotion_U_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_U_L->setPlayFrame(54, 59, false, true);
	_attackMotion_U_L->setFPS(1);
	//���ȷ� ���� �������� �ִϸ��̼�

	//���ȷ� �������� �ִϸ��̼�
	_attackMotion_R = new animation;
	_attackMotion_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_R->setPlayFrame(42, 47, false, true);
	_attackMotion_R->setFPS(1);

	_attackMotion_L = new animation;
	_attackMotion_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_L->setPlayFrame(65, 60, false, true);
	_attackMotion_L->setFPS(1);
	//���ȷ� �������� �ִϸ��̼�

	//���ȷ� �Ʒ��� �������� �ִϸ��̼�
	_attackMotion_D_R = new animation;
	_attackMotion_D_R->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_D_R->setPlayFrame(48, 53, false, true);
	_attackMotion_D_R->setFPS(1);

	_attackMotion_D_L = new animation;
	_attackMotion_D_L->init(_attackImage->getWidth(), _attackImage->getHeight(), _attackImage->getFrameSize().x, _attackImage->getFrameSize().y);
	_attackMotion_D_L->setPlayFrame(71, 66, false, true);
	_attackMotion_D_L->setFPS(1);
	//���ȷ� �Ʒ��� �������� �ִϸ��̼�

	//���ȷ� ���� ��Ʈ �ִϸ��̼�
	_hitMotion_U_R = new animation;
	_hitMotion_U_R->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_U_R->setPlayFrame(0, 3, false, false);
	_hitMotion_U_R->setFPS(1);

	_hitMotion_U_L = new animation;
	_hitMotion_U_L->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_U_L->setPlayFrame(15, 12, false, false);
	_hitMotion_U_L->setFPS(1);
	//���ȷ� ���� ��Ʈ �ִϸ��̼�

	//���ȷ� ��Ʈ �ִϸ��̼�
	_hitMotion_R = new animation;
	_hitMotion_R->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_R->setPlayFrame(5, 8, false, false);
	_hitMotion_R->setFPS(1);

	_hitMotion_L = new animation;
	_hitMotion_L->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_L->setPlayFrame(19, 16, false, false);
	_hitMotion_L->setFPS(1);
	//���ȷ� ��Ʈ �ִϸ��̼�

	//���ȷ� �Ʒ��� ��Ʈ �ִϸ��̼�
	_hitMotion_D_R = new animation;
	_hitMotion_D_R->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_D_R->setPlayFrame(8, 11, false, false);
	_hitMotion_D_R->setFPS(1);

	_hitMotion_D_L = new animation;
	_hitMotion_D_L->init(_hitImage->getWidth(), _hitImage->getHeight(), _hitImage->getFrameSize().x, _hitImage->getFrameSize().y);
	_hitMotion_D_L->setPlayFrame(23, 20, false, false);
	_hitMotion_D_L->setFPS(1);
	//���ȷ� �Ʒ��� ��Ʈ �ִϸ��̼�

	_rc.update(_position, Vector2(70, 70), pivot::CENTER);

	_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
	_enemyMotion = _idleMotion_D_R;

	_tile.update(Vector2(0, 0), Vector2(48, 48), pivot::LEFTTOP);

	_nowOrder = 1;

	return S_OK;
}

void buffalo::release()
{
}

void buffalo::update()
{
	tileGet();//���ȷ� Ÿ�� ���� ������Ʈ
	move();//���ȷ� ����
	animationControl();//����� �𷺼� ���°��� ���� �ִϸ��̼� ����
	//animationAngleControl();//���ȷ��� �������� ���� �ִϸ��̼� ����
	_enemyMotion->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);//���ȷ� �ִϸ��̼� ������Ʈ
	angry();//���ȷ��� ü���� �������ϰ� �Ǹ� �ɷ�ġ ���(���ǵ�, ���ݼӵ�, ���ݷ�)
}

void buffalo::render()
{
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_attackRC));//���ȷ� ���ݷ�Ʈ
	animationDraw();
	D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_rc));//���ȷ� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_t[i]->getRect()));
	}
	for (int i = 0; i < _move.size(); i++)
	{
		D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_move[i]->getRect()));
	}
}

void buffalo::move()
{
	_playerX = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().x;
	_playerY = OBJECTMANAGER->findObject(objectType::PLAYER, "player")->getPosition().y;

	_distance = getDistance(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);
	_angle = getAngle(_rc.getCenter().x, _rc.getCenter().y, _playerX, _playerY);

	if (_maxHP > _currentHP)//���ݹ޾�����
	{
		_idleMove = false;

		if (_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
		{
			if (!_distanceChange)
			{
				if (_move.size() != NULL)
				{
					d = getDistance(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);
					an = getAngle(_position.x, _position.y, _move[_move.size() - 1]->getRect().getCenter().x,
						_move[_move.size() - 1]->getRect().getCenter().y);

					_position.x += cosf(an) * _speed;
					_position.y += -sinf(an) * _speed;

					if (d < 5)
					{
						deleteMove();
					}

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
			else if (_distanceChange && _distance > 100)//�Ÿ��� 350���� ������ 100���� �ָ�
			{
				_attackDelay++;
				if (_attackDelay >= _maxAttackDelay && !_isAttack)
				{
					_angleSave = _angle;
					_playerSaveX = _playerX;
					_playerSaveY = _playerY;

					if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//����
					{
						_enemyDirection = ENEMY_LEFT_ATTACK_PREPARE;
					}

					if (_angleSave * (180 / PI) >= 90 && _angleSave * (180 / PI) <= 135)//������
					{
						_enemyDirection = ENEMY_UP_LEFT_ATTACK_PREPARE;
					}

					if (_angleSave * (180 / PI) >= 45 && _angleSave * (180 / PI) <= 90)//��������
					{
						_enemyDirection = ENEMY_UP_RIGHT_ATTACK_PREPARE;
					}

					if ((_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45) || (_angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360))//������
					{
						_enemyDirection = ENEMY_RIGHT_ATTACK_PREPARE;
					}

					if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//�Ʒ�������
					{
						_enemyDirection = ENEMY_DOWN_RIGHT_ATTACK_PREPARE;
					}

					if (_angleSave * (180 / PI) >= 225 && _angleSave * (180 / PI) <= 270)//�Ʒ�����
					{
						_enemyDirection = ENEMY_DOWN_LEFT_ATTACK_PREPARE;
					}
				}
			}

			if (_isAttack)//���ʹ� ���ݽ���
			{
				if (tileMove())//��ֹ��� �ε����� �ƴ϶��
				{
					_position.x += cosf(_angleSave) * _attackSpeed;
					_position.y += -sinf(_angleSave) * _attackSpeed;
				}
				else//��ֹ��� �ε�������
				{
					_position.x += cosf(_angleSave + PI) * _attackSpeed;
					_position.y += -sinf(_angleSave + PI) * _attackSpeed;
					//_count++;
					//if (_count % 5 == 0)
					//{
						if (_enemyDirection == ENEMY_UP_LEFT_ATTACK)
						{
							_enemyDirection = ENEMY_UP_LEFT_HIT;
						}
						if (_enemyDirection == ENEMY_UP_RIGHT_ATTACK)
						{
							_enemyDirection = ENEMY_UP_RIGHT_HIT;
						}
						if (_enemyDirection == ENEMY_LEFT_ATTACK)
						{
							_enemyDirection = ENEMY_LEFT_HIT;
						}
						if (_enemyDirection == ENEMY_RIGHT_ATTACK)
						{
							_enemyDirection = ENEMY_RIGHT_HIT;
						}
						if (_enemyDirection == ENEMY_DOWN_LEFT_ATTACK)
						{
							_enemyDirection = ENEMY_DOWN_LEFT_HIT;
						}
						if (_enemyDirection == ENEMY_DOWN_RIGHT_ATTACK)
						{
							_enemyDirection = ENEMY_DOWN_RIGHT_HIT;
						}

						_isAttack = false;
					//	_count = 0;
					//}
				}
				_attackRC.update(Vector2(0, 0), Vector2(100, 100), pivot::CENTER);
			}

			if (_distance <= 100)//�Ÿ��� 100���� ������
			{
				_count++;
				if (_count % 5 == 0)
				{
					if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//����
					{
						_enemyDirection = ENEMY_LEFT_MELEE_ATTACK;
					}

					if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//������
					{
						_enemyDirection = ENEMY_UP_LEFT_MELEE_ATTACK;
					}

					if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//��������
					{
						_enemyDirection = ENEMY_UP_RIGHT_MELEE_ATTACK;
					}

					if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45) || (_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360))//������
					{
						_enemyDirection = ENEMY_RIGHT_MELEE_ATTACK;
					}

					if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//�Ʒ�������
					{
						_enemyDirection = ENEMY_DOWN_RIGHT_MELEE_ATTACK;
					}

					if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//�Ʒ�����
					{
						_enemyDirection = ENEMY_DOWN_LEFT_MELEE_ATTACK;
					}
					_count = 0;
				}
			}
		}

		if (_distance > 350)//�÷��̾�� ���ʹ��� �Ÿ��� 350���� ũ��
		{
			_distanceChange = false;
		}
		else
		{
			_distanceChange = true;
		}

		if (!_isAttack)//���ȷ��� ���ݻ��°��� �޽���
		{
			_attackRC.update(Vector2(0, 0), Vector2(0, 0), pivot::CENTER);
		}

		if (!tileMove())
		{
			_position.x += cosf(_angle) * _speed;
			_position.y += -sinf(_angle) * _speed;

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
	else//���ݹ��� �ʾ�����
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

	_rc.set(_position, pivot::CENTER);//���ȷ� ��Ʈ ��ġ ������Ʈ
	_attackRC.set(_position, pivot::CENTER);//���ȷ� ���ݷ�Ʈ ��ġ ������Ʈ
}

void buffalo::animationAngleControl()
{
	if (_maxHP > _currentHP)//���ݹ޾�����
	{
		if (_enemyDirection != ENEMY_UP_LEFT_HIT &&
			_enemyDirection != ENEMY_UP_RIGHT_HIT &&
			_enemyDirection != ENEMY_LEFT_HIT &&
			_enemyDirection != ENEMY_RIGHT_HIT &&
			_enemyDirection != ENEMY_DOWN_LEFT_HIT &&
			_enemyDirection != ENEMY_DOWN_RIGHT_HIT)
		{
			if (!_distanceChange)
			{
				if (_move.size() != NULL)
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
			else if (_distanceChange && _distance > 100)//�Ÿ��� 350���� ������ 100���� �ָ�
			{
				if (_attackDelay >= _maxAttackDelay && !_isAttack)
				{
					if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//����
					{
						_enemyDirection = ENEMY_LEFT_ATTACK_PREPARE;
					}

					if (_angleSave * (180 / PI) >= 90 && _angleSave * (180 / PI) <= 135)//������
					{
						_enemyDirection = ENEMY_UP_LEFT_ATTACK_PREPARE;
					}

					if (_angleSave * (180 / PI) >= 45 && _angleSave * (180 / PI) <= 90)//��������
					{
						_enemyDirection = ENEMY_UP_RIGHT_ATTACK_PREPARE;
					}

					if ((_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45) || (_angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360))//������
					{
						_enemyDirection = ENEMY_RIGHT_ATTACK_PREPARE;
					}

					if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//�Ʒ�������
					{
						_enemyDirection = ENEMY_DOWN_RIGHT_ATTACK_PREPARE;
					}

					if (_angleSave * (180 / PI) >= 225 && _angleSave * (180 / PI) <= 270)//�Ʒ�����
					{
						_enemyDirection = ENEMY_DOWN_LEFT_ATTACK_PREPARE;
					}
				}
			}

			if (_isAttack)//���ʹ� ���ݽ���
			{
				if (!tileMove())//��ֹ��� �ε�������
				{
					if (_count % 5 == 0)
					{
						if (_enemyDirection == ENEMY_UP_LEFT_ATTACK)
						{
							_enemyDirection = ENEMY_UP_LEFT_HIT;
						}
						if (_enemyDirection == ENEMY_UP_RIGHT_ATTACK)
						{
							_enemyDirection = ENEMY_UP_RIGHT_HIT;
						}
						if (_enemyDirection == ENEMY_LEFT_ATTACK)
						{
							_enemyDirection = ENEMY_LEFT_HIT;
						}
						if (_enemyDirection == ENEMY_RIGHT_ATTACK)
						{
							_enemyDirection = ENEMY_RIGHT_HIT;
						}
						if (_enemyDirection == ENEMY_DOWN_LEFT_ATTACK)
						{
							_enemyDirection = ENEMY_DOWN_LEFT_HIT;
						}
						if (_enemyDirection == ENEMY_DOWN_RIGHT_ATTACK)
						{
							_enemyDirection = ENEMY_DOWN_RIGHT_HIT;
						}
					}
				}
			}

			if (_distance <= 100)//�Ÿ��� 100���� ������
			{
				if (_count % 5 == 0)
				{
					if (_angle * (180 / PI) >= 135 && _angle * (180 / PI) <= 225)//����
					{
						_enemyDirection = ENEMY_LEFT_MELEE_ATTACK;
					}

					if (_angle * (180 / PI) >= 90 && _angle * (180 / PI) <= 135)//������
					{
						_enemyDirection = ENEMY_UP_LEFT_MELEE_ATTACK;
					}

					if (_angle * (180 / PI) >= 45 && _angle * (180 / PI) <= 90)//��������
					{
						_enemyDirection = ENEMY_UP_RIGHT_MELEE_ATTACK;
					}

					if ((_angle * (180 / PI) >= 0 && _angle * (180 / PI) <= 45) || (_angle * (180 / PI) >= 315 && _angle * (180 / PI) <= 360))//������
					{
						_enemyDirection = ENEMY_RIGHT_MELEE_ATTACK;
					}

					if (_angle * (180 / PI) >= 270 && _angle * (180 / PI) <= 315)//�Ʒ�������
					{
						_enemyDirection = ENEMY_DOWN_RIGHT_MELEE_ATTACK;
					}

					if (_angle * (180 / PI) >= 225 && _angle * (180 / PI) <= 270)//�Ʒ�����
					{
						_enemyDirection = ENEMY_DOWN_LEFT_MELEE_ATTACK;
					}
				}
			}
		}
	}
	else//���ݹ��� �ʾ�����
	{
		if (_distanceSave > 10 && tileMove())
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
}

void buffalo::animationDraw()
{
	switch (_enemyDirection)
	{
	case ENEMY_LEFT_IDLE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_RIGHT_IDLE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_LEFT_IDLE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_RIGHT_IDLE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_LEFT_IDLE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_RIGHT_IDLE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_LEFT_MOVE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_RIGHT_MOVE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_LEFT_MOVE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_RIGHT_MOVE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_LEFT_HIT:
		_hitImage->setSize(Vector2(_hitImage->getFrameSize()) * CAMERA->getZoomAmount());
		_hitImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_RIGHT_HIT:
		_hitImage->setSize(Vector2(_hitImage->getFrameSize()) * CAMERA->getZoomAmount());
		_hitImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_LEFT_HIT:
		_hitImage->setSize(Vector2(_hitImage->getFrameSize()) * CAMERA->getZoomAmount());
		_hitImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_RIGHT_HIT:
		_hitImage->setSize(Vector2(_hitImage->getFrameSize()) * CAMERA->getZoomAmount());
		_hitImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_LEFT_HIT:
		_hitImage->setSize(Vector2(_hitImage->getFrameSize()) * CAMERA->getZoomAmount());
		_hitImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_RIGHT_HIT:
		_hitImage->setSize(Vector2(_hitImage->getFrameSize()) * CAMERA->getZoomAmount());
		_hitImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_LEFT_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_RIGHT_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_LEFT_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_RIGHT_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_LEFT_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_RIGHT_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_LEFT_ATTACK_PREPARE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_RIGHT_ATTACK_PREPARE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_LEFT_ATTACK_PREPARE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_RIGHT_ATTACK_PREPARE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_LEFT_ATTACK_PREPARE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_RIGHT_ATTACK_PREPARE:
		_enemyImage->setSize(Vector2(_enemyImage->getFrameSize()) * CAMERA->getZoomAmount());
		_enemyImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_LEFT_MELEE_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_UP_RIGHT_MELEE_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_LEFT_MELEE_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_RIGHT_MELEE_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_LEFT_MELEE_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	case ENEMY_DOWN_RIGHT_MELEE_ATTACK:
		_attackImage->setSize(Vector2(_attackImage->getFrameSize()) * CAMERA->getZoomAmount());
		_attackImage->aniRender(CAMERA->getRelativeVector2(_rc.getCenter().x, _rc.getCenter().y), _enemyMotion, 1.0f);//���ȷ� �ִϸ��̼� ���
		break;
	}
}

void buffalo::animationControl()
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
		_enemyMotion = _moveMotion_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_RIGHT_MOVE:
		_enemyMotion = _moveMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_LEFT_MOVE:
		_enemyMotion = _moveMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_UP_RIGHT_MOVE:
		_enemyMotion = _moveMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_LEFT_MOVE:
		_enemyMotion = _moveMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_DOWN_RIGHT_MOVE:
		_enemyMotion = _moveMotion_D_R;

		if (!_enemyMotion->isPlay())
		{
			_enemyMotion->start();
		}
		break;
	case ENEMY_LEFT_HIT:
		_enemyMotion = _hitMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_LEFT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_RIGHT_HIT:
		_enemyMotion = _hitMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_RIGHT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_UP_LEFT_HIT:
		_enemyMotion = _hitMotion_U_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_UP_LEFT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_UP_RIGHT_HIT:
		_enemyMotion = _hitMotion_U_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_UP_RIGHT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_DOWN_LEFT_HIT:
		_enemyMotion = _hitMotion_D_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
		}
		break;
	case ENEMY_DOWN_RIGHT_HIT:
		_enemyMotion = _hitMotion_D_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_hitCount++;
			if (_hitCount >= 50)
			{
				_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
				_oneAnimation = false;
				_hitCount = 0;
			}
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
	case ENEMY_UP_LEFT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_U_L;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}

		if (_attackCount >= 3)
		{
			_isAttack = true;
			_enemyDirection = ENEMY_UP_LEFT_ATTACK;
			_attackCount = 0;
		}
		break;
	case ENEMY_UP_RIGHT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_U_R;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}

		if (_attackCount >= 3)
		{
			_isAttack = true;
			_enemyDirection = ENEMY_UP_RIGHT_ATTACK;
			_attackCount = 0;
		}
		break;
	case ENEMY_LEFT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_L;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}

		if (_attackCount >= 3)
		{
			_isAttack = true;
			_enemyDirection = ENEMY_LEFT_ATTACK;
			_attackCount = 0;
		}
		break;
	case ENEMY_RIGHT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_R;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}

		if (_attackCount >= 3)
		{
			_isAttack = true;
			_enemyDirection = ENEMY_RIGHT_ATTACK;
			_attackCount = 0;
		}
		break;
	case ENEMY_DOWN_LEFT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_D_L;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}

		if (_attackCount >= 3)
		{
			_isAttack = true;
			_enemyDirection = ENEMY_DOWN_LEFT_ATTACK;
			_attackCount = 0;
		}
		break;
	case ENEMY_DOWN_RIGHT_ATTACK_PREPARE:
		_enemyMotion = _attackPrepareMotion_D_R;

		if (!_enemyMotion->isPlay())
		{
			_attackCount++;
			_enemyMotion->start();
		}

		if (_attackCount >= 3)
		{
			_isAttack = true;
			_enemyDirection = ENEMY_DOWN_RIGHT_ATTACK;
		}
		break;
	case ENEMY_UP_LEFT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_U_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_UP_LEFT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}
		break;
	case ENEMY_UP_RIGHT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_U_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_UP_RIGHT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}
		break;
	case ENEMY_LEFT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_LEFT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}
		break;
	case ENEMY_RIGHT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_RIGHT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}
		break;
	case ENEMY_DOWN_LEFT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_D_L;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_DOWN_LEFT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}
		break;
	case ENEMY_DOWN_RIGHT_MELEE_ATTACK:
		_enemyMotion = _meleeAttackMotion_D_R;

		if (!_enemyMotion->isPlay() && !_oneAnimation)
		{
			_enemyMotion->start();
			_oneAnimation = true;
			_isAttack = true;
		}

		if (!_enemyMotion->isPlay() && _oneAnimation)
		{
			_enemyDirection = ENEMY_DOWN_RIGHT_IDLE;
			_oneAnimation = false;
			_isAttack = false;
		}
		break;
	}
}

void buffalo::tileGet()
{
	_tile.set(Vector2(((int)_position.x / SIZE) * SIZE, ((int)(_rc.bottom + 10 - SIZE * 0.5f) / SIZE) * SIZE), pivot::LEFTTOP);

	int k = 1;
	currentTileIndex = Vector2(_tile.left / SIZE, _tile.top / SIZE);//���� ���ȷ� ��ġ�� Ÿ��

	if (_angleSave * (180 / PI) >= 135 && _angleSave * (180 / PI) <= 225)//�ަU
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
		nextTileIndex[2] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);
	}

	if (_angleSave * (180 / PI) >= 0 && _angleSave * (180 / PI) <= 45 || _angleSave * (180 / PI) >= 315 && _angleSave * (180 / PI) <= 360)//������
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x + k, currentTileIndex.y);
		nextTileIndex[1] = Vector2(currentTileIndex.x + k, currentTileIndex.y - k);
		nextTileIndex[2] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);
	}

	if (_angleSave * (180 / PI) >= 270 && _angleSave * (180 / PI) <= 315)//�Ʒ�������
	{
		nextTileIndex[0] = Vector2(currentTileIndex.x + k, currentTileIndex.y + k);
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

bool buffalo::tileMove()
{
	if (_t[0]->getOrderIndex() == _nowOrder && _t[1]->getOrderIndex() == _nowOrder && _t[2]->getOrderIndex() == _nowOrder)
	{
		return true;
	}
	else
	{
		return false;
	}
}