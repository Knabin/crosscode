#include "stdafx.h"
#include "scene.h"
#include <commdlg.h>
#include "hedgehag.h"
#include "meerkat.h"
#include "buffalo.h"
#include "vendor.h"
#include "door.h"
#include "mapObject.h"
//#include "tile.h"

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
	if (_vTiles.size() <= 0) return;
	
	int startX = CAMERA->getRect().left / SIZE;
	int startY = CAMERA->getRect().top / SIZE;
	int endX = CAMERA->getRect().right / SIZE;
	int endY = CAMERA->getRect().bottom / SIZE;

	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{
			/*if (CAMERA->getRect().left >= _vTiles[i][j]->getRect().right ||
				CAMERA->getRect().right <= _vTiles[i][j]->getRect().left ||
				CAMERA->getRect().bottom <= _vTiles[i][j]->getRect().top ||
				CAMERA->getRect().top >= _vTiles[i][j]->getRect().bottom) continue;*/

			SCENEMANAGER->getTileImage(_vTiles[i][j]->getTerrainImageNum())->setSize(Vector2(48, 48) * CAMERA->getZoomAmount());
			SCENEMANAGER->getTileImage(_vTiles[i][j]->getTerrainImageNum())->frameRender(
				CAMERA->getRelativeVector2(_vTiles[i][j]->getRect().getCenter()),
				_vTiles[i][j]->getTerrainX(), _vTiles[i][j]->getTerrainY());

			if (_vTiles[i][j]->getObjectX() < 0 || _vTiles[i][j]->getObjectImageNum() == 3) continue;
			SCENEMANAGER->getObjectImage(_vTiles[i][j]->getObjectImageNum())->setSize(Vector2(48, 48) * CAMERA->getZoomAmount());
			SCENEMANAGER->getObjectImage(_vTiles[i][j]->getObjectImageNum())->frameRender(
				CAMERA->getRelativeVector2(_vTiles[i][j]->getRect().getCenter()),
				_vTiles[i][j]->getObjectX(), _vTiles[i][j]->getObjectY());
		}
	}
}

void scene::getDataFromFile(string fileName)
{
	getTilesFromFile(fileName);
	getEnemiesFromFile(fileName);
	//getObjectsFromFile(fileName);
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
				int tx = -1, ty = -1, ox = -1, oy = -1, pn = 0, on = 0, oi = 0;
				sscanf_s(tok, "%d,%d,%d,%d,%d,%d,%d", &tx, &ty, &ox, &oy, &pn, &on, &oi);
				tile* t = new tile();
				t->setTiles(tx, ty, ox, oy, pn, on, oi);
				t->setTileRc(j * SIZE, i * SIZE);
				v.push_back(t);

				if (ox != -1 && oy != -1 && on == 3)
				{
					int type = ox / 3;
					if (oy == 0)
					{
						switch (type)
						{
						case 0:
						{
							vendor* ven = new vendor();
							ven->setType(ox % 3);
							ven->setPosition(v[j]->getRect().getCenter());
							ven->init();
							OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(ven));
						}
						break;
						case 1:
						{
							door* doo = new door();
							doo->setType(ox % 3);
							doo->setPosition(Vector2(v[j]->getRect().left, v[j]->getRect().top));
							doo->init();
							OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(doo));
						}
						break;
						}
					}
					else
					{
						switch (type)
						{
						case 0:
						{
							mapObject* tree = new mapObject(0, ox % 3);
							tree->setPosition(Vector2{ v[j]->getRect().getCenter().x, v[j]->getRect().top - SIZE * 2 });
							tree->init();
							OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(tree));
						}
						break;
						case 1:
						{
							mapObject* grass = new mapObject(1, ox % 3);
							grass->setPosition(Vector2{ v[j]->getRect().getCenter().x, v[j]->getRect().top });
							grass->init();
							OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(grass));
						}
						break;
						}
					}
				}
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
		{
			gameObject* hed = new hedgehag();
			hed->init();
			hed->setPosition(_vTiles[ty][tx]->getRect().getCenter());
			OBJECTMANAGER->addObject(objectType::ENEMY, hed);
		}
		break;
		case 1:
		{
			gameObject* hed = new meerkat();
			hed->init();
			hed->setPosition(_vTiles[ty][tx]->getRect().getCenter());
			OBJECTMANAGER->addObject(objectType::ENEMY, hed);
		}
		break;
		case 2:
		{
			gameObject* hed = new buffalo();
			hed->init();
			hed->setPosition(_vTiles[ty][tx]->getRect().getCenter());
			OBJECTMANAGER->addObject(objectType::ENEMY, hed);
		}
		break;
		}
		tok = strtok_s(NULL, "\n", &context);
	}

	CloseHandle(file);
}

void scene::getObjectsFromFile(string fileName)
{
	HANDLE file;
	DWORD read;

	char str[1000];
	char* context = NULL;

	string strfileName = "object/" + fileName;

	file = CreateFile(TEXT(strfileName.c_str()), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	ReadFile(file, str, strlen(str), &read, NULL);

	int maxNum = 0;

	char* tok = strtok_s(str, "\n", &context);
	sscanf_s(tok, "object number: %d", &maxNum);
	tok = strtok_s(NULL, "\n", &context);

	for (int i = 0; i < maxNum; ++i)
	{
		int tx = -1, ty = -1, fx = -1, fy = -1, pn = 0, ot = 0;
		sscanf_s(tok, "%d,%d,%d,%d,%d,%d", &tx, &ty, &fx, &fy, &pn, &ot);

		if (fy == 0)
		{
			switch (ot)
			{
			case 0:
			{
				vendor* ven = new vendor();
				ven->setType(ot);
				ven->setPosition(_vTiles[ty][tx]->getRect().getCenter());
				ven->init();
				OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(ven));
			}
			break;
			case 1:
			{
				door* doo = new door();
				doo->setType(ot);
				doo->setPosition(Vector2{ _vTiles[ty][tx]->getRect().left, _vTiles[ty][tx]->getRect().top });
				doo->init();
				OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(doo));
			}
			break;
			}
		}
		else
		{
			switch (ot)
			{
			case 0:
			{
				mapObject* tree = new mapObject(0, fx);
				tree->setPosition(Vector2{ _vTiles[ty][tx]->getRect().getCenter().x, _vTiles[ty][tx]->getRect().getCenter().y - SIZE * 2 });
				tree->init();
				OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(tree));
			}
			break;
			case 1:
			{
				mapObject* grass = new mapObject(1, fx - 3);
				grass->setPosition(Vector2{ _vTiles[ty][tx]->getRect().getCenter().x, _vTiles[ty][tx]->getRect().top });
				grass->init();
				OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(grass));
			}
			break;
			}
		}
		tok = strtok_s(NULL, "\n", &context);
	}

	CloseHandle(file);
}
