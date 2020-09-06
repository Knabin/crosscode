#pragma once

enum class CAMERASTATE : int
{
	NONE,		// 고정된 카메라
	TARGET,		// 타겟팅 카메라, 부드럽게 움직임
	END,
};

class camera
{
public:
	static camera* getInstance()
	{
		static camera instance;
		return &instance;
	}
private:
	camera();
	~camera();

private:
	CAMERASTATE _state;		// 현재 카메라의 상태
	RECT _rc;				// 현재 카메라의 RECT
	Vector2 _position;		// 카메라의 중점
	float _width;			// 카메라의 가로 길이
	float _height;			// 카메라의 세로 길이
	Vector2 _mapSize;		// 맵의 크기
	float _speed;			// 카메라 이동 속도

	// 이벤트용 변수
	float _moveTime;
	float _stopTime;
	float _worldTime;

	// 카메라 셰이크용 변수
	bool _isShake;
	float _shakeAmount;
	float _shakeTime;
	float _shakeNowTime;
	float _shakeDirectionChangeTime;
	float _shakeFlag;

	// 카메라 줌용 변수
	bool _isZoom;
	bool _isZoomOutSmooth;
	float _nowZoomAmount;
	float _zoomAmount;
	float _zoomTime;

	// 페이드인/페이드아웃용 변수
	bool _isFade;
	float _fadeAmount;
	float _nowFadeAmount;
	float _fadeTime;
	float _fadeNowTime;
	float _fadeInOutChangeTime;

	class gameObject* _target;	// 타겟팅될 게임 오브젝트

public:
	void update();
	void release();

	void moveToTarget();
	void moveToTargetSmooth();
	void updateShake();
	void updateZoom();
	void checkRect();
	void updateRect();
	void updateFade();

	void setCameraMode(CAMERASTATE state) { _state = state; }

	void changePosition(Vector2 vector) { _position = vector; }
	// 타겟팅될 게임 오브젝트 변경
	void changeTarget(class gameObject* gameObject);

	Vector2 getMapSize() { return _mapSize; }
	void setMapSize(Vector2 vector) { _mapSize = vector; }

	void shakeStart(float amount, float time);
	void zoomStart(float amount, float time, bool isZoomOutSmooth = FALSE);
	void fadeStart(float amount, float time);

	RECT getRelativeRect(RECT rc);
	floatRect getRelativeRect(floatRect rc);
	Vector2 getRelativeVector2(Vector2 vector);
	Vector2 getRelativeVector2(float x, float y);

	Vector2 getPosition() { return _position; }
	RECT& getRect() { return _rc; }
	bool getIsZoom() { return _isZoom; }
	float getZoomAmount() { return _nowZoomAmount; }

	bool getIsFade() { return _isFade; }
	bool getIsShake() { return _isShake; }

	float getFadeAmount() { return _nowFadeAmount; }
	bool getIsFadeOut() { return _fadeTime <= 0.0f; }

};

