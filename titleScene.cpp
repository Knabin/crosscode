#include "stdafx.h"
#include "titleScene.h"

titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	CAMERA->setCameraMode(CAMERASTATE::NONE);
	CAMERA->setMapSize(WINSIZEX, WINSIZEY);

	IMAGEMANAGER->addFrameImage("buttons", "images/title/button_title.bmp", 486, 360, 1, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("leaTitle", "images/title/lea.bmp", 3312, 735, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("title", "images/title/title.bmp", 1920, 1080, false, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("clouds1", "images/title/clouds-1.bmp", 1771, 439, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("clouds2", "images/title/clouds-2.bmp", 1920, 936, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ground", "images/title/ground.bmp", 1920, 548, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("planet", "images/title/planet.bmp", 608, 1064, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("railings", "images/title/railings.bmp", 1920, 213, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sky", "images/title/sky.bmp", 1920, 1335, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("logo", "images/title/logo.bmp", 1056, 768, true, RGB(255, 0, 255));

	//로딩이미지
	//IMAGEMANAGER->addFrameImage("load", "images/loading.bmp", 4371, 141, 31, 1, true, RGB(255, 0, 255));
	
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
	_pl.x = 1300;
	_pl.y = 710;

	return S_OK;
}

void titleScene::release()
{
	
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
	}

}

void titleScene::render()
{
	//IMAGEMANAGER->findImage("title")->render(getMemDC());
	IMAGEMANAGER->findImage("sky")->render(getMemDC(),0,0);
	IMAGEMANAGER->findImage("planet")->render(getMemDC(), _mn.x, _mn.y);
	IMAGEMANAGER->findImage("clouds1")->render(getMemDC(),_c1.x,_c1.y);
	IMAGEMANAGER->findImage("clouds2")->render(getMemDC(),_c2.x,_c2.y);
	IMAGEMANAGER->findImage("ground")->render(getMemDC(),_gr.x,_gr.y);
	IMAGEMANAGER->findImage("logo")->render(getMemDC(), 400, _rl.y - 1000);
	IMAGEMANAGER->findImage("railings"	)->render(getMemDC(),_rl.x,_rl.y);

	IMAGEMANAGER->findImage("leaTitle")->frameRender(getMemDC(), _pl.x, _pl.y, _index, 0);
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