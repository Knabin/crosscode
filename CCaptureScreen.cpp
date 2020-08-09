#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include "CCaptureScreen.h"


void CCaptureScreen::cc(int startX, int startY, int endX, int endY)
{

	//HDC h_screen_dc = ::GetDC(NULL);
	HDC h_screen_dc = getMemDC();
	// ���� ��ũ���� �ػ󵵸� ��´�.
	/*int width = ::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = ::GetDeviceCaps(h_screen_dc, VERTRES);*/

	int width = endX-startX;
	int height = endY-startY;


	// DIB�� ������ �����Ѵ�.
	BITMAPINFO dib_define;
	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	dib_define.bmiHeader.biWidth = width;
	dib_define.bmiHeader.biHeight = height;
	dib_define.bmiHeader.biPlanes = 1;
	dib_define.bmiHeader.biBitCount = 24;
	dib_define.bmiHeader.biCompression = BI_RGB;
	dib_define.bmiHeader.biSizeImage = (((width * 24 + 31) & ~31) >> 3) * height;
	dib_define.bmiHeader.biXPelsPerMeter = 0;
	dib_define.bmiHeader.biYPelsPerMeter = 0;
	dib_define.bmiHeader.biClrImportant = 0;
	dib_define.bmiHeader.biClrUsed = 0;

	// DIB�� ���� �̹��� ��Ʈ ������ ������ ������ ����
	BYTE *p_image_data = NULL;

	// dib_define�� ���ǵ� �������� DIB�� �����Ѵ�.
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);

	// �̹����� �����ϱ� ���ؼ� ���� DC�� �����Ѵ�. ���� DC������ ���������� ��Ʈ�ʿ� �����Ͽ�
	// �̹��� ������ ���� �� ���� �����̴�.
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);

	// ���� DC�� �̹����� ������ ��Ʈ���� �����Ѵ�.
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

	// ���� ��ũ�� ȭ���� ĸ���Ѵ�.
	::BitBlt(h_memory_dc, -startX, -startY, startX+ endX, startY+ endY, h_screen_dc, 0, 0, SRCCOPY);

	// ������ ��Ʈ������ �����Ѵ�.
	::SelectObject(h_memory_dc, h_old_bitmap);

	// ���� DC�� �����Ѵ�.
	DeleteDC(h_memory_dc);

	// DIB ������ ��� ������ �����Ѵ�.
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// DIB ������ �����Ѵ�.
	FILE *p_file = fopen("image.bmp", "wb");
	if (p_file != NULL) {
		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
		fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
		fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
		fclose(p_file);
	}

	// ����ߴ� ��Ʈ�ʰ� DC �� �����Ѵ�.
	if (NULL != h_bitmap) DeleteObject(h_bitmap);
	if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);

}
