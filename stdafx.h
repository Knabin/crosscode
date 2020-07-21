#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <vector>
#include <map>
#include <queue>

using namespace std;

enum class pivot : int
{
	LEFTTOP, CENTER, BOTTOM
};

#include "vector2.h"
#include "utils.h"
#include "floatPoint.h"
#include "floatRect.h"
#include "floatCircle.h"

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "timeManager.h"
#include "keyManager.h"
#include "keyAniManager.h"
#include "effectManager.h"
#include "eventManager.h"
#include "iniDataManager.h"
#include "objectManager.h"
#include "soundManager.h"
#include "textData.h"

using namespace UTIL;


//MS VS버전이 올라가면서 기존의 문자열 함수의 안정성을 올리기위해
//_s를 붙인 함수를 사용하게끔 경고하는 메시지를 무시해준다


// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#define WINNAME (LPCTSTR)(TEXT("프레임워크 테스트"))
#define WINSTARTX	200
#define WINSTARTY	50
#define WINSIZEX	1024		
#define WINSIZEY	768
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()

#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p); (p) = NULL;}}

//====================================
// ## 20.05.29 ## Extern ##
//====================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;