#include "stdafx.h"
#include "titleScene.h"

titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	IMAGEMANAGER->addFrameImage("buttons", "images/buttons.bmp", 486, 360, 1, 5, true, RGB(255, 0, 255));

	button* btnStart = new button();
	btnStart->init("buttons", 300, 500, 0, 0, 0, 0, bind(&titleScene::cbStart, this));

	button* btnContinue = new button();
	btnContinue->init("buttons", 300, 600, 0, 1, 0, 1, bind(&titleScene::cbContinue, this));

	button* btnMaptool = new button();
	btnMaptool->init("buttons", 300, 700, 0, 2, 0, 2, bind(&titleScene::cbMaptool, this));

	button* btnOption = new button();
	btnOption->init("buttons", 300, 800, 0, 3, 0, 3, bind(&titleScene::cbOption, this));

	button* btnExit = new button();
	btnExit->init("buttons", 300, 900, 0, 4, 0, 4, bind(&titleScene::cbExit, this));

	OBJECTMANAGER->addObject(objectType::UI, btnStart);
	OBJECTMANAGER->addObject(objectType::UI, btnContinue);
	OBJECTMANAGER->addObject(objectType::UI, btnMaptool);
	OBJECTMANAGER->addObject(objectType::UI, btnOption);
	OBJECTMANAGER->addObject(objectType::UI, btnExit);

	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
}

void titleScene::render()
{
}

void titleScene::cbStart()
{
	SCENEMANAGER->loadScene("test");
}

void titleScene::cbContinue()
{
	SCENEMANAGER->loadScene("test2");
}

void titleScene::cbMaptool()
{
	SCENEMANAGER->loadScene("maptool");
}

void titleScene::cbOption()
{
	SCENEMANAGER->loadScene("boss");
}

void titleScene::cbExit()
{
	PostQuitMessage(0);
}