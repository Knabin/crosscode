#pragma once
#include "image.h"

class gameNode
{
private:
	bool _managerInit;		//매니저들 초기화할꺼니

public:
	gameNode();
	virtual ~gameNode();

	//HRESULT는 마이크로소프트 전용 디버깅 반환자 인데
	//S_OK, E_FAIL, SUCCDED 등으로 출력창에 
	//제대로 초기화가 잘됐는지 아닌지를 보여준다
	virtual HRESULT init();			//초기화 전용 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 전용
	virtual void update();			//연산 전용
	virtual void render();			//그리기 전용

	//백버퍼 DC메모리 접근자

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

