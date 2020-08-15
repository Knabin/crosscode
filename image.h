#pragma once
#include "animation.h"

class image final
{
public:
	struct TagLoadedImageInfo
	{
		string key;
		wstring directory;

		TagLoadedImageInfo() {}
		TagLoadedImageInfo(const string& key, const wstring& directory)
			:key(key), directory(directory) {}
	};
	struct FrameRect
	{
		float x;
		float y;
		float width;
		float height;
	};
private:
	ID2D1Bitmap*		mBitmap;
	float				mAlpha;

	Vector2				mSize;
	float				mScale;
	float				mAngle;

	TagLoadedImageInfo	mLoadInfo;
	vector<image::FrameRect>	mFrameInfo;
	int							mMaxFrameX;
	int							mMaxFrameY;
private:
	friend class imageManager;
	image() = delete;
	image(ID2D1Bitmap*const bitmap, const TagLoadedImageInfo& loadinfo);
	image(ID2D1Bitmap*const bitmap, const TagLoadedImageInfo& loadinfo, const int maxFrameX, const int maxFrameY);
	virtual ~image();
	image operator = (const image& image) {}
public:
	void render(const Vector2& position);
	void render(const Vector2& position, float scale);
	void topRender(const Vector2& position);
	void aniRender(const Vector2& position, animation* ani, float scale);
	void frameRender(const Vector2& position, const int frameX, const int frameY);
	void frameTopRender(const Vector2& position, const int frameX, const int frameY);
	void frameRender(const Vector2& position, const int frameX, const int frameY, float scale);

	void ResetRenderOption();

	void setSize(const Vector2& vec) { this->mSize = vec; }
	void setAlpha(const float alpha) { this->mAlpha = alpha; }
	void setScale(const float scale) { this->mScale = scale; }
	void setAngle(const float angle) { this->mAngle = angle; }
	const int getMaxFrameX()const { return mMaxFrameX; }
	const int getMaxFrameY()const { return mMaxFrameY; }
	const string GetKey() const { return this->mLoadInfo.key; }
	const UINT getWidth() const { return mBitmap->GetPixelSize().width; }
	const UINT getHeight()const { return mBitmap->GetPixelSize().height; }
	Vector2 getSize() { return this->mSize; }
	Vector2 getFrameSize(const int& frame = 0) const { return Vector2(mFrameInfo[frame].width, mFrameInfo[frame].height); }
	const TagLoadedImageInfo& getLoadInfo() const { return mLoadInfo; }
};

