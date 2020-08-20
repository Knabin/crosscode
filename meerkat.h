#pragma once
#include "enemy.h"

class meerkat : public enemy
{
private:
	class bullets* _bullet;

	image* _meerkatMoveImage;//미어캣 무브 이미지

	animation* _meerkatMoveMotion;//미어캣이 땅속으로 들어간 상태에서 무브하는 애니메이션
	animation* _meerkatTunnelDownMotion_L;//미어캣이 땅속으로 들어가는 애니메이션
	animation* _meerkatTunnelDownMotion_R;
	animation* _meerkatTunnelUpMotion_L;//미어캣이 땅위로 올라가는 애니메이션
	animation* _meerkatTunnelUpMotion_R;

	int _smallDistance;//짧은 거리값 기준
	int _bigDistance;//먼거리값 기준
	int _reflectCount;//벽에 부딪힌 횟수
	int _meerkatSpeed;

	int _meerkatBallFrameX;
	int _meerkatBallFrameY;

	bool _isMove;//플레이어와 거리가 가까울때 반대방향으로 이동시키기 위해 필요한 변수
	bool _isBigMove;//플레이어와 미어캣의 거리가 너무 멀경우 미어캣을 플레이어 근처로 쫓아오게 하기 위한 변수
	bool _reflect;//미어캣이 벽에 부딪히면 벽의 반대쪽으로 이동시키기 위해 필요한 변수
	bool _oneAnimation;//애니메이션을 한번만 실행시키기 위한 변수

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void animationControl();
	void tileGet();//타일위치 가져오기
	void ballTileGet();//미어캣의 볼타일위치 가져오기
	void mapOutCollision();//에너미들이 맵밖으로 나가지 못하게 하기위한 함수
	bool ballTileMove();//볼타일 무브
	bool tileMove();//에너미의 타일무브

	bullets* getBullets() { return _bullet; }
};

