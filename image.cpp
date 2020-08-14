#include "stdafx.h"
#include "image.h"

//#pragma <- 컴파일러 지시기
#pragma comment(lib, "msimg32.lib")

//멤버 이니셜라이즈
image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//예외처리
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//위에 셋팅이 실패해서 백버퍼가 NULL이면
	if (_imageInfo == NULL)
	{
		//메모리 해제 후
		release();

		//실패했단 메세지를 호출해라
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);


	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 혹시나 남아있다면 해제해라
	if (_imageInfo != NULL) release();

	//DC영역을 가져다 사용하고 싶을때
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역 하나 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//비트맵 정보가 생성이 되지 않았다면
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 혹시나 남아있다면 해제해라
	if (_imageInfo != NULL) release();

	//DC영역을 가져다 사용하고 싶을때
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역 하나 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//비트맵 정보가 생성이 되지 않았다면
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//이미지 정보가 혹시나 남아있다면 해제해라
	if (_imageInfo != NULL) release();

	//DC영역을 가져다 사용하고 싶을때
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역 하나 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//비트맵 정보가 생성이 되지 않았다면
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}
/////////////////
HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor, float angle)
{

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hBBIT = _imageInfo->hBit;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->angle = angle;
	_imageInfo->hBit = GetRotatedBitmap(hdc, _imageInfo->hBit, 0, 0, _imageInfo->width, _imageInfo->height, angle, transColor);

	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

////////////////
void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		if (_blendImage != nullptr) 
		{
			SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
			DeleteObject(_blendImage->hBit);
			DeleteDC(_blendImage->hMemDC);
		}

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}
//////////////
void image::render(HDC hdc, int destX, int destY, float angle)
{	
	if (_imageInfo->angle != angle)
	{
		_imageInfo->hBit = GetRotatedBitmap(_imageInfo->hMemDC, _imageInfo->hBBIT, 0, 0, _imageInfo->width, _imageInfo->height, angle, RGB(255, 0, 255));
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	}

	
	GdiTransparentBlt(
		hdc,					//복사될 영역 DC
		destX,					//복사될 좌표 X
		destY,					//복사될 좌표 Y
		_imageInfo->width,		//복사될 크기 (가로)
		_imageInfo->height,		//복사될 크기 (세로)
		_imageInfo->hMemDC,		//복사해올 DC
		0, 0,					//복사해올 좌표 X,Y
		_imageInfo->width,		//복사할 가로크기
		_imageInfo->height,		//복사할 세로크기
		_transColor);			//복사할때 제외할 픽셀값

	_imageInfo->angle = angle;
}
//////////////
void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역 DC
			_imageInfo->x,					//복사될 좌표 X
			_imageInfo->y,					//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			0, 0,					//복사해올 좌표 X,Y
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_transColor);			//복사할때 제외할 픽셀값
	}
	else
	{
		//DC영역 간의 고속복사를 해주는 함수 BitBlt
		BitBlt(hdc,					//복사할 DC
			_imageInfo->x,			//복사할 X좌표(left)
			_imageInfo->y,			//복사할 Y좌표(top)
			_imageInfo->width,		//복사할 크기
			_imageInfo->height,		//복사할 크기
			_imageInfo->hMemDC,		//복사될 DC
			0, 0,					//복사될 X,Y(left, top)
			SRCCOPY);				//변형없이 복사하겠다
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역 DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			0, 0,					//복사해올 좌표 X,Y
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_transColor);			//복사할때 제외할 픽셀값
	}
	else
	{
		//DC영역 간의 고속복사를 해주는 함수 BitBlt
		BitBlt(hdc,					//복사할 DC
			destX,					//복사할 X좌표(left)
			destY,					//복사할 Y좌표(top)
			_imageInfo->width,		//복사할 크기
			_imageInfo->height,	//복사할 크기
			_imageInfo->hMemDC,	//복사될 DC
			0, 0,					//복사될 X,Y(left, top)
			SRCCOPY);				//변형없이 복사하겠다
	}


}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역 DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			sourWidth,				//복사될 크기 (가로)
			sourHeight,				//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			sourX, sourY,			//복사해올 좌표 X,Y
			sourWidth,				//복사할 가로크기
			sourHeight,				//복사할 세로크기
			_transColor);			//복사할때 제외할 픽셀값
	}
	else
	{
		//DC영역 간의 고속복사를 해주는 함수 BitBlt
		BitBlt(hdc,					//복사할 DC
			destX,					//복사할 X좌표(left)
			destY,					//복사할 Y좌표(top)
			sourWidth,				//복사할 크기
			sourHeight,				//복사할 크기
			_imageInfo->hMemDC,		//복사될 DC
			sourX, sourY,			//복사될 X,Y(left, top)
			SRCCOPY);				//변형없이 복사하겠다
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역 DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->frameWidth,	//복사될 크기 (가로)
			_imageInfo->frameHeight,//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//복사해올 좌표 X,Y
			_imageInfo->frameWidth,								//복사할 가로크기
			_imageInfo->frameHeight,							//복사할 세로크기
			_transColor);			//복사할때 제외할 픽셀값
	}
	else
	{
		//DC영역 간의 고속복사를 해주는 함수 BitBlt
		BitBlt(hdc,							//복사할 DC
			destX,							//복사할 X좌표(left)
			destY,							//복사할 Y좌표(top)
			_imageInfo->frameWidth,			//복사할 크기
			_imageInfo->frameHeight,		//복사할 크기
			_imageInfo->hMemDC,				//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//복사될 X,Y(left, top)
			SRCCOPY);				//변형없이 복사하겠다
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역 DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->frameWidth,	//복사될 크기 (가로)
			_imageInfo->frameHeight,//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//복사해올 좌표 X,Y
			_imageInfo->frameWidth,								//복사할 가로크기
			_imageInfo->frameHeight,							//복사할 세로크기
			_transColor);			//복사할때 제외할 픽셀값
	}
	else
	{
		//DC영역 간의 고속복사를 해주는 함수 BitBlt
		BitBlt(hdc,							//복사할 DC
			destX,							//복사할 X좌표(left)
			destY,							//복사할 Y좌표(top)
			_imageInfo->frameWidth,			//복사할 크기
			_imageInfo->frameHeight,		//복사할 크기
			_imageInfo->hMemDC,				//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//복사될 X,Y(left, top)
			SRCCOPY);				//변형없이 복사하겠다
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//정밀한 예외처리를 할땐 나머지 연산자를 꼭 이용합시다
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;					//그려질 영역 left
	int drawAreaY = drawArea->top;					//그려질 영역 top
	int drawAreaW = drawArea->right - drawAreaX;	//그려질 영역 width
	int drawAreaH = drawArea->bottom - drawAreaY;	//그려질 영역 height

	//세로부터
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//화면 밖 나간 영역 확보
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}


		//화면밖으로 나간영역만큼을 산정한다
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}


	}


}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, sourX, sourY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			sourWidth, sourHeight,
			_blendImage->hMemDC, sourX, sourY, sourWidth,
			sourHeight, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth,
			sourHeight, _blendFunc);
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::aniRedRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{
	alphaRedRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

void image::aniAlphaRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,	// 출력할 DC, 출력할 위치
			_imageInfo->frameWidth,		// 출력할 길이
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,			// 가져올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	// 가져올 위치
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		// 가져올 크기
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY,	// 출력할 dc, 출력할 위치
			_imageInfo->frameWidth,		// 출력할 이미지 크기
			_imageInfo->frameHeight,
			_blendImage->hMemDC,		// 가져올 dc
			0, 0,						// 가져올 위치 x,y
			_imageInfo->frameWidth,		// 가져올 크기
			_imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,	// 출력할 DC, 출력할 위치
			_imageInfo->frameWidth,		// 출력할 길이
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,			// 가져올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	// 가져올 위치
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		// 가져올 크기
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY,	// 출력할 dc, 출력할 위치
			_imageInfo->frameWidth,		// 출력할 이미지 크기
			_imageInfo->frameHeight,
			_blendImage->hMemDC,		// 가져올 dc
			0, 0,						// 가져올 위치 x,y
			_imageInfo->frameWidth,		// 가져올 크기
			_imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendFunc);
	}

}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int size, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,	// 출력할 DC, 출력할 위치
			_imageInfo->frameWidth,		// 출력할 길이
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,			// 가져올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	// 가져올 위치
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		// 가져올 크기
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY,	// 출력할 dc, 출력할 위치
			_imageInfo->frameWidth,		// 출력할 이미지 크기
			_imageInfo->frameHeight,
			_blendImage->hMemDC,		// 가져올 dc
			0, 0,						// 가져올 위치 x,y
			_imageInfo->frameWidth,		// 가져올 크기
			_imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendFunc);
	}
}

void image::alphaRedRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	HDC tempDC = CreateCompatibleDC(_imageInfo->hMemDC);
	HBITMAP tempBitMap = CreateCompatibleBitmap(_imageInfo->hMemDC, _imageInfo->width, _imageInfo->height);
	HBITMAP tempOrigin = static_cast<HBITMAP>(SelectObject(tempDC, tempBitMap));

	HDC redDC = CreateCompatibleDC(_imageInfo->hMemDC);
	HBITMAP redBitMap = CreateCompatibleBitmap(_imageInfo->hMemDC, _imageInfo->width, _imageInfo->height);
	HBITMAP redOrigin = static_cast<HBITMAP>(SelectObject(redDC, redBitMap));

	if (_trans)
	{
		// 1. redDC에 빨간색 DC 복사 (bitblt : IMAGE_MANAGER(origin redDC) -> redDC)
		// 2. tempDC에 빨간색 DC 복사 (bitblt : redDC -> tempDC)
		// 3. tempDC에 캐릭터 그리기(transparent(RGB(255, 0, 255)) : imageDC -> tempDC)
		// 4. redDC에 alpharender로 그리기 (alphaBlend : tempDC -> redDC) 
		// 5. 원래 그리려던 DC에 이미지 그리기(transparent(255, 0, 0) : redDC -> hdc)

		BitBlt(redDC, 0, 0, _imageInfo->width, _imageInfo->height,
			imageManager::getInstance()->findImage("redDC")->getMemDC(), 0, 0, SRCCOPY);

		BitBlt(tempDC, 0, 0, _imageInfo->width, _imageInfo->height,
			redDC, 0, 0, SRCCOPY);

		GdiTransparentBlt(tempDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(redDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			tempDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);

		GdiTransparentBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			redDC, 0, 0, _imageInfo->width, _imageInfo->height, RGB(255, 0, 0));
	}
	else // 여기는 구현 안했습니다.
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}

	DeleteObject(tempDC);
	DeleteObject(tempBitMap);
	DeleteObject(tempOrigin);

	DeleteObject(redDC);
	DeleteObject(redBitMap);
	DeleteObject(redOrigin);
}

void image::alphaRedRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	HDC tempDC = CreateCompatibleDC(_imageInfo->hMemDC);
	HBITMAP tempBitMap = CreateCompatibleBitmap(_imageInfo->hMemDC, sourWidth, sourHeight);
	HBITMAP tempOrigin = static_cast<HBITMAP>(SelectObject(tempDC, tempBitMap));

	HDC redDC = CreateCompatibleDC(_imageInfo->hMemDC);
	HBITMAP redBitMap = CreateCompatibleBitmap(_imageInfo->hMemDC, sourWidth, sourHeight);
	HBITMAP redOrigin = static_cast<HBITMAP>(SelectObject(redDC, redBitMap));

	if (_trans)
	{
		// 1. redDC에 빨간색 DC 복사 (bitblt : IMAGE_MANAGER(origin redDC) -> redDC)
		// 2. tempDC에 빨간색 DC 복사 (bitblt : redDC -> tempDC)
		// 3. tempDC에 캐릭터 그리기(transparent(RGB(255, 0, 255)) : imageDC -> tempDC)
		// 4. redDC에 alpharender로 그리기 (alphaBlend : tempDC -> redDC) 
		// 5. 원래 그리려던 DC에 이미지 그리기(transparent(255, 0, 0) : redDC -> hdc)

		// redDC의 0,0에 사진 크기만큼 빨간색 사진을 복사한다!
		BitBlt(redDC, 0, 0, sourWidth, sourHeight,
			imageManager::getInstance()->findImage("redDC")->getMemDC(), 0, 0, SRCCOPY);

		// tempDC의 0,0에 사진 크기만큼 redDC에서 가져온다
		BitBlt(tempDC, 0, 0, sourWidth, sourHeight,
			redDC, 0, 0, SRCCOPY);

		// tempDC의 0,0에 사진 크기만큼 해당 사진을 복사해 온다
		GdiTransparentBlt(tempDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY,
			sourWidth, sourHeight, _transColor);

		// redDC에 alpha로 
		AlphaBlend(redDC, 0, 0,
			sourWidth, sourHeight,
			tempDC, 0, 0, sourWidth,
			sourHeight, _blendFunc);

		GdiTransparentBlt(hdc, destX, destY, sourWidth, sourHeight,
			redDC, 0, 0, sourWidth, sourHeight, RGB(255, 0, 0));
	}
	else // 여기는 구현 안했습니다.
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}

	DeleteObject(tempDC);
	DeleteObject(tempBitMap);
	DeleteObject(tempOrigin);

	DeleteObject(redDC);
	DeleteObject(redBitMap);
	DeleteObject(redOrigin);
}


