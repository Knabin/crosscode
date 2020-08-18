#pragma once
class effect;

class effectManager
{
public:
	static effectManager* getInstance()
	{
		static effectManager instance;
		return &instance;
	}

private:
	effectManager();
	~effectManager();

private:
	//생산
	typedef vector<effect*>				arrEffects;
	typedef vector<effect*>::iterator	iterEffects;
	//가공
	typedef map<string, arrEffects>			  arrEffect;
	typedef map<string, arrEffects>::iterator iterEffect;
	//포장
	typedef vector<map<string, arrEffects>>			  arrTotalEffect;
	typedef vector<map<string, arrEffects>>::iterator iterTotalEffect;

private:
	arrTotalEffect _vTotalEffect;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addEffect(string effectName, const char* imageName,
		int fps, float elapsedTime, int buffer, float scale = 1.0f);
	void addEffect(string effectName, const char* imageName,
		int imageWidth, int imageHeight, int effectWidth, int effectHeight,
		int fps, float elapsedTime, int buffer, float scale = 1.0f);

	void play(string effectName, int x, int y, float angle = 0.0f, float alpha = 1.0f);
	void play(string effectName, Vector2 pos, float angle = 0.0f, float alpha = 1.0f);
};

