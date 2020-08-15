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
	this->AddTextFormat(L"�������");
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
	//private: // ���к��ϰ� ��������� �����ڸ� private��
	//	friend class Factory;
	//	Item() {}
	//	~Item() {}
	//};

	//class Factory // ���丮 ������ ����
	//{
	//public:
	//	Item* CreateItem() {
	//		return new Item();
	//	}
	//};



	// 1) D2D ���丮 ����
	// �̱۾�����Ÿ������ 
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
#ifdef _DEBUG
	assert(SUCCEEDED(hr)); // E_FAIL�� ������ �����.
#endif
	// 2) DWriteFactory ����
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
	// ���� Ÿ���̶� ������� ������ �ϴ� Ŭ�������� ���� �������� ���� ��ƿ���� �͵��� ����ִ� Ŭ�����̴�.
	// �׷��� ȭ�鿡 ���� �������� ��û�Ϸ��� ����Ÿ���� ���ؼ��� ���� �ϴ�.

	//����ü�����κ��� ����� ���� �޾ƿ´�. 
	HRESULT hr;
	// 1) ������ �ڵ��� ���ؼ� ȭ�� Rect�� �޾ƿ´�.(GetClientRect())
	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);

	// �������� Factory�� ���ؼ� ���� ����̽��� DPI�� �޾� ������ � ������������ MS���� �ش� �Լ��� ������� ���ϰ� ������, ��ü API�Լ��� �ҷ�����
	// mD2DFactory->GetDesktopDpi(&dpiX, &dpiY)

	// 2) ����̽��� DPI������ �޾ƿ´�. (WinAPI �Լ�)
	FLOAT dpiX = GetDeviceCaps(_hdc, LOGPIXELSX);
	FLOAT dpiY = GetDeviceCaps(_hdc, LOGPIXELSY);

	// 3) ����Ÿ���� �����ϱ� ���� �Ӽ� ������ �ʱ�ȭ.
	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	// 4) ����Ÿ���� ������ �ʱ�ȭ(ȭ�� ũ���) 
	D2D1_SIZE_U renderTargetSize = D2D1::SizeU(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	// 5) ����Ÿ���� ����
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
@@ wstring font : ��Ʈ��
@@ float defaultSize : ��Ʈ ������ = 1.f
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


