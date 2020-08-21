#pragma once
#include <time.h>

class randomFunction
{
public:
	static randomFunction* getInstance()
	{
		static randomFunction instance;
		return &instance;
	}

private:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{
	}

public:
	//�Ű������� ���� ������ -1��ŭ ������ ������ ����
	inline int getInt(int num) { return rand() % num; }

	//������ ���� ���̿� �������� ������ ���� �̰��ϴ� �Լ�
	inline int getFromIntTo(int fromNum, int toNum)
	{
		if (toNum != 0)
			return rand() % (toNum - fromNum) + fromNum;
		else
			return 0;
	}

	//=========================================
	// ## �Ǽ��� ���� ##
	//=========================================

	inline float getFloat(float num)
	{
		return (float)rand() / (float)num;
	}

	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}

};