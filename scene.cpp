#include "stdafx.h"
#include "scene.h"
#include <commdlg.h>
#include "hedgehag.h"
#include "meerkat.h"
#include "buffalo.h"
#include "vendor.h"
#include "door.h"
#include "mapObject.h"
#include "puzzleTabButton.h"
#include "puzzleComboButton.h"
#include "puzzleDestruct.h"
#include "puzzleBlueWall.h"
#include "puzzleOrangeWall.h"
#include "foothold.h"
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

	if (startX <= 0) startX = 0;
	if (startY <= 0) startY = 0;
	if (endX >= _maxX) endX = _maxX;
	if (endY >= _maxY) endY = _maxY;

	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{
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
}

void scene::getTilesFromFile(string fileName)
{
	// 파일로부터 타일 불러오는 함수
	HANDLE file;
	DWORD read;

	char* context = NULL;

	string strfileName = "map/" + fileName;

	file = CreateFile(TEXT(strfileName.c_str()), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	ReadFile(file, &_maxX, sizeof(int), &read, NULL);
	ReadFile(file, &_maxY, sizeof(int), &read, NULL);

	_vTiles.clear();

	for (int i = 0; i <= _maxY; ++i)
	{
		vTileOneLine v;
		for (int j = 0; j <= _maxX; ++j)
		{
			tile* t = new tile();

			int terX;
			int terY;
			int objX;
			int objY;
			int terN;
			int objN;
			int order;

			ReadFile(file, &terX, sizeof(int), &read, NULL);
			ReadFile(file, &terY, sizeof(int), &read, NULL);
			ReadFile(file, &objX, sizeof(int), &read, NULL);
			ReadFile(file, &objY, sizeof(int), &read, NULL);
			ReadFile(file, &terN, sizeof(int), &read, NULL);
			ReadFile(file, &objN, sizeof(int), &read, NULL);
			ReadFile(file, &order, sizeof(int), &read, NULL);

			t->setName("tile");
			t->setTiles(terX, terY, objX, objY, terN, objN, order);
			t->setTileRc(j * SIZE, i * SIZE);
			v.push_back(t);

			if (objX != -1 && objY != -1 && objN == 3)
			{
				int type = objX / 3;
				if (objY == 0)
				{
					switch (type)
					{
					case 0:
					{
						vendor* ven = new vendor();
						ven->setType(objX % 3);
						ven->setPosition(v[j]->getRect().getCenter());
						ven->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(ven));
					}
					break;
					case 1:
					{
						door* doo = new door();
						doo->setType(objX % 3);
						doo->setPosition(Vector2(v[j]->getRect().left, v[j]->getRect().top + SIZE * 0.5f));
						doo->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(doo));
					}
					break;
					}
				}
				else if (objY == 1)
				{
					switch (type)
					{
					case 0:
					{
						mapObject* tree = new mapObject(0, objX % 3);
						tree->setPosition(Vector2{ v[j]->getRect().getCenter().x, v[j]->getRect().top - SIZE * 2 });
						tree->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(tree));
					}
					break;
					case 1:
					{
						mapObject* grass = new mapObject(1, objX % 3);
						grass->setPosition(Vector2{ v[j]->getRect().getCenter().x, v[j]->getRect().top });
						grass->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(grass));
					}
					break;
					}
				}
				else if (objY == 2)
				{
					{
						puzzleTabButton* puzzle = new puzzleTabButton();
						puzzle->setPosition(Vector2{ v[j]->getRect().getCenter().x, v[j]->getRect().top });
						puzzle->init();
						puzzle->setFrameY(objX);
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(puzzle));
					}
				}
				else if (objY == 3)
				{
					{
						puzzleComboButton* puzzle = new puzzleComboButton();
						puzzle->setPosition(Vector2{ v[j]->getRect().getCenter().x, v[j]->getRect().top });
						puzzle->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(puzzle));
					}
				}
				else if (objY == 4)
				{
					{
						puzzleDestruct* puzzle = new puzzleDestruct();
						puzzle->setPosition(Vector2{ v[j]->getRect().getCenter().x - SIZE * 0.5f, v[j]->getRect().getCenter().y });
						puzzle->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(puzzle));
					}
				}
				else if (objY == 5)
				{
					switch (objX)
					{
					case 0:	// 꺾인 네모
					{
						puzzleBlueWall* wall = new puzzleBlueWall(objX);
						wall->setPosition(Vector2{ v[j]->getRect().getCenter().x, v[j]->getRect().getCenter().y });
						wall->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(wall));
					}
					break;
					case 1:	// 긴 네모
					{
						puzzleBlueWall* wall = new puzzleBlueWall(objX);
						wall->setPosition(Vector2{ v[j]->getRect().getCenter().x, v[j]->getRect().getCenter().y });
						wall->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(wall));
					}
					break;
					case 2: // 짧음
					case 3: // 긺
					{
						puzzleOrangeWall* wall = new puzzleOrangeWall(objX % 2);
						wall->setPosition(Vector2{ v[j]->getRect().getCenter() });
						wall->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(wall));
					}
					break;
					}
				}
				else if (objY == 6)
				{
					{
						mapObject* roof = new mapObject(2, 0);
						roof->setPosition(Vector2{ v[j]->getRect().getCenter() });
						roof->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(roof));
					}
				}
				else if (objY == 7)
				{
					{
						foothold* foot = new foothold();
						foot->setPosition(Vector2{ v[j]->getRect().getCenter() });
						foot->init();
						OBJECTMANAGER->addObject(objectType::MAPOBJECT, dynamic_cast<gameObject*>(foot));
					}
				}
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
	
	char* context = NULL;

	string strfileName = "enemy/" + fileName;

	file = CreateFile(TEXT(strfileName.c_str()), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	int maxNum = 0;

	ReadFile(file, &maxNum, sizeof(int), &read, NULL);

	for (int i = 0; i < maxNum; ++i)
	{
		int tileX;
		int tileY;
		int frameX;
		int frameY;
		int enemyType;

		ReadFile(file, &tileX, sizeof(int), &read, NULL);
		ReadFile(file, &tileY, sizeof(int), &read, NULL);
		ReadFile(file, &frameX, sizeof(int), &read, NULL);
		ReadFile(file, &frameY, sizeof(int), &read, NULL);
		ReadFile(file, &enemyType, sizeof(int), &read, NULL);

		switch (enemyType)
		{
		case 0:
		{
			gameObject* hed = new hedgehag();
			hed->init();
			hed->setPosition(_vTiles[tileY][tileX]->getRect().getCenter());
			OBJECTMANAGER->addObject(objectType::ENEMY, hed);
		}
		break;
		case 1:
		{
			gameObject* hed = new meerkat();
			hed->init();
			hed->setPosition(_vTiles[tileY][tileX]->getRect().getCenter());
			OBJECTMANAGER->addObject(objectType::ENEMY, hed);
		}
		break;
		case 2:
		{
			gameObject* hed = new buffalo();
			hed->init();
			hed->setPosition(_vTiles[tileY][tileX]->getRect().getCenter());
			OBJECTMANAGER->addObject(objectType::ENEMY, hed);
		}
		break;
		}
	}

	CloseHandle(file);
}