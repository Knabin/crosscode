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
		// ============================ 씬 추가 ==============================
		SCENEMANAGER->addScene(L"title", new titleScene());			// 타이틀 씬
		SCENEMANAGER->addScene(L"maptool", new mapToolScene());		// 맵툴 씬
		SCENEMANAGER->addScene(L"test", new testScene());			// 테스트용(새 게임 버튼)
		SCENEMANAGER->addScene(L"test2", new testScene2());			// 테스트용(게임 불러오기 버튼)
		SCENEMANAGER->addScene(L"boss", new bossTestScene());		// 테스트용(옵션 버튼)
		SCENEMANAGER->addScene(L"puzzle", new puzzleScene());
		SCENEMANAGER->addScene(L"mountain", new mountainScene());
		SCENEMANAGER->addScene(L"town", new townScene());
		// ==================================================================

		// ============================ 이미지 추가 ==============================
		// 커서 이미지
		IMAGEMANAGER->addImage("cursor normal", L"cursor/cursor-3.png");
		IMAGEMANAGER->addImage("cursor melee", L"cursor/cursor-melee-3.png");
		IMAGEMANAGER->addImage("cursor throw", L"cursor/cursor-throw-3.png");
		IMAGEMANAGER->addImage("cursor charge", L"cursor/cursor-charge-3.png");

		// 맵툴 배경 이미지
		IMAGEMANAGER->addImage("map bg", L"images/maptool/map_bg.png");
		IMAGEMANAGER->addImage("map bg2", L"images/maptool/map_back.png");

		// 맵툴 버튼 이미지
		IMAGEMANAGER->addFrameImage("saveload", L"images/maptool/button_saveload.png", 2, 2);
		IMAGEMANAGER->addFrameImage("editmode", L"images/maptool/button_menu.png", 2, 4);
		IMAGEMANAGER->addFrameImage("numbutton", L"images/maptool/button_num.png", 2, 3);
		IMAGEMANAGER->addFrameImage("numobj", L"images/maptool/button_numobj.png", 2, 4);
		IMAGEMANAGER->addFrameImage("backtotitle", L"images/maptool/button_backtotitle.png", 1, 1);

		// 맵툴 ui 전체 이미지
		IMAGEMANAGER->addImage("edit ui", L"images/maptool/ui_edit.png");

		// 맵툴 샘플 이미지


		// 맵툴 미리 보기용 이미지
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

		// 타이틀 씬
		IMAGEMANAGER->addFrameImage("buttons", L"images/title/button_title.png", 1, 5);
		IMAGEMANAGER->addFrameImage("leaTitle", L"images/title/lea.png", 6, 1);

		IMAGEMANAGER->addImage("clouds1", L"images/title/clouds-1.png");
		IMAGEMANAGER->addImage("clouds2", L"images/title/clouds-2.png");
		IMAGEMANAGER->addImage("ground", L"images/title/ground.png");
		IMAGEMANAGER->addImage("planet", L"images/title/planet.png");
		IMAGEMANAGER->addImage("railings", L"images/title/railings.png");
		IMAGEMANAGER->addImage("sky", L"images/title/sky.png");
		IMAGEMANAGER->addImage("logo", L"images/title/logo.png");

		IMAGEMANAGER->addFrameImage("townblock", L"images/object/townblock.png", 2, 1);


		// 사운드
		SOUNDMANAGER->addSound("bgm title", "sounds/bgm/muTitle.ogg", true, true);
		SOUNDMANAGER->addSound("bgm puzzle", "sounds/bgm/puzzle-bgm.ogg", true, true);
		SOUNDMANAGER->addSound("bgm town", "sounds/bgm/muAutumnsrise.ogg", true, true);
		SOUNDMANAGER->addSound("bgm boss", "sounds/bgm/muVermillion.ogg", true, true);

		SOUNDMANAGER->addSound("buffalo-attack", "sounds/enemy/buffalo-attack.ogg", false, false);
		SOUNDMANAGER->addSound("buffalo-run", "sounds/enemy/buffalo-run.ogg", false, false);
		SOUNDMANAGER->addSound("buffalo-gasp", "sounds/enemy/buffalo-gasp.ogg", false, false);
		SOUNDMANAGER->addSound("hit", "sounds/enemy/hit.ogg", false, false);

		SOUNDMANAGER->addSound("pS step", "sounds/player/step-1.ogg", false, true);	//발자국소리
		SOUNDMANAGER->addSound("pS jump", "sounds/player/jump.ogg", false, false);	//점프소리
		SOUNDMANAGER->addSound("pS lattack", "sounds/player/throw-ball-1.ogg", false, false);	//원거리발사소리
		SOUNDMANAGER->addSound("pS mattack", "sounds/player/close-combat-sweep-1.ogg", false, false);	//근거리공격소리
		SOUNDMANAGER->addSound("pS mattackf", "sounds/player/close-combat-sweep-massive.ogg", false, false);	//근거리막타공격소리
		SOUNDMANAGER->addSound("pS dodge", "sounds/player/dash-3.ogg", false, false);	//회피
		SOUNDMANAGER->addSound("dodge", "sound/player/hit-block.ogg", false, false);
		SOUNDMANAGER->addSound("dead", "sound/player/teleport-out-1s.ogg", false, false);
		SOUNDMANAGER->addSound("dead2", "sound/player/teleport-1s.ogg", false, false);
		
		SOUNDMANAGER->addSound("counter", "sounds/object/counter.ogg", false, false);
		SOUNDMANAGER->addSound("barrier", "sounds/object/barrier-down.ogg", false, false);
		SOUNDMANAGER->addSound("item drop", "sounds/object/drop-normal-bronze", false, false);
		SOUNDMANAGER->addSound("puzzle", "sounds/object/puzzle-solved.ogg", false, false);

		SOUNDMANAGER->addSound("button hover", "sounds/ui/menu-hover.ogg", false, false);
		SOUNDMANAGER->addSound("button ok", "sounds/ui/menu-submit.ogg", false, false);
		SOUNDMANAGER->addSound("button cancel", "sounds/ui/menu-cancel.ogg", false, false);
		SOUNDMANAGER->addSound("dialog", "sounds/ui/dialog-beep-2.ogg", false, false);

		_isInit = true;
	}

	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->loadScene(L"title");
	}
}

void initLoadingScene::render()
{
	_progressBarBack->render(Vector2(_progressRc.left, _progressRc.top));
	D2DRENDERER->DrawRotationFillRectangle(_progressBar, D2D1::ColorF::SkyBlue, 0);
}