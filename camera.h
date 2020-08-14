#pragma once

enum class CAMERASTATE : int
{
	NONE,		// 고정 카메라
	TARGET,		// 타겟팅 카메라
	EVENT,		// 이벤트용 카메라
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
	floatPoint _position;	// 카메라의 중점
	float _width;			// 카메라의 가로 길이
	float _height;			// 카메라의 세로 길이
	float _mapWidth;		// 백버퍼의 가로 길이
	float _mapHeight;		// 백버퍼의 세로 길이
	float _speed;			// 카메라 이동 속도

	// 이벤트용 변수(미구현)
	float _moveTime;
	float _stopTime;
	float _worldTime;

	// 카메라 셰이크용 변수(미구현)
	bool _isShake;
	float _shakeAmount;
	float _shakeTime;
	float _shakeNowTime;
	float _shakeDirectionChangeTime;
	float _shakeFlag;

	// 카메라 줌용 변수(미구현)
	bool _isZoom;
	bool _isZoomOutSmooth;
	float _nowZoomAmount;
	float _zoomAmount;
	float _zoomTime;

	class gameObject* _target;	// 타겟팅될 게임 오브젝트

public:
	void update();
	void release();

	void moveToTarget();
	void moveToTargetSmooth();
	void updateShake();
	void updateZoom();
	void zoom(HDC hdc);

	void setCameraMode(CAMERASTATE state) { _state = state; }

	// 타겟팅될 게임 오브젝트 변경
	void changeTarget(class gameObject* gameObject);

	float getMapWidth() { return _mapWidth; }
	float getMapHeight() { return _mapHeight; }
	void setMapSize(float mapWidth, float mapHeight) { _mapWidth = mapWidth; _mapHeight = mapHeight; }

	void shakeStart(float amount, float time);
	void zoomStart(float amount, float time, bool isZoomOutSmooth = FALSE);

	RECT& getRect() { return _rc; }
	bool getIsZoom() { return _isZoom; }
	int getZoomAmount() { return _zoomAmount; }
};

