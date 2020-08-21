#include "stdafx.h"
#include "initLoadingScene.h"
#include "titleScene.h"
#include "mapToolScene.h"
#include "testScene.h"
#include "testScene2.h"
#include "bossTestScene.h"
#include "puzzleScene.h"
#include "mountainScene.h"
#include "townScene.h"

HRESULT initLoadingScene::init()
{
	_progressBarBack = IMAGEMANAGER->addImage("progress back", L"images/UI/progress_back.png");
	_progressRc.update(Vector2(WINSIZEX * 0.5f, WINSIZEY * 0.5f), _progressBarBack->getSize(), pivot::CENTER);
	_progressBar.update(Vector2(_progressRc.getRect().left + 7, _progressRc.getRect().top + 7),
		Vector2(0, 14), pivot::LEFTTOP);

	_width = 0;
	
	_currentCount = 0;
	_isInit = false;

	return S_OK;
}

void initLoadingScene::release()
{
}

void initLoadingScene::update()
{
	_currentCount++;
	_width = (_progressBarBack->getWidth() - 14) * ((float)_currentCount / LOADINGMAX);
	_progressBar.update(Vector2(_progressRc.getRect().left + 7, _progressRc.getRect().top + 7),
		Vector2(_width, 14.f), pivot::LEFTTOP);

	if (!_isInit)
	{
		// ============================ �� �߰� ==============================
		SCENEMANAGER->addScene("title", new titleScene());			// Ÿ��Ʋ ��
		SCENEMANAGER->addScene("maptool", new mapToolScene());		// ���� ��
		SCENEMANAGER->addScene("test", new testScene());			// �׽�Ʈ��(�� ���� ��ư)
		SCENEMANAGER->addScene("test2", new testScene2());			// �׽�Ʈ��(���� �ҷ����� ��ư)
		SCENEMANAGER->addScene("boss", new bossTestScene());		// �׽�Ʈ��(�ɼ� ��ư)
		SCENEMANAGER->addScene("puzzle", new puzzleScene());
		SCENEMANAGER->addScene("mountain", new mountainScene());
		SCENEMANAGER->addScene("town", new townScene());
		// ==================================================================

		// ============================ �̹��� �߰� ==============================
		// Ŀ�� �̹���
		IMAGEMANAGER->addImage("cursor normal", L"cursor/cursor-3.png");
		IMAGEMANAGER->addImage("cursor melee", L"cursor/cursor-melee-3.png");
		IMAGEMANAGER->addImage("cursor throw", L"cursor/cursor-throw-3.png");

		// ���� ��� �̹���
		IMAGEMANAGER->addImage("map bg", L"images/maptool/map_bg.png");
		IMAGEMANAGER->addImage("map bg2", L"images/maptool/map_back.png");

		// ���� ��ư �̹���
		IMAGEMANAGER->addFrameImage("saveload", L"images/maptool/button_saveload.png", 2, 2);
		IMAGEMANAGER->addFrameImage("editmode", L"images/maptool/button_menu.png", 2, 4);
		IMAGEMANAGER->addFrameImage("numbutton", L"images/maptool/button_num.png", 2, 3);
		IMAGEMANAGER->addFrameImage("numobj", L"images/maptool/button_numobj.png", 2, 4);
		IMAGEMANAGER->addFrameImage("backtotitle", L"images/maptool/button_backtotitle.png", 1, 1);

		// ���� ui ��ü �̹���
		IMAGEMANAGER->addImage("edit ui", L"images/maptool/ui_edit.png");

		// ���� ���� �̹���


		// ���� �̸� ����� �̹���
		IMAGEMANAGER->addFrameImage("vendor", L"images/object/vendor.png", 3, 1);
		IMAGEMANAGER->addFrameImage("door prev", L"images/tile/doorpreview.png", 3, 1);
		IMAGEMANAGER->addFrameImage("tree", L"images/object/tree.png", 3, 1);
		IMAGEMANAGER->addFrameImage("grass", L"images/object/grass.png", 3, 1);
		IMAGEMANAGER->addFrameImage("button prev", L"images/tile/buttonpreview.png", 3, 1);
		IMAGEMANAGER->addFrameImage("button2 prev", L"images/tile/button2preview.png", 1, 1);
		IMAGEMANAGER->addFrameImage("destruct", L"images/object/destruct.png", 1, 1);
		IMAGEMANAGER->addFrameImage("wall prev", L"images/tile/wallpreview.png", 1, 1);
		IMAGEMANAGER->addFrameImage("wall2 prev", L"images/tile/wall2preview.png", 1, 1);
		IMAGEMANAGER->addFrameImage("wall3 prev", L"images/tile/wall3preview.png", 1, 1);
		IMAGEMANAGER->addFrameImage("wall4 prev", L"images/tile/wall4preview.png", 1, 1);
		IMAGEMANAGER->addFrameImage("roof", L"images/object/test.png", 1, 1);

		IMAGEMANAGER->addImage("event back", L"images/UI/eventback.png");
		IMAGEMANAGER->addImage("black", L"images/UI/black.png");

		IMAGEMANAGER->addFrameImage("townblock", L"images/object/townblock.png", 2, 1);


		_isInit = true;
	}

	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->loadScene("title");
	}
}

void initLoadingScene::render()
{
	_progressBarBack->render(Vector2(_progressRc.left, _progressRc.top));
	D2DRENDERER->DrawRotationFillRectangle(_progressBar, D2D1::ColorF::SkyBlue, 0);
}