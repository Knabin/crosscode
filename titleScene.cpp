#include "stdafx.h"
#include "titleScene.h"
#include "iEvent.h"

titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	_loading = false;
	CAMERA->setCameraMode(CAMERASTATE::NONE);
	CAMERA->setMapSize(Vector2(WINSIZEX, WINSIZEY));

	SOUNDMANAGER->playBGM("bgm title", 0.4f);


	//로딩이미지
	//IMAGEMANAGER->addFrameImage("load", "images/loading.png", 4371, 141, 31, 1, true, RGB(255, 0, 255));
	
	_index = _time = 0;
	_c1.x = 150;
	_c1.y = 650;
	_c2.x = 0;
	_c2.y = 100;
	_gr.x = 0;
	_gr.y = 800;
	_mn.x = 0;
	_mn.y = -150;
	_rl.x = 0;
	_rl.y = 1200;
	_pl.x = 1300 + 200;
	_pl.y = 710 + 370;

	button* btnStart = new button();
	btnStart->init("buttons", 300, 500, 0, 0, 0, 0, bind(&titleScene::cbStart, this));
	btnStart->setName("start");
	btnStart->setIsActive(false);

	button* btnContinue = new button();
	btnContinue->init("buttons", 300, 600, 0, 1, 0, 1, bind(&titleScene::cbContinue, this));
	btnContinue->setName("continue");
	btnContinue->setIsActive(false);

	button* btnMaptool = new button();
	btnMaptool->init("buttons", 300, 700, 0, 2, 0, 2, bind(&titleScene::cbMaptool, this));
	btnMaptool->setName("maptool");
	btnMaptool->setIsActive(false);

	button* btnOption = new button();
	btnOption->init("buttons", 300, 800, 0, 3, 0, 3, bind(&titleScene::cbOption, this));
	btnOption->setName("option");
	btnOption->setIsActive(false);

	button* btnExit = new button();
	btnExit->init("buttons", 300, 900, 0, 4, 0, 4, bind(&titleScene::cbExit, this));
	btnExit->setName("exit");
	btnExit->setIsActive(false);

	OBJECTMANAGER->addObject(objectType::UI, btnStart);
	OBJECTMANAGER->addObject(objectType::UI, btnContinue);
	OBJECTMANAGER->addObject(objectType::UI, btnMaptool);
	OBJECTMANAGER->addObject(objectType::UI, btnOption);
	OBJECTMANAGER->addObject(objectType::UI, btnExit);

	return S_OK;
}

void titleScene::release()
{
	OBJECTMANAGER->findObject(objectType::UI, "start")->setIsAlive(false);
	OBJECTMANAGER->findObject(objectType::UI, "continue")->setIsAlive(false);
	OBJECTMANAGER->findObject(objectType::UI, "maptool")->setIsAlive(false);
	OBJECTMANAGER->findObject(objectType::UI, "option")->setIsAlive(false);
	OBJECTMANAGER->findObject(objectType::UI, "exit")->setIsAlive(false);
}

void titleScene::update()
{
	_time++;

	if (_time < 68 && _time % 2 == 0)
	{
		_mn.y -= 3;
		_c2.y -= 3;
		_c1.y -= 5;
		
		_gr.y -= 8;
		_rl.y -= 10;
		_pl.y -= 11;
	}

	if (_time % 5 == 0)
	{
		_index++;
		if (_index > 5)
			_index = 0;
	}

	if (_time == 68 )
	{
		OBJECTMANAGER->findObject(objectType::UI, "start")->setIsActive(true);
		OBJECTMANAGER->findObject(objectType::UI, "continue")->setIsActive(true);
		OBJECTMANAGER->findObject(objectType::UI, "maptool")->setIsActive(true);
		OBJECTMANAGER->findObject(objectType::UI, "option")->setIsActive(true);
		OBJECTMANAGER->findObject(objectType::UI, "exit")->setIsActive(true);
	}

}

void titleScene::render()
{
	IMAGEMANAGER->findImage("sky")->render(Vector2(0,0));
	IMAGEMANAGER->findImage("planet")->render(Vector2(_mn.x, _mn.y));
	IMAGEMANAGER->findImage("clouds1")->render(Vector2(_c1.x,_c1.y));
	IMAGEMANAGER->findImage("clouds2")->render(Vector2(_c2.x,_c2.y));
	IMAGEMANAGER->findImage("ground")->render(Vector2(_gr.x,_gr.y));
	IMAGEMANAGER->findImage("logo")->render(Vector2(400, _rl.y - 1000));
	IMAGEMANAGER->findImage("railings")->render(Vector2(_rl.x,_rl.y));

	IMAGEMANAGER->findImage("leaTitle")->frameRender(Vector2(_pl.x, _pl.y), _index, 0);
}

void titleScene::cbStart()
{
	iMoveScene* e = new iMoveScene(L"town", Vector2(36 * SIZE, 47 * SIZE));
	EVENTMANAGER->addEvent(e);
	SOUNDMANAGER->play("button ok");
}

void titleScene::cbContinue()
{
	OBJECTMANAGER->findObject(objectType::UI, "start")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "continue")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "maptool")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "option")->setIsActive(false);
	OBJECTMANAGER->findObject(objectType::UI, "exit")->setIsActive(false);

	OBJECTMANAGER->findObject(objectType::UI, "loadUI")->setIsActive(true);
	SOUNDMANAGER->play("button ok");
}

void titleScene::cbMaptool()
{
	SCENEMANAGER->loadScene(L"maptool");
	SOUNDMANAGER->stop("bgm title");
	SOUNDMANAGER->play("button ok");
}

void titleScene::cbOption()
{
}

void titleScene::cbExit()
{
	SOUNDMANAGER->play("button ok");
	PostQuitMessage(0);
}