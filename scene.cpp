#include "stdafx.h"
#include "scene.h"
#include <commdlg.h>

scene::~scene()
{
}

HRESULT scene::init()
{
	return S_OK;
}

void scene::release()
{
}

void scene::update()
{
}

void scene::render()
{
}

void scene::getTilesFromFile(string fileName)
{
	HANDLE file;
	DWORD read;

	char str[100 + MAXNUMX * MAXNUMY * 14];
	char* context = NULL;

	LPCSTR t = fileName.c_str();

	file = CreateFile(TEXT(fileName.c_str()), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	ReadFile(file, str, strlen(str), &read, NULL);

	char* tok = strtok_s(str, "\n", &context);
	sscanf_s(tok, "x: %d, y: %d", &_maxX, &_maxY);
	tok = strtok_s(NULL, "\n", &context);

	for (int i = 0; i <= _maxY; ++i)
	{
		_vTiles.push_back(vector<tile *>());
		for (int j = 0; j <= _maxX; ++j)
		{
			if (tok != NULL)
			{
				int tx = -1, ty = -1, ox = -1, oy = -1, oi = 0;
				sscanf_s(tok, "%d,%d,%d,%d,%d", &tx, &ty, &ox, &oy, &oi);
				tile* t = new tile();
				t->setTiles(tx, ty, ox, oy, oi);
				t->getRect().set(0, 0, SIZE, SIZE);
				t->getRect().setLeftTop(j * SIZE, i * SIZE);
				_vTiles[i].push_back(t);
				tok = strtok_s(NULL, "\n", &context);
			}
		}
	}

	CloseHandle(file);

	//OPENFILENAME ofn = { 0 };
	//char filePathSize[1028] = "";
	//char str[100 + MAXNUMX * MAXNUMY * 14];
	//char* context = NULL;

	//ZeroMemory(&ofn, sizeof(OPENFILENAME));

	//ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner = NULL;
	//ofn.lpstrFile = filePathSize;
	//ofn.nMaxFile = sizeof(filePathSize);
	//ofn.nFilterIndex = true;
	//ofn.lpstrFileTitle = NULL;
	//ofn.nMaxFileTitle = NULL;
	//ofn.lpstrInitialDir = NULL;
	//ofn.lpstrFilter = ("≈∏¿œ∏  ∆ƒ¿œ(*.map)");
	//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//if (GetOpenFileName(&ofn) == FALSE) return;

	//HANDLE file;
	//DWORD read;

	//file = CreateFile(filePathSize, GENERIC_READ, NULL, NULL,
	//	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//ReadFile(file, str, strlen(str), &read, NULL);

	//char* tok = strtok_s(str, "\n", &context);
	//sscanf_s(tok, "x: %d, y: %d", &_maxX, &_maxY);
	//tok = strtok_s(NULL, "\n", &context);

	//for (int i = 0; i <= _maxY; ++i)
	//{
	//	_vTiles.push_back(vector<tile *>());
	//	for (int j = 0; j <= _maxX; ++j)
	//	{
	//		if (tok != NULL)
	//		{
	//			int tx = -1, ty = -1, ox = -1, oy = -1, oi = 0;
	//			sscanf_s(tok, "%d,%d,%d,%d,%d", &tx, &ty, &ox, &oy, &oi);
	//			tile* t = new tile();
	//			t->setTiles(tx, ty, ox, oy, oi);
	//			t->getRect().set(0, 0, SIZE, SIZE);
	//			t->getRect().setLeftTop(j * SIZE, i * SIZE);
	//			_vTiles[i].push_back(t);
	//			tok = strtok_s(NULL, "\n", &context);
	//		}
	//	}
	//}

	//CloseHandle(file);
}
