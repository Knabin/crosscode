#pragma once
class camera
{
public:
	enum class CAMERASTATE : int
	{
		NONE,		// ���� ī�޶�
		TARGET,		// Ÿ���� ī�޶�
		END,
	};

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

	// ī�޶� �ܿ� ����(�̱���)
	bool _isZoom;
	float _zoomAmount;
	float _zoomTime;

	class gameObject* _target;	// Ÿ���õ� ���� ������Ʈ

public:
	void update();
	void release();

	void moveToTarget();

	// Ÿ���õ� ���� ������Ʈ ����
	void changeTarget(class gameObject* gameObject);

	float getMapWidth() { return _mapWidth; }
	float getMapHeight() { return _mapHeight; }
	void setMapSize(float mapWidth, float mapHeight) { _mapWidth = mapWidth; _mapHeight = mapHeight; }

	RECT& getRect() { return _rc; }
};

