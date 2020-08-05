#include "stdafx.h"
#include "testScene.h"

testScene::~testScene()
{
}

HRESULT testScene::init()
{
	CAMERA->changeTarget(OBJECTMANAGER->findObject(objectType::Player, "player"));
	OBJECTMANAGER->findObject(objectType::Player, "player")->setIsActive(true);

	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
}

void testScene::render()
{
}
