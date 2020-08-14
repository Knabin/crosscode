#pragma once
#include "image.h"
#include <map>

class imageManager
{
public:
	static imageManager* getInstance()
	{
		static imageManager instance;
		return &instance;
	}

private:
	imageManager();
	~imageManager();

private:
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT init();
	void release();

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);

	image * addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor, float angle);

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//이미지 찾는 함수 (중요)
	image* findImage(string strKey);

	BOOL deleteImage(string strKey);
	
	BOOL deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

};

