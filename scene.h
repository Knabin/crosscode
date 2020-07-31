#pragma once
class scene
{
private:

public:
	virtual ~scene();
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();
};

