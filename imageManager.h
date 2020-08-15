#pragma once

/****************************************************************************
## ImageRenderer ##
*****************************************************************************/
class imageManager final
{
public:
	static imageManager* getInstance()
	{
		static imageManager istance;
		return &istance;
	}
	//unordered_map : 해시테이블 알고리즘으로 이루어져 있다
	//map : 레드블랙바이너리트리 알고리즘으로 이루어져 있다
private:
	typedef map<string, class image*>::iterator ImageIter;
private:
	map<string, class image*> mImageList;

	class IWICImagingFactory* mWicFactory;
public:
	imageManager();
	virtual ~imageManager();

	class image* addImage(const string& key, const wstring& file);
	class image* addFrameImage(const string& key, const wstring& file, const int maxFrameX, const int maxFrameY);
	class image* findImage(const string& key);
private:
	ID2D1Bitmap* CreateD2DBitmapFromFile(const wstring& file);
	void DeleteAll();
};

#define _ImageManager imageManager::Get()