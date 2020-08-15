#include "stdafx.h"
#include "imageManager.h"
#include "image.h"

#include <io.h>

imageManager::imageManager()
	:mWicFactory(nullptr)
{
	//WIC ���丮 ����
	//Windows Imaging Component
	//Direct2D�� �̹����� �ε��ϴ� ����� ����. 
	//��� Direct2D�� WIC��� ���̺귯���� �̹����κ��� �̹��� �����͸� ���� �� �ִ�.
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mWicFactory));
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
}

/*********************************************************************
## imageManager ##
**********************************************************************/
imageManager::~imageManager()
{
	this->DeleteAll();
	NEW_SAFE_RELEASE(mWicFactory);
}
/*********************************************************************
## addImage ##
**********************************************************************/
image * imageManager::addImage(const string& key, const wstring& file)
{
	image* img = this->findImage(key);
	if (img)
		return img;

	ID2D1Bitmap* bitmap = this->CreateD2DBitmapFromFile(file);
	if (bitmap)
	{
		image::TagLoadedImageInfo loadInfo(key, file);
		img = new image(bitmap, loadInfo);
		mImageList.insert(make_pair(key, img));
		return img;
	}
	else
		assert(SUCCEEDED(E_FAIL));

	return nullptr;
}
/*********************************************************************
## addFrameImage ##
**********************************************************************/
image * imageManager::addFrameImage(const string& key, const wstring& file, const int maxFrameX, const int maxFrameY)
{
	image* img = this->findImage(key);
	if (img)
		return img;

	ID2D1Bitmap* bitmap = CreateD2DBitmapFromFile(file);
	if (bitmap)
	{
		image::TagLoadedImageInfo loadInfo(key, file);
		img = new image(bitmap, loadInfo, maxFrameX, maxFrameY);
		this->mImageList.insert(make_pair(key, img));
		return img;
	}

	return nullptr;
}
/*********************************************************************
## findImage ##
**********************************************************************/
image * imageManager::findImage(const string& key)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end())
		return iter->second;
	return nullptr;
}
/*********************************************************************
## CreateD2DBitmapFromFile ##
@@ wstring file : ���� ���
**********************************************************************/
ID2D1Bitmap * imageManager::CreateD2DBitmapFromFile(const wstring & file)
{
	//���ڴ� ����
	IWICBitmapDecoder* ipDecoder = nullptr;
	HRESULT hr;
	hr = mWicFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &ipDecoder);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//���ڴ����� �����Ӿ���
	IWICBitmapFrameDecode* ipFrame = nullptr;
	hr = ipDecoder->GetFrame(0, &ipFrame);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//�������� ������� ���� ������ ����
	IWICFormatConverter* convertedSrcBmp = nullptr;
	hr = mWicFactory->CreateFormatConverter(&convertedSrcBmp);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//������ �ʱ�ȭ
	hr = convertedSrcBmp->Initialize
	(
		ipFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//����Ʈ�� �����͸� ������� ���� Direct2D�� ��Ʈ���� ����
	ID2D1Bitmap* ipResult = nullptr;
	hr = D2DRENDERER->GetRenderTarget()->CreateBitmapFromWicBitmap
	(
		convertedSrcBmp,
		nullptr,
		&ipResult
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif

	NEW_SAFE_RELEASE(convertedSrcBmp);
	NEW_SAFE_RELEASE(ipFrame);
	NEW_SAFE_RELEASE(ipDecoder);

	return ipResult;
}
/*********************************************************************
## DeleteAll ##
**********************************************************************/
void imageManager::DeleteAll()
{
	ImageIter iter = mImageList.begin();
	for (; iter != mImageList.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	mImageList.clear();
}

