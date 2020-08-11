#include "stdafx.h"
#include "scene.h"
#include <commdlg.h>
#include "hedgehag.h"

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

void scene::getDataFromFile(string fileName)
{
	getTilesFromFile(fileName);
	getEnemiesFromFile(fileName);

	_as = new aStar;
	_as->init();
	_as->setTiles();
}

void scene::getTilesFromFile(string fileName)
{
	// 파일로부터 타일 불러오는 함수
	HANDLE file;
	DWORD read;

	char str[100 + MAXTILEX * MAXTILEY * 18];
	char* context = NULL;

	string strfileName = "map/" + fileName;

	file = CreateFile(TEXT(strfileName.c_str()), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	ReadFile(file, str, strlen(str), &read, NULL);

	char* tok = strtok_s(str, "\n", &context);
	sscanf_s(tok, "x: %d, y: %d", &_maxX, &_maxY);
	tok = strtok_s(NULL, "\n", &context);

	_vTiles.clear();

	for (int i = 0; i <= _maxY; ++i)
	{
		vTileOneLine v;
		for (int j = 0; j <= _maxX; ++j)
		{
			if (tok != NULL)
			{
				int tx = -1, ty = -1, ox = -1, oy = -1, pn = 0, oi = 0;
				sscanf_s(tok, "%d,%d,%d,%d,%d,%d", &tx, &ty, &ox, &oy, &pn, &oi);
				tile* t = new tile();
				t->setTiles(tx, ty, ox, oy, pn, oi);
				t->setTileRc(j * SIZE, i * SIZE);
				v.push_back(t);
				tok = strtok_s(NULL, "\n", &context);
			}
		}
		_vTiles.push_back(v);
	}

	CloseHandle(file);
}

void scene::getEnemiesFromFile(string fileName)
{
	HANDLE file;
	DWORD read;
	
	char str[1000];
	char* context = NULL;

	string strfileName = "enemy/" + fileName;

	file = CreateFile(TEXT(strfileName.c_str()), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	ReadFile(file, str, strlen(str), &read, NULL);

	int maxNum = 0;

	char* tok = strtok_s(str, "\n", &context);
	sscanf_s(tok, "enemy number: %d", &maxNum);
	tok = strtok_s(NULL, "\n", &context);

	for (int i = 0; i < maxNum; ++i)
	{
		int tx = -1, ty = -1, fx = -1, fy = -1, et = 0;
		sscanf_s(tok, "%d,%d,%d,%d,%d", &tx, &ty, &fx, &fy, &et);

		switch (et)
		{
		case 0:
			gameObject* hed = new hedgehag();
			hed->init();
			hed->setPosition(_vTiles[ty][tx]->getRect().getCenter());
			OBJECTMANAGER->addObject(objectType::Monster, hed);
			break;
		}
		tok = strtok_s(NULL, "\n", &context);
	}

	CloseHandle(file);
}
