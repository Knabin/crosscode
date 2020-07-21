#pragma once
class gameObject
{
protected:
	string _name;
	vector2 _position;
	vector2 _size;
	floatRect _rc;
	bool _isActive;

public:
	gameObject();
	virtual ~gameObject();

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	void setName(string name) { _name = name; }
	string getName() const { return _name; }

	void setPosition(vector2 position) { _position = position; }
	vector2 getPosition() const { return _position; }

	void setSize(vector2 size) { _size = size; }
	vector2 getSize() const { return _size; }

	void setRect(floatRect rect) { _rc = rect; }
	floatRect getRect() const { return _rc; }

	void setActive(bool active) { _isActive = active; }
	bool getActive() { return _isActive; }
};

