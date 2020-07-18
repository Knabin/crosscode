#pragma once
#include "animation.h"

class image
{
public:
	//이미지 불러올 타입
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//리소스로부터
		LOAD_FILE,			//파일로부터
		LOAD_EMPTY,			//빈 비트맵
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		//리소스 불러올때 사용할 ID값
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;			//이미지 뿌려질 곳의 x(left)
		float y;			//이미지 뿌려질 곳의 y(top)
		int width;
		int height;
		int currentFrameX;	//현재 프레임 가로번호 (X열)
		int currentFrameY;	//현재 프레임 세로번호 (Y열)
		int maxFrameX;		//최대 프레임 번호 가로
		int maxFrameY;		//최대 프레임 번호 세로
		int frameWidth;		//한 프레임의 가로크기
		int frameHeight;	//한 프레임의 세로크기
		BYTE loadType;	//이미지 불러올 타입

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;	//파일 이름(bmp)
	BOOL			_trans;		//특정픽셀 제거할꺼니? 유무
	COLORREF		_transColor;//제거할 특정 픽셀값 정보

	BLENDFUNCTION	_blendFunc;	//알파블렌드 관련 함수
	LPIMAGE_INFO	_blendImage;//알파블렌드 처리할 이미지정보

public:
	image();
	~image();

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	//프레임 이미지 용 초기화 함수
	HRESULT init(const char* fileName, float x, float y,
		int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);


	void release();

	//혹시 다른 픽셀값으로 날려야 할때 날려줄 픽셀값 변경할 함수
	void setTransColor(BOOL trans, COLORREF transColor);


	//렌더함수(뿌려질DC)
	void render(HDC hdc);

	//렌더함수(뿌려질DC, left, top)
	void render(HDC hdc, int destX, int destY);

	//렌더함수(뿌려질DC, 그려질 좌표X(left), 그려질 좌표Y(top), 가져올좌표X, 가져올좌표Y, 가져올 가로크기, 가져올 세로크기)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//이미지 프레임 렌더(뿌려질DC, 그려질 좌표(left), 그려질 좌표(top))
	void frameRender(HDC hdc, int destX, int destY);

	//이미지 프레임 렌더(뿌려질DC, 그려질 좌표(left), 그려질 좌표(top), 현재 프레임 가로번호, 현재 프레임 세로번호)
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//알파렌더 (뿌려질DC, 알파값(0 ~ 255))
	void alphaRender(HDC hdc, BYTE alpha);
	//알파렌더 (뿌려질DC, 뿌릴위치X, 뿌릴위치Y, 알파값(0 ~ 255))
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//애니메이션 렌더링용
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void aniRedRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);
	void aniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//프레임 알파렌더(뿌려질DC, 그려질 좌표(left), 그려질 좌표(top), 알파값(0 ~ 255))
	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	//프레임 알파렌더(뿌려질DC, 그려질 좌표(left), 그려질 좌표(top), 현재 프레임 가로번호, 현재 프레임 세로번호, 알파값(0 ~ 255))
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void alphaRedRender(HDC hdc, BYTE alpha);
	void alphaRedRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//=======================================
	// ## 이미지 관련 접근자, 설정자 ##
	//=======================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }


};

