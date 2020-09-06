#pragma once

enum class CAMERASTATE : int
{
	NONE,		// ������ ī�޶�
	TARGET,		// Ÿ���� ī�޶�, �ε巴�� ������
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
	Vector2 _position;		// ī�޶��� ����
	float _width;			// ī�޶��� ���� ����
	float _height;			// ī�޶��� ���� ����
	Vector2 _mapSize;		// ���� ũ��
	float _speed;			// ī�޶� �̵� �ӵ�

	// �̺�Ʈ�� ����
	float _moveTime;
	float _stopTime;
	float _worldTime;

	// ī�޶� ����ũ�� ����
	bool _isShake;
	float _shakeAmount;
	float _shakeTime;
	float _shakeNowTime;
	float _shakeDirectionChangeTime;
	float _shakeFlag;

	// ī�޶� �ܿ� ����
	bool _isZoom;
	bool _isZoomOutSmooth;
	float _nowZoomAmount;
	float _zoomAmount;
	float _zoomTime;

	// ���̵���/���̵�ƿ��� ����
	bool _isFade;
	float _fadeAmount;
	float _nowFadeAmount;
	float _fadeTime;
	float _fadeNowTime;
	float _fadeInOutChangeTime;

	class gameObject* _target;	// Ÿ���õ� ���� ������Ʈ

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
	// Ÿ���õ� ���� ������Ʈ ����
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

