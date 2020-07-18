#pragma once
#include <vector>

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//void* ���� ���� �� �ֽ��ϴ� �ٸ� ����ȯ �ؼ� ��ߡ�

class animation
{
public:
	typedef vector<POINT>	vFrameList;	//�ִϸ��̼� ������ �����
	typedef vector<int>		vPlayList;	//�ִϸ��̼� �÷��� �ε��� �����

private:
	int _frameNum;	//�ִϸ��̼� ������ ����

	vFrameList	_frameList;
	vPlayList	_playList;

	int _frameWidth;		//������ ����ũ��
	int _frameHeight;		//������ ����ũ��

	BOOL _loop;				//�ִϸ��̼� ���� ����

	float _frameUpdateSec;	//������ ����ð�
	float _elapsedSec;		//��Ÿ Ÿ��

	DWORD _nowPlayIndex;	//���� �÷��� �ε���
	BOOL _play;				//�ִϸ��̼� �������

	void*						_obj;
	CALLBACK_FUNCTION			_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	//����Ʈ �ִϸ��̼�
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//�迭 �ִϸ��̼�
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//���� �ִϸ��̼�
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);


	void setFPS(int framePerSec);

	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }


};

