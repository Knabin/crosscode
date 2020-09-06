#pragma once
#include "targetver.h"
#define _CRT_SECURE_NO_WARNINGS
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
#include <functional>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

using namespace std;

enum class pivot : int
{
	LEFTTOP, CENTER, BOTTOM
};
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib, "dxguid.lib")
//WIC 라이브러리
#pragma comment(lib, "WindowsCodecs.lib")

#include <D2D1.h>
#include <d2d1helper.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#include "Vector2.h"
#include "floatRect.h"
#include "utils.h"
#include "floatPoint.h"
#include "floatCircle.h"
#include "collision.h"

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "D2DRenderer.h"
#include "imageManager.h"
#include "timeManager.h"
#include "keyManager.h"
#include "effectManager.h"
#include "eventManager.h"
#include "objectManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "camera.h"

using namespace UTIL;
using namespace MINTCHOCO_UTIL;

//MS VS버전이 올라가면서 기존의 문자열 함수의 안정성을 올리기위해
//_s를 붙인 함수를 사용하게끔 경고하는 메시지를 무시해준다


// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#define WINNAME (LPCTSTR)(TEXT("프레임워크 테스트"))
#define WINSTARTX	0
#define WINSTARTY	0
#define WINSIZEX	GetSystemMetrics(SM_CXSCREEN)		
#define WINSIZEY	GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	WS_CAPTION | WS_SYSMENU


#define RND randomFunction::getInstance()
#define IMAGEMANAGER imageManager::getInstance()
#define TIMEMANAGER timeManager::getInstance()
#define KEYMANAGER keyManager::getInstance()
#define EFFECTMANAGER effectManager::getInstance()
#define EVENTMANAGER eventManager::getInstance()
#define OBJECTMANAGER objectManager::getInstance()
#define SCENEMANAGER sceneManager::getInstance()
#define CAMERA camera::getInstance()
#define D2DRENDERER D2DRenderer::getInstance()
#define SOUNDMANAGER soundManager::getInstance()

#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p); (p) = NULL;}}
#define NEW_SAFE_RELEASE(p)  {if(p) {(p)->Release(); (p) = NULL;}}

//====================================
// ## 20.05.29 ## Extern ##
//====================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern HDC			_hdc;