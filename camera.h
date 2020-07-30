#pragma once
class camera
{
public:
	enum class CAMERASTATE : int
	{
		TARGET,
		MOUSE,		// ¸ÊÅø¿ë?
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
	CAMERASTATE _state;
	RECT _rc;
	floatPoint _position;
	float _width;
	float _height;
	float _mapWidth;
	float _mapHeight;
	float _speed;

	float _moveTime;
	float _stopTime;
	float _worldTime;
	float _worldTime2;

	bool _isShake;
	float _shakeAmount;
	float _shakeTime;
	float _shakeNowTime;

	bool _isZoom;
	float _zoomAmount;
	float _zoomTime;

	class gameObject* _target;

public:
	void update();
	void release();

	float lerpX(float deltaTime);
	float lerpY(float deltaTime);

	void changeTarget(class gameObject* gameObject);

	//bool checkCameraX();
	//bool checkCameraY();

	//void cameraShake();
	//void shakeStart();

	//void cameraFixed(float x, float y);
	//void FixedStart();

	//void changePosition(float x, float y);

	//inline float getShakeNumber() { return _shakeAmount * _flag; }

	//inline void setPosition(float x, float y) { _cameraInfo->x = x; _cameraInfo->y = y; }

	//inline void setX(int x) { _cameraInfo->x = x; }
	//inline float getX() { return _cameraInfo->x; }

	//inline void setY(int y) { _cameraInfo->y = y; }
	//inline float getY() { return _cameraInfo->y; }

	//inline void setBlackSize(int size) { _cameraInfo->blackSize = size; }
	//inline int getBlackSize() { return _cameraInfo->blackSize; }

	//inline void setWidth(int width) { _cameraInfo->width = width; }
	//inline int getWidth() { return _cameraInfo->width; }

	//inline void setHeight(int height) { _cameraInfo->height = height; }
	//inline int getHeight() { return _cameraInfo->height; }

	//inline void setBackWidth(int width) { _cameraInfo->backWidth = width; }
	//inline void setBackHeight(int height) { _cameraInfo->backHeight = height; }

	//inline int getLeft() {
	//	if (!checkCameraX()) return (_cameraInfo->x <= _cameraInfo->backWidth / 2) ? 0 : _cameraInfo->backWidth - _cameraInfo->width;
	//	return _cameraInfo->x - _cameraInfo->width / 2;
	//}
	//inline int getTop() {
	//	if (!checkCameraY()) return (_cameraInfo->y <= _cameraInfo->backHeight / 2) ? 0 : _cameraInfo->backHeight - _cameraInfo->height;
	//	return _cameraInfo->y - _cameraInfo->height / 2;
	//}

	//inline void setIsShaking(bool isShaking) { _isShaking = isShaking; _shakeAmount = _isShaking ? 6.0f : 0; }
	//inline bool getIsShaking() { return _isShaking; }

	//inline RECT getRect() { return RectMakeCenter(_cameraInfo->x, _cameraInfo->y, _cameraInfo->width, _cameraInfo->height); }

};

