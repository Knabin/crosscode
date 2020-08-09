#pragma once
#include "gameObject.h"

enum class BUTTONDIRECTION : int
{
	NONE, UP, DOWN,
};

class button : public gameObject
{
private:
	BUTTONDIRECTION _direction;

	const char* _imageName;
	image* _image;
	POINT _frameDownPoint;
	POINT _frameUpPoint;
	POINT _ptMouseAbs;

	function<void(void)> _callbackFunction;

public:
	button();
	~button();

	HRESULT init(const char* imageName, float x, float y, int frameX, int frameY, int frameDownX, int frameDownY, function<void(void)> cbFunction);

	void release();
	void update();
	void render();
	void renderRelative(float x, float y);
};

