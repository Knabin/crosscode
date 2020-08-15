#include "stdafx.h"
#include "D2DRenderer.h"

/*****************************************************
## D2DRenderer ##
*******************************************************/
D2DRenderer::D2DRenderer()
	:mD2DFactory(nullptr), mD2DRenderTarget(nullptr), mDWFactory(nullptr)
{
	this->CreateFactory();
	this->CreateRenderTarget();
	this->CreateDefaultBrush();
	this->AddTextFormat(L"맑은고딕");
	mD2DRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
}

/*****************************************************
## ~D2DRenderer ##
*******************************************************/
D2DRenderer::~D2DRenderer()
{
	TextIter iter = mFontList.begin();
	for (; iter != mFontList.end(); ++iter)
		NEW_SAFE_RELEASE(iter->second);

	for (UINT i = 0; i < (UINT)DefaultBrush::End; ++i)
		NEW_SAFE_RELEASE(mDefaultBrushList[i]);

	NEW_SAFE_RELEASE(mDWFactory);

	NEW_SAFE_RELEASE(mD2DSurface);
	NEW_SAFE_RELEASE(mD2DRenderTarget);
	NEW_SAFE_RELEASE(mD2DFactory);
}
/*****************************************************
## BeginRender ##
*******************************************************/
void D2DRenderer::BeginRender(const D2D1::ColorF& backgroundColor)
{
	mD2DRenderTarget->BeginDraw();
	mD2DRenderTarget->Clear(backgroundColor);
}
/*****************************************************
## EndRender ##
*******************************************************/
void D2DRenderer::EndRender()
{
	mD2DRenderTarget->EndDraw();
}

/*****************************************************
## CreateFactory ##
*******************************************************/
void D2DRenderer::CreateFactory()
{
	//class Item 
	//{
	//private: // 무분별하게 쓰기싫을때 생성자를 private로
	//	friend class Factory;
	//	Item() {}
	//	~Item() {}
	//};

	//class Factory // 팩토리 디자인 패턴
	//{
	//public:
	//	Item* CreateItem() {
	//		return new Item();
	//	}
	//};



	// 1) D2D 팩토리 생성
	// 싱글쓰레드타입으로 
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
#ifdef _DEBUG
	assert(SUCCEEDED(hr)); // E_FAIL이 들어오면 멈춘다.
#endif
	// 2) DWriteFactory 생성
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(*&mDWFactory),
		(IUnknown**)&mDWFactory
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
}
/*****************************************************
## CreateRenderTarget ##
*******************************************************/
void D2DRenderer::CreateRenderTarget()
{
	// 랜더 타겟이란 백버퍼의 역할을 하는 클래스이자 여러 랜더링을 위한 유틸적인 것들이 들어있는 클래스이다.
	// 그래서 화면에 뭔가 랜더링을 요청하려면 랜더타겟을 통해서만 가능 하다.

	//스왑체인으로부터 백버퍼 정보 받아온다. 
	HRESULT hr;
	// 1) 윈도우 핸들을 통해서 화면 Rect를 받아온다.(GetClientRect())
	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);

	// 이전에는 Factory를 통해서 현재 디바이스의 DPI를 받아 왔으나 어떤 이유에서인지 MS에서 해당 함수를 사용하지 못하게 변경함, 자체 API함수로 불러오자
	// mD2DFactory->GetDesktopDpi(&dpiX, &dpiY)

	// 2) 디바이스의 DPI정보를 받아온다. (WinAPI 함수)
	FLOAT dpiX = GetDeviceCaps(_hdc, LOGPIXELSX);
	FLOAT dpiY = GetDeviceCaps(_hdc, LOGPIXELSY);

	// 3) 랜더타겟을 생성하기 위한 속성 값들을 초기화.
	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	// 4) 랜더타겟의 사이즈 초기화(화면 크기로) 
	D2D1_SIZE_U renderTargetSize = D2D1::SizeU(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	// 5) 랜더타겟의 생성
	hr = mD2DFactory->CreateHwndRenderTarget(
		renderTargetProperties,
		D2D1::HwndRenderTargetProperties(_hWnd, renderTargetSize),
		&mD2DRenderTarget
	);

	assert(SUCCEEDED(hr));
}
/*****************************************************
## CreateDefaultBrush ##
*******************************************************/
void D2DRenderer::CreateDefaultBrush()
{
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Black]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::White]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Yellow]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Red]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Blue]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Green]);
	this->mD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Gray]);
}
/*****************************************************
## AddTextFormat ##
@@ wstring font : 폰트명
@@ float defaultSize : 폰트 사이즈 = 1.f
*******************************************************/
void D2DRenderer::AddTextFormat(const wstring& font, const float& defaultSize)
{
	HRESULT hr;
	IDWriteTextFormat* format = NULL;

	hr = this->mDWFactory->CreateTextFormat(
		font.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		defaultSize,
		L"ko",
		&format
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif

	this->mFontList.insert(make_pair(font, format));
}


