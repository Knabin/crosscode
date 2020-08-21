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
	//매개변수에 넣은 숫자의 -1만큼 범위를 가지는 난수
	inline int getInt(int num) { return rand() % num; }

	//정수와 정수 사이에 범위에서 랜덤한 수를 뽑게하는 함수
	inline int getFromIntTo(int fromNum, int toNum)
	{
		if (toNum != 0)
			return rand() % (toNum - fromNum) + fromNum;
		else
			return 0;
	}

	//=========================================
	// ## 실수형 난수 ##
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