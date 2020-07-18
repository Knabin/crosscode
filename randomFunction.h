#pragma once
#include "singletonBase.h"
#include <time.h>

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{

	}

	//매개변수에 넣은 숫자의 -1만큼 범위를 가지는 난수
	inline int getInt(int num) { return rand() % num; }

	//정수와 정수 사이에 범위에서 랜덤한 수를 뽑게하는 함수
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum) + fromNum;
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