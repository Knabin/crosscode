#include "stdafx.h"
#include "D2DRenderer.h"



/**********************************************************************************************
## RenderText ##
@@ int x : x 좌표
@@ int y : y 좌표
@@ wstring text : 그릴 텍스트
@@ int size : 폰트 사이즈
@@ DefaultBrush brush : 그릴 브러쉬 = DefaultBrush::Black
@@ DWRITE_TEXT_ALIGNMENT align : 정렬 옵션 = DWRITE_TEXT_ALIGNMENT_LEADING
@@ bool isRelative : 카메라 보정 여부 = false
@@ wstring font : 폰트 = 


기본 정의해둔 브러쉬로 텍스트 렌더링
************************************************************************************************/
void D2DRenderer::RenderText(const int x, const int y, const wstring& text, const int size,
	const DefaultBrush& defaultBrush, const DWRITE_TEXT_ALIGNMENT& align, const wstring& font)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout = nullptr;
	HRESULT hr = this->mDWFactory->CreateTextLayout
	(
		text.c_str(),
		text.length(),
		this->mFontList[font],
		(float)text.length() * size,
		(float)size,
		&layout
	);
	assert(SUCCEEDED(hr));

	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();

	layout->SetFontSize((float)size, range);
	layout->SetTextAlignment(align);

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	mD2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout,
		mDefaultBrushList[(UINT)defaultBrush]);

	NEW_SAFE_RELEASE(layout);
}

/**********************************************************************************************
## RenderText ##
@@ int x : 그릴좌표
@@ int y : 그릴좌표
@@ wstring text : 그릴 텍스트
@@ COLORREF color : RGB컬러
@@ float alpha : 알파 값
@@ int size : 폰트 사이즈
@@ DWRITE_TEXT_ALIGNMENT align : 정렬옵션
@@ bool isRelative : 카메라 보정 여부
@@ wstring font : 폰트

새로운 브러쉬 생성후 렌더링
************************************************************************************************/
void D2DRenderer::RenderText(const int x, const int y, const wstring& text, const COLORREF& color,
	const float alpha, const int size, const DWRITE_TEXT_ALIGNMENT& align, const wstring& font)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout = nullptr;
	//텍스트 레이아웃 생성
	mDWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		mFontList[font],
		(float)text.length() * size,
		(float)size,
		&layout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);
	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	//브러쉬 생성
	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, brush);

	NEW_SAFE_RELEASE(brush);
	NEW_SAFE_RELEASE(layout);
}
/**********************************************************************************************
## RenderTextField ##
@@ int x : 그릴 좌표
@@ int y : 그릴 좌표
@@ wstring text : 그릴 텍스트
@@ int size : 폰트 사이즈
@@ int width : 영역 가로길이
@@ int heifht : 영역 세로길이
@@ DefaultBrush brush : 기본 정의 브러쉬
@@ DWRITE_TEXT_ALIGNMENT align : 정렬 옵션
@@ bool isRalative : 카메라 보정 여부
@@ wstring font : 폰트

영역내에서 기본 브러쉬로 글자 출력
************************************************************************************************/
void D2DRenderer::RenderTextField(const int x, const int y, const wstring& text, const int size,
	const int width, const int height, const DefaultBrush& defaultBrush, const DWRITE_TEXT_ALIGNMENT& align, const wstring& font)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout = nullptr;
	mDWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		mFontList[font],
		(float)width,
		(float)height,
		&layout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);

	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, mDefaultBrushList[(UINT)defaultBrush]);

	NEW_SAFE_RELEASE(layout);
}
/**********************************************************************************************
## RenderText ##
@@ int x : 그릴 좌표
@@ int y : 그릴 좌표
@@ wstring text : 그릴 텍스트
@@ COLORREF color : 그릴 컬러
@@ int size : 폰트 사이즈
@@ int width : 가로 영역 길이
@@ int height : 세로 영역 길이
@@ float alpha : 알파값
@@ DWRITE_TEXT_ALIGNMENT align : 정렬 옵션
@@ bool isRelative : 카메라 보정여부
@@ wstring font : 폰트

영역안에서 새로운 브러쉬를 생성해서 폰트출력
************************************************************************************************/
void D2DRenderer::RenderTextField(const int x, const int y, const wstring& text, const COLORREF& color,
	const int size, const int width, const int height, const float alpha, const DWRITE_TEXT_ALIGNMENT& align, const wstring& font)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout = nullptr;
	mDWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		mFontList[font],
		(float)width,
		(float)height,
		&layout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);

	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	//브러쉬 생성
	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->DrawTextLayout(D2D1::Point2F((float)x, (float)y), layout, brush);

	NEW_SAFE_RELEASE(layout);
	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## DrawLine ##
@@ Vector2 start : 시작 점
@@ Vector2 end : 끝 점
@@ D2D1::ColorF::Enum color : 색상
@@ float alpha : 알파 값
@@ bool isRelative : 카메라 보정 여부
@@ float strokeWidth : 선 굵기
************************************************************************************************/
void D2DRenderer::DrawLine(const Vector2& start, const Vector2& end, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth)
{
	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	Vector2 startPos = start;
	Vector2 endPos = end;

	mD2DRenderTarget->DrawLine(D2D1::Point2F(startPos.x, startPos.y), D2D1::Point2F(endPos.x, endPos.y), brush, strokeWidth);
	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## RenderText ##
@@ Vector2 start : 시작 점
@@ Vector2 end : 끝 점
@@ DefaultBrush brush : 기본 정의 브러쉬
@@ bool isRelative : 카메라 보정 여부
@@ float stroke : 선 굵기
***********************************************************************************************/
void D2DRenderer::DrawLine(const Vector2& start, const Vector2& end, const DefaultBrush& defaultBrush, const float strokeWidth)
{
	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	Vector2 startPos = start;
	Vector2 endPos = end;

	mD2DRenderTarget->DrawLine(D2D1::Point2F(startPos.x, startPos.y),
		D2D1::Point2F(endPos.x, endPos.y), mDefaultBrushList[(UINT)defaultBrush], strokeWidth);

}
/**********************************************************************************************
## DrawRectangle ##
@@ FloatRect rc : 렉트
@@ D2D1::ColorF::Enum color : 컬러
@@ float alpha : 알파 값
@@ bool isRelative : 카메라 보정여부
@@ float strokeWidth : 선 굵기
************************************************************************************************/
void D2DRenderer::DrawRectangle(const floatRect& rc, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth)
{
	floatRect rect = rc;

	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	mD2DRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}
void D2DRenderer::DrawRectangle(const RECT & rc, const D2D1::ColorF::Enum & color, const float alpha, const float strokeWidth)
{
	RECT rect = rc;

	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());


	mD2DRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## DrawRectangle ##
@@ FloatRect rc : 그릴 렉트
@@ DefaultBrush brush : 그릴 브러쉬
@@ bool isRelative : 카메라 보정 여부
@@ float stroke : 선 굵기
************************************************************************************************/
void D2DRenderer::DrawRectangle(const floatRect& rc, const DefaultBrush& defaultBrush, const float strokeWidth)
{
	floatRect rect = rc;

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	mD2DRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		mDefaultBrushList[(UINT)defaultBrush], strokeWidth);
}
/**********************************************************************************************
## DrawEllipse ##
@@ Vector2 origin : 중점
@@ flaot radius : 반지름
@@ DefaultBrush brush : 브러쉬
@@ bool isRelative : 카메라 보정여부
@@ float stroke : 선 굵기
************************************************************************************************/
void D2DRenderer::DrawEllipse(const Vector2& origin, const float radius, const DefaultBrush& defaultBrush, const float strokeWidth)
{
	floatRect rc = RectMakePivot(origin, Vector2(radius, radius), pivot::CENTER);
	Vector2 pos = origin;
	float tempRadius = radius;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->DrawEllipse(&ellipse, mDefaultBrushList[(UINT)defaultBrush], strokeWidth);
}
/**********************************************************************************************
## DrawEllipse ##
@@ Vector2 origin : 중점
@@ flaot radius : 반지름
@@ D2D1::ColorF::Enum color : D2D컬러 값
@@ float alpha : 알파 값
@@ bool isRelative : 카메라 보정 여부
@@ float stroke : 선 굵기
************************************************************************************************/
void D2DRenderer::DrawEllipse(const Vector2& origin, const float radius, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth)
{
	floatRect rc = RectMakePivot(origin, Vector2(radius, radius), pivot::CENTER);
	Vector2 pos = origin;
	float tempRadius = radius;

	ID2D1SolidColorBrush* brush(nullptr);
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->DrawEllipse(&ellipse, brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## FillRectagle ##
@@ FloatRect rc : 그릴 렉트
@@ D2D1::ColorF::Enum color : D2D컬러
@@ float alpha  : 알파 값
@@ bool isRelative : 카메라 보정 여부
************************************************************************************************/
void D2DRenderer::FillRectangle(const floatRect& rc, const D2D1::ColorF::Enum& color, const float alpha)
{
	floatRect rect = rc;

	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);
	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom), brush);

	NEW_SAFE_RELEASE(brush);
}
void D2DRenderer::FillRectangle(const RECT & rc, const D2D1::ColorF::Enum & color, const float alpha)
{
	RECT rect = rc;

	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);
	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->FillRectangle(D2D1::Rect(rect.left, rect.top, rect.right, rect.bottom), brush);

	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## FillRectangle  ##
@@ FloatRec rc : 크릴 렉트
@@ DefaultBrush brush : 브러쉬
@@ bool isRelative : 카메라 보정여부
************************************************************************************************/
void D2DRenderer::FillRectangle(const floatRect& rc, const DefaultBrush& defaultBrush)
{
	floatRect rect = rc;

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	mD2DRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		mDefaultBrushList[(UINT)defaultBrush]);
}
/**********************************************************************************************
## FillEllipse ##
@@ Vector2 origin : 중점 좌표
@@ flaot radius : 반지름
@@ D2D1::ColorF::Enum color : D2D컬러
@@ float alpha : 알파 값
@@ bool isRelative : 카메라 보정 여부
************************************************************************************************/
void D2DRenderer::FiilEllipse(const Vector2& origin, const float radius, const D2D1::ColorF::Enum& color, const float alpha)
{
	floatRect rc = RectMakePivot(origin, Vector2(radius, radius), pivot::CENTER);
	Vector2 pos = origin;
	float tempRadius = radius;

	ID2D1SolidColorBrush* brush(nullptr);
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->FillEllipse(&ellipse, brush);
	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## FillEllipse ##
@@ Vector2 origin : 중점 좌표
@@ float radius : 반지름
@@ DefaultBrush brush : 브러쉬
@@ bool isRlative : 카메라 보정 여부
************************************************************************************************/
void D2DRenderer::FiilEllipse(const Vector2& origin, const float radius, const DefaultBrush& brush)
{
	floatRect rc = RectMakePivot(origin, Vector2(radius, radius), pivot::CENTER);
	Vector2 pos = origin;
	float tempRadius = radius;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	mD2DRenderTarget->FillEllipse(&ellipse, mDefaultBrushList[(UINT)brush]);
}

void D2DRenderer::DrawRotationNullRectangle(const floatRect& rc, const D2D1::ColorF::Enum& color,
	const float alpha, const float angle, const float strokeWidth)
{
	floatRect rect = rc;

	D2D1_POINT_2F offset;
	offset.x = rect.left + rect.GetWidth() / 2;
	offset.y = rect.top + rect.GetHeight() / 2;

	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, offset));

	mD2DRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}

void D2DRenderer::DrawRotationFillRectangle(const floatRect& rc, const D2D1::ColorF& color, const float angle)
{
	floatRect rect = rc;

	D2D1_POINT_2F offset;
	offset.x = rect.left + rect.GetWidth() / 2;
	offset.y = rect.top + rect.GetHeight() / 2;
	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(color, &brush);
	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, offset));
	mD2DRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom), brush);

	NEW_SAFE_RELEASE(brush);
}


void D2DRenderer::SkewRectangle(const floatRect& rc, const D2D1::ColorF& color, const float angle, float angle2)
{
	floatRect rect = rc;

	D2D1_POINT_2F offset;
	offset.x = rect.left + rect.GetWidth() / 2;
	offset.y = rect.top + rect.GetHeight() / 2;

	ID2D1SolidColorBrush* brush;
	mD2DRenderTarget->CreateSolidColorBrush(color, &brush);
	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, offset));
	mD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Skew(angle2, 0, offset));
	mD2DRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom), brush);

	NEW_SAFE_RELEASE(brush);
}