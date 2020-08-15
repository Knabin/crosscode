#include "stdafx.h"
#include "image.h"

/********************************************************************************
## image ##
@@ ID2D1Bitmap* bitmap : ImageManager에서 생성된 비트맵
@@ TagLoadImageInfo loadinfo : 이미지 정보(키값,파일 경로)

프레임이미지가 아닌 이미지 클래스 생성
*********************************************************************************/
image::image(ID2D1Bitmap * const bitmap, const TagLoadedImageInfo & loadinfo)
	:mBitmap(bitmap), mLoadInfo(loadinfo), mScale(1.f), mAlpha(1.f), mAngle(0.f), mMaxFrameX(1), mMaxFrameY(1)
{
	this->mSize.x = (float)this->mBitmap->GetPixelSize().width;
	this->mSize.y = (float)this->mBitmap->GetPixelSize().height;

	FrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = mSize.x;
	rc.height = mSize.y;
	this->mFrameInfo.push_back(rc);
	this->ResetRenderOption();
}
/********************************************************************************
## image ##
@@ ID2D1Bitmap* bitmap : ImageManager에서 생성된 비트맵
@@ TagLoadImageInfo loadinfo : 이미지 정보(키값,파일 경로)
@@ int maxFrameX : 가로 프레임 수
@@ int maxFrameY : 세로 프레임 수

프레임 이미지 클래스 생성
*********************************************************************************/
image::image(ID2D1Bitmap *const bitmap, const TagLoadedImageInfo & loadinfo, const int  maxFrameX, const int  maxFrameY)
	:mBitmap(bitmap), mLoadInfo(loadinfo), mMaxFrameX(maxFrameX), mMaxFrameY(maxFrameY), mScale(1.f), mAlpha(1.f), mAngle(0.f)
{
	this->mSize.x = (float)mBitmap->GetPixelSize().width;
	this->mSize.y = (float)mBitmap->GetPixelSize().height;

	float frameX = mSize.x / (float)this->mMaxFrameX;
	float frameY = mSize.y / (float)this->mMaxFrameY;

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
		for (int i = 0; i < maxFrameX; ++i)
		{
			rc.x = (float)i * (frameX);
			rc.y = (float)j * (frameY);
			rc.width = frameX;
			rc.height = frameY;
			this->mFrameInfo.push_back(rc);
		}
	}

	this->ResetRenderOption();
}
/********************************************************************************
## ~image ##
비트맵 해제
*********************************************************************************/
image::~image()
{
	NEW_SAFE_RELEASE(mBitmap);
}
/********************************************************************************
## PerfeactRender ##
*********************************************************************************/
void image::render(const Vector2& position)
{
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale , mScale , D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x, position.y);//(position.x - size.x / 2.f, position.y - size.y / 2.f ); // 중점 ??

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, mSize.x, mSize.y);

	D2DRENDERER->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRENDERER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

void image::render(const Vector2 & position, float scale)
{
	mScale = scale;
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x, position.y);//(position.x - size.x / 2.f, position.y - size.y / 2.f ); // 중점 ??

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, mSize.x, mSize.y);

	D2DRENDERER->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRENDERER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

void image::topRender(const Vector2 & position)
{
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, 0.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x, position.y);//(position.x - size.x / 2.f, position.y - size.y / 2.f ); // 중점 ??

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, mSize.x, mSize.y);

	D2DRENDERER->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRENDERER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

void image::aniRender(const Vector2& position, animation* ani, float scale)
{
	Vector2 tempFrameSize;
	tempFrameSize.x = ani->getFrameWidth();
	tempFrameSize.y = ani->getFrameHeight();

	Vector2 size = tempFrameSize * scale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(scale, scale, D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation((position.x - size.x / 2.f), (position.y - size.y / 2.f));//(position.x - size.x / 2.f, position.y - size.y / 2.f ); // 중점 ??

	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, mSize.x, mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)ani->getFramePos().x, (float)ani->getFramePos().y,
		(float)(ani->getFramePos().x + tempFrameSize.x),
		(float)(ani->getFramePos().y + tempFrameSize.y));

	D2DRENDERER->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRENDERER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);
	ResetRenderOption();
}


/********************************************************************************
## PerfeactFrameRender ##
*********************************************************************************/
void image::frameRender(const Vector2& position, const int frameX, const int frameY)
{
	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation((position.x - size.x / 2.f), (position.y - size.y / 2.f));

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, mSize.x, mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRENDERER->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRENDERER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

void image::frameTopRender(const Vector2 & position, const int frameX, const int frameY)
{
	//Vector2 size = mSize * mScale;

	//D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(0, 0));
	//D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, 0.f));
	//D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x, position.y);//(position.x - size.x / 2.f, position.y - size.y / 2.f ); // 중점 ??

	//D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, mSize.x, mSize.y);

	//D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	//ResetRenderOption();

	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, 0.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, mSize.x, mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRENDERER->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRENDERER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

void image::frameRender(const Vector2 & position, const int frameX, const int frameY, float scale)
{//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	mScale = scale;
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, mSize.x, mSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRENDERER->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRENDERER->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

/********************************************************************************
## ResetRenderOption ##
이미지 클래스 렌더 관련 옵션들 전부 초기화
*********************************************************************************/
void image::ResetRenderOption()
{
	this->mAlpha = 1.0f;
	this->mScale = 1.0f;
	this->mAngle = 0.f;
	if (mFrameInfo.size() <= 1)
	{
		this->mSize.x = (float)mBitmap->GetPixelSize().width;
		this->mSize.y = (float)mBitmap->GetPixelSize().height;
	}
	else
	{
		this->mSize.x = mFrameInfo[0].width;
		this->mSize.y = mFrameInfo[0].height;
	}
}
