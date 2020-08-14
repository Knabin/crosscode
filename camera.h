#pragma once

enum class CAMERASTATE : int
{
	NONE,		// ���� ī�޶�
	TARGET,		// Ÿ���� ī�޶�
	EVENT,		// �̺�Ʈ�� ī�޶�
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
	CAMERASTATE _state;		// ���� ī�޶��� ����
	RECT _rc;				// ���� ī�޶��� RECT
	floatPoint _position;	// ī�޶��� ����
	float _width;			// ī�޶��� ���� ����
	float _height;			// ī�޶��� ���� ����
	float _mapWidth;		// ������� ���� ����
	float _mapHeight;		// ������� ���� ����
	float _speed;			// ī�޶� �̵� �ӵ�

	// �̺�Ʈ�� ����(�̱���)
	float _moveTime;
	float _stopTime;
	float _worldTime;

	// ī�޶� ����ũ�� ����(�̱���)
	bool _isShake;
	float _shakeAmount;
	float _shakeTime;
	float _shakeNowTime;
	float _shakeDirectionChangeTime;
	float _shakeFlag;

	// ī�޶� �ܿ� ����(�̱���)
	bool _isZoom;
	bool _isZoomOutSmooth;
	float _nowZoomAmount;
	float _zoomAmount;
	float _zoomTime;

	class gameObject* _target;	// Ÿ���õ� ���� ������Ʈ

public:
	void update();
	void release();

	void moveToTarget();
	void moveToTargetSmooth();
	void updateShake();
	void updateZoom();
	void zoom(HDC hdc);

	void setCameraMode(CAMERASTATE state) { _state = state; }

	// Ÿ���õ� ���� ������Ʈ ����
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

