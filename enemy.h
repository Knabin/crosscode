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

	ENEMY_TUNNEL_MOVE,//미어캣 땅속으로 들어간 상태에서 무브
	ENEMY_DOWN_LEFT_TUNNEL,//미어캣이 땅속으로 들어가는 상태
	ENEMY_DOWN_RIGHT_TUNNEL,
	ENEMY_UP_LEFT_TUNNEL,//미어캣이 땅속에서 나오는 상태
	ENEMY_UP_RIGHT_TUNNEL
};

class enemy : public gameObject
{
protected:
	ENEMYDIRECTION _enemyDirection;

	image* _enemyImage;//에너미 이미지

	animation* _enemyMotion;//에너미 애니메이션

	animation* _idleMotion_L;//왼쪽기본 애니메이션
	animation* _idleMotion_R;//오른쪽기본 애니메이션
	animation* _idleMotion_U_L;
	animation* _idleMotion_U_R;
	animation* _idleMotion_D_L;
	animation* _idleMotion_D_R;

	animation* _moveMotion_L;//왼쪽으로 움직이는 애니메이션
	animation* _moveMotion_R;//오른쪽으로 움직이는 애니메이션
	animation* _moveMotion_U_L;
	animation* _moveMotion_U_R;
	animation* _moveMotion_D_L;
	animation* _moveMotion_D_R;

	animation* _attackMotion_L;//왼쪽공격 애니메이션
	animation* _attackMotion_R;//오른쪽공격 애니메이션
	animation* _attackMotion_U_L;
	animation* _attackMotion_U_R;
	animation* _attackMotion_D_L;
	animation* _attackMotion_D_R;

	animation* _hitMotion_L;//왼쪽에서 공격당했을때 애니메이션
	animation* _hitMotion_R;//오른쪽에서 공격당했을때 애니메이션
	animation* _hitMotion_U_L;//오른쪽에서 공격당했을때 애니메이션
	animation* _hitMotion_U_R;//오른쪽에서 공격당했을때 애니메이션
	animation* _hitMotion_D_L;//오른쪽에서 공격당했을때 애니메이션
	animation* _hitMotion_D_R;//오른쪽에서 공격당했을때 애니메이션

	vector<tile*> _move;

	Vector2 nextTileIndex[8];//현재 에너미 위치에서 근처에 장애물 위치를 파악할 타일
	Vector2 currentTileIndex;

	Vector2 ballNextTileIndex[8];//현재 미어캣 위치에서 근처에 장애물 위치를 파악할 타일
	Vector2 ballCurrentTileIndex;

	floatRect _attackRC;//에너미 공격렉트

	floatRect _tile;//에너미가 타일을 검출하기 위해 필요한 렉트
	floatRect _ballTile;//미어캣의 볼 렉트의 타일검사용 렉트

	floatRect _currentHpBar;

	tile* _t[8];//검출할 타일
	tile* _ballT[8];//미어캣의 볼타일

	float _speed;//에너미 스피드
	float _noHitSpeed;//데미지를 받기전의 움직일 이동속도
	float _angle;//에너미 앵글

	float _playerX, _playerY;//플레이어 좌표
	float _distance;//플레이어와 에너미의 거리

	float _angleSave, _distanceSave;//플레이어와 에너미간의 거리와 각도를 잠시동안 저장해놓을 변수
	float _playerSaveX, _playerSaveY;//일시적으로 플레이어의 좌표를 저장해 놓을 변수

	int _count;
	int _attackCount;//공격할때 플레이어에게 달려갈때까지 딜레이
	int _maxAttackDelay;//에너미 공격 최대 딜레이
	int _attackDelay;//에너미 공격 딜레이
	int _hitCount;//공격당하는 애니메이션을 여러번 실행시키기 위한 변수

	int _attackPower;//에너미 공격력

	int _maxHP;//에너미의 최대 체력
	int _currentHP;//에너미의 현재 체력

	bool _isAttack;//에너미가 공격상태인지 확인하기 위한 변수
	bool _distanceChange;//거리에 따른 상태처리
	bool _idleMove;//공격당하기전에 움직이는 거리, 각도값을 한번만 저장시켜놓고 사용하기 위한 변수
	bool _collision;//에너미들이 공격당할때 한번만 공격을 맞게하기 위한 변수

	int _nowOrder;//현재 에너미의 층이 몇층인지 확인하기 위한 변수

	int _damaged;
	bool _dealing;
	int _dealingCount;

private:
	bool _oneAngry;//앵그리 함수를 한번만 실행되게 하기 위한 변수

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void angry();//에너미의 체력이 절반 이하로 떨어지면 능력치 향상(공격력, 스피드, 공격딜레이)

	//접근자
	ENEMYDIRECTION getEnemyDirection() { return _enemyDirection; }

	floatRect getEnemyAttackRect() { return _attackRC; }//에너미 공격렉트

	float getEnemyAngle() { return _angle; }//에너미와 플레이어간의 각도
	float getEnemyAngleSave() { return _angleSave; }

	int getEnemyHP() { return _currentHP; }//에너미의 현재 체력 얻어오기
	int getEnemyAttackPower() { return _attackPower; }//에너미의 현재 공격력 얻어오기

	bool getEnemyIsAttack() { return _isAttack; }//에너미의 공격상태값 얻어오기
	bool getEnemyCollision() { return _collision; }
	//접근자

	//설정자
	void setEnemyHP(int currentHP) { _currentHP -= currentHP; }//에너미의 현재 체력깍기
	void setEnemyDirection(ENEMYDIRECTION enemyDirection) { _enemyDirection = enemyDirection; }//에너미의 상태값 변경
	void setEnemyX(float x) { _position.x = x; }//에너미의 x좌표 변경
	void setEnemyY(float y) { _position.y = y; }//에너미의 y좌표 변경
	void setEnemyAttackRect() { _attackRC.update(Vector2(0,0), Vector2(0,0), pivot::CENTER); }//에너미의 공격렉트 지우기
	void setEnemyIsActive(bool isActive) { _isActive = isActive; }//에너미 사망
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	void setEnemyCollision(bool collision) { _collision = collision; }
	//설정자

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

