#pragma once
#include "gameObject.h"
#include "playerStateController.h"

enum class PLAYERDIRECTION : int
{
	TOP,
	LEFT_TOP,
	LEFT,
	LEFT_BOTTOM,
	BOTTOM,
	RIGHT_BOTTOM,
	RIGHT,
	RIGHT_TOP,
};

enum PLAYERSTATE : int
{
	IDLE,
	MOVE,
	JUMP,
	GUARD,
	DODGE,
	LONGATTACK,
	LONGATTACKIDLE,
	LONGATTACKMOVE,
	MOVESTOP,
	LEFT_ATTACK,
	RIGHT_ATTACK,
	RIGHT_FINALATTACK,
	END,
};

class player : public gameObject
{
private:
	image* _image;
	animation* _ani;
	floatRect _tile;		// center x, bottom �������� ���� ��� �ִ� tile rect

	floatRect rc1[12];
	floatRect rc2[12];
	float de;

	playerStateController* _state;
	PLAYERDIRECTION _direction;


	vector<playerState*>	_vState;

	POINT tileIndex;
	RECT rcCollision;
	int _nowOrder;
	int _count;

	int _jumpCount;

	bool _iscombo;		//�ٰŸ� �޺� �������� üũ
	int _combocount;	//�ٰŸ� �޺���
	int _combo;			//�ٰŸ� �޺���

	int _fullCount;	//���Ÿ����� �����ð�

	int _dodgeCount;	//����Ƚ��
	int _dodgeCharge;	//����Ƚ�� ������

	int _pHp;		//�÷��̾� HP 
	int _pXp;		//�÷��̾� ����ġ ���� �׿�����
	int _pSp;		//�÷��̾� SP ���� �������� ���ߵ�

	float _jumpPower;
	float _gravity;
	bool _jumping;

	floatRect _tileRect;
	POINT next[6];

public:
	player();
	virtual ~player();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void playerMove();
	void playerDodge();
	void playerJumpMove();
	void playerLongAttackMove();
	void playermeleeattackMove();
	void playerfinalattackMove();
	void move(const float& x, const float& y);
	void moveAngle(const float& cangle, const float& speed);
	void playerFire();
	void playerMeleeattack();

	void setImage(image* image) { _image = image; }
	void setImage(string imageName) { _image = IMAGEMANAGER->findImage(imageName); }
	void setAnimation(animation* ani) { _ani = ani; }
	void setDirection(PLAYERDIRECTION direction) { _direction = direction; }

	animation* getAnimation() { return _ani; }

	PLAYERDIRECTION getDirection() { return _direction; }
};