#pragma once

class image;
class animation;

class keyAniManager
{
public:
	keyAniManager* getInstance()
	{
		static keyAniManager instance;
		return &instance;
	}

private:
	keyAniManager();
	~keyAniManager();

private:
	typedef vector<animation*>						arrAnimations;
	typedef vector<animation*>::iterator			iterAnimations;

	typedef map<string, arrAnimations>				arrAnimation;
	typedef map<string, arrAnimations>::iterator	iterAnimation;

	typedef vector<map<string, arrAnimations>>				arrTotalAnimation;
	typedef vector<map<string, arrAnimations>>::iterator	iterTotalAnimation;

private:
	arrTotalAnimation _vTotalAnimation;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, int buffer);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, int buffer);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj, int buffer);

	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj, int buffer);

	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, int buffer);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, int buffer);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj, int buffer);

	void start(string animationKeyName);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);

	animation* findAnimation(string animationKeyName);

	void deleteAll();

};

