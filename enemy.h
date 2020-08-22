#pragma once
#include "gameObject.h"
#include "tile.h"

enum ENEMYDIRECTION
{
	ENEMY_LEFT_IDLE,
	ENEMY_RIGHT_IDLE,

	ENEMY_UP_LEFT_IDLE,
	ENEMY_UP_RIGHT_IDLE,

	ENEMY_DOWN_LEFT_IDLE,
	ENEMY_DOWN_RIGHT_IDLE,

	ENEMY_LEFT_MOVE,
	ENEMY_RIGHT_MOVE,

	ENEMY_UP_LEFT_MOVE,
	ENEMY_UP_RIGHT_MOVE,

	ENEMY_DOWN_LEFT_MOVE,
	ENEMY_DOWN_RIGHT_MOVE,

	ENEMY_LEFT_HIT,
	ENEMY_RIGHT_HIT,

	ENEMY_UP_LEFT_HIT,
	ENEMY_UP_RIGHT_HIT,

	ENEMY_DOWN_LEFT_HIT,
	ENEMY_DOWN_RIGHT_HIT,

	ENEMY_LEFT_ATTACK,
	ENEMY_RIGHT_ATTACK,

	ENEMY_UP_LEFT_ATTACK,
	ENEMY_UP_RIGHT_ATTACK,

	ENEMY_DOWN_LEFT_ATTACK,
	ENEMY_DOWN_RIGHT_ATTACK,

	ENEMY_UP_LEFT_ATTACK_PREPARE,
	ENEMY_UP_RIGHT_ATTACK_PREPARE,

	ENEMY_LEFT_ATTACK_PREPARE,
	ENEMY_RIGHT_ATTACK_PREPARE,

	ENEMY_DOWN_LEFT_ATTACK_PREPARE,
	ENEMY_DOWN_RIGHT_ATTACK_PREPARE,

	ENEMY_UP_LEFT_MELEE_ATTACK,
	ENEMY_UP_RIGHT_MELEE_ATTACK,

	ENEMY_LEFT_MELEE_ATTACK,
	ENEMY_RIGHT_MELEE_ATTACK,

	ENEMY_DOWN_LEFT_MELEE_ATTACK,
	ENEMY_DOWN_RIGHT_MELEE_ATTACK,

	ENEMY_TUNNEL_MOVE,//�̾�Ĺ �������� �� ���¿��� ����
	ENEMY_DOWN_LEFT_TUNNEL,//�̾�Ĺ�� �������� ���� ����
	ENEMY_DOWN_RIGHT_TUNNEL,
	ENEMY_UP_LEFT_TUNNEL,//�̾�Ĺ�� ���ӿ��� ������ ����
	ENEMY_UP_RIGHT_TUNNEL
};

class enemy : public gameObject
{
protected:
	ENEMYDIRECTION _enemyDirection;

	image* _enemyImage;//���ʹ� �̹���

	animation* _enemyMotion;//���ʹ� �ִϸ��̼�

	animation* _idleMotion_L;//���ʱ⺻ �ִϸ��̼�
	animation* _idleMotion_R;//�����ʱ⺻ �ִϸ��̼�
	animation* _idleMotion_U_L;
	animation* _idleMotion_U_R;
	animation* _idleMotion_D_L;
	animation* _idleMotion_D_R;

	animation* _moveMotion_L;//�������� �����̴� �ִϸ��̼�
	animation* _moveMotion_R;//���������� �����̴� �ִϸ��̼�
	animation* _moveMotion_U_L;
	animation* _moveMotion_U_R;
	animation* _moveMotion_D_L;
	animation* _moveMotion_D_R;

	animation* _attackMotion_L;//���ʰ��� �ִϸ��̼�
	animation* _attackMotion_R;//�����ʰ��� �ִϸ��̼�
	animation* _attackMotion_U_L;
	animation* _attackMotion_U_R;
	animation* _attackMotion_D_L;
	animation* _attackMotion_D_R;

	animation* _hitMotion_L;//���ʿ��� ���ݴ������� �ִϸ��̼�
	animation* _hitMotion_R;//�����ʿ��� ���ݴ������� �ִϸ��̼�
	animation* _hitMotion_U_L;//�����ʿ��� ���ݴ������� �ִϸ��̼�
	animation* _hitMotion_U_R;//�����ʿ��� ���ݴ������� �ִϸ��̼�
	animation* _hitMotion_D_L;//�����ʿ��� ���ݴ������� �ִϸ��̼�
	animation* _hitMotion_D_R;//�����ʿ��� ���ݴ������� �ִϸ��̼�

	vector<tile*> _move;

	Vector2 nextTileIndex[8];//���� ���ʹ� ��ġ���� ��ó�� ��ֹ� ��ġ�� �ľ��� Ÿ��
	Vector2 currentTileIndex;

	Vector2 ballNextTileIndex[8];//���� �̾�Ĺ ��ġ���� ��ó�� ��ֹ� ��ġ�� �ľ��� Ÿ��
	Vector2 ballCurrentTileIndex;

	floatRect _attackRC;//���ʹ� ���ݷ�Ʈ

	floatRect _tile;//���ʹ̰� Ÿ���� �����ϱ� ���� �ʿ��� ��Ʈ
	floatRect _ballTile;//�̾�Ĺ�� �� ��Ʈ�� Ÿ�ϰ˻�� ��Ʈ

	floatRect _currentHpBar;

	tile* _t[8];//������ Ÿ��
	tile* _ballT[8];//�̾�Ĺ�� ��Ÿ��

	float _speed;//���ʹ� ���ǵ�
	float _noHitSpeed;//�������� �ޱ����� ������ �̵��ӵ�
	float _angle;//���ʹ� �ޱ�

	float _playerX, _playerY;//�÷��̾� ��ǥ
	float _distance;//�÷��̾�� ���ʹ��� �Ÿ�

	float _angleSave, _distanceSave;//�÷��̾�� ���ʹ̰��� �Ÿ��� ������ ��õ��� �����س��� ����
	float _playerSaveX, _playerSaveY;//�Ͻ������� �÷��̾��� ��ǥ�� ������ ���� ����

	int _count;
	int _attackCount;//�����Ҷ� �÷��̾�� �޷��������� ������
	int _maxAttackDelay;//���ʹ� ���� �ִ� ������
	int _attackDelay;//���ʹ� ���� ������
	int _hitCount;//���ݴ��ϴ� �ִϸ��̼��� ������ �����Ű�� ���� ����

	int _attackPower;//���ʹ� ���ݷ�

	int _maxHP;//���ʹ��� �ִ� ü��
	int _currentHP;//���ʹ��� ���� ü��

	bool _isAttack;//���ʹ̰� ���ݻ������� Ȯ���ϱ� ���� ����
	bool _distanceChange;//�Ÿ��� ���� ����ó��
	bool _idleMove;//���ݴ��ϱ����� �����̴� �Ÿ�, �������� �ѹ��� ������ѳ��� ����ϱ� ���� ����
	bool _collision;//���ʹ̵��� ���ݴ��Ҷ� �ѹ��� ������ �°��ϱ� ���� ����

	int _nowOrder;//���� ���ʹ��� ���� �������� Ȯ���ϱ� ���� ����

	int _damaged;
	bool _dealing;
	int _dealingCount;

private:
	bool _oneAngry;//�ޱ׸� �Լ��� �ѹ��� ����ǰ� �ϱ� ���� ����

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void angry();//���ʹ��� ü���� ���� ���Ϸ� �������� �ɷ�ġ ���(���ݷ�, ���ǵ�, ���ݵ�����)

	//������
	ENEMYDIRECTION getEnemyDirection() { return _enemyDirection; }

	floatRect getEnemyAttackRect() { return _attackRC; }//���ʹ� ���ݷ�Ʈ

	float getEnemyAngle() { return _angle; }//���ʹ̿� �÷��̾�� ����
	float getEnemyAngleSave() { return _angleSave; }

	int getEnemyHP() { return _currentHP; }//���ʹ��� ���� ü�� ������
	int getEnemyAttackPower() { return _attackPower; }//���ʹ��� ���� ���ݷ� ������

	bool getEnemyIsAttack() { return _isAttack; }//���ʹ��� ���ݻ��°� ������
	bool getEnemyCollision() { return _collision; }
	//������

	//������
	void setEnemyHP(int currentHP) { _currentHP -= currentHP; }//���ʹ��� ���� ü�±��
	void setEnemyDirection(ENEMYDIRECTION enemyDirection) { _enemyDirection = enemyDirection; }//���ʹ��� ���°� ����
	void setEnemyX(float x) { _position.x = x; }//���ʹ��� x��ǥ ����
	void setEnemyY(float y) { _position.y = y; }//���ʹ��� y��ǥ ����
	void setEnemyAttackRect() { _attackRC.update(Vector2(0,0), Vector2(0,0), pivot::CENTER); }//���ʹ��� ���ݷ�Ʈ �����
	void setEnemyIsActive(bool isActive) { _isActive = isActive; }//���ʹ� ���
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	void setEnemyCollision(bool collision) { _collision = collision; }
	//������

	vector<tile*>& getMove() { return _move; }
	void setMove(vector<tile*> moveV) { _move = moveV; }
	void deleteMove() { _move.erase(_move.begin() + _move.size() - 1); }
	void clearMove() { _move.clear(); }

	int getDamaged() { return _damaged; }
	void setDamaged(int d) { _damaged = d; }

	bool getDealing() { return _dealing; }
	void setDealing(bool b) { _dealing = b; }

	int getCount() { return _dealingCount; }
	void setCount(int t) { _dealingCount = t;}
	void plusCount(int t) { _dealingCount += t; }
};

