#include "stdafx.h"
#include "nomalUI.h"
#include "player.h"

HRESULT nomalUI::init()
{
	IMAGEMANAGER->addImage("nomalUI", L"images/menu/nomalUI.png");
	_player = dynamic_cast<player*>(OBJECTMANAGER->findObject(objectType::PLAYER, "player"));

	_hpRC.update(Vector2(125, 44), Vector2(158, 10), pivot::LEFTTOP);
	_expRC.update(Vector2(125, 60), Vector2(158, 5), pivot::LEFTTOP);
	_hp = 158;
	_exp = 157;

	IMAGEMANAGER->addFrameImage("levelUP", L"images/UI/levelUP.png", 5, 1);
	
	_lvAnim = new animation;
	_lvAnim->init(IMAGEMANAGER->findImage("levelUP")->getWidth(), IMAGEMANAGER->findImage("levelUP")->getHeight(), IMAGEMANAGER->findImage("levelUP")->getFrameSize().x, IMAGEMANAGER->findImage("levelUP")->getFrameSize().y);
	_lvAnim->setPlayFrame(0, 4, false ,true);
	_lvAnim->setFPS(1);

	_lvUPCount = 0;
	
	_lvUP = false;

	SOUNDMANAGER->addSound("ui lvup", "sounds/ui/level-up.ogg", false, false);

	return S_OK;
}

void nomalUI::release()
{
}

void nomalUI::update()
{
	_hp = (float)_player->getPlayerHP() / (float)_player->getPlayerMaxHP() * 158;
	_exp = (float)_player->getPlayerEXP() / (float)_player->getPlayerNextEXP() * 157;

	_hpRC.update(Vector2(125, 44), Vector2(_hp, 10), pivot::LEFTTOP);
	_expRC.update(Vector2(135, 57), Vector2(_exp, 4), pivot::LEFTTOP);



	if (_player->getPlayerEXP() >= _player->getPlayerNextEXP())
	{
		_player->setPlayerEXP(_player->getPlayerEXP() - _player->getPlayerNextEXP());
		_player->setPlayerNextEXP(_player->getPlayerNextEXP()*2);
		_player->setPlayerMaxHP(_player->getPlayerMaxHP() + 50);
		_player->setPlayerHP(_player->getPlayerHP());
		_player->setPlayerDef(_player->getPlayerDef() + 1);
		_player->setPlayerAtk(_player->getPlayerAtk() + 5);
		_player->setPlayerCri(_player->getPlayerCri() + 1);
		_player->setPlayerLEVEL(_player->getPlayerLEVEL() + 1);

		SOUNDMANAGER->play("ui lvup", 0.8f);
		_lvUP = true;
		_lvAnim->start();
		_lvUPCount = 0;
	}

	if (_lvUP)
	{
		_lvAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		_lvUPCount++;

		if(_lvUPCount > 100)
		{
			_lvUP = false;
			SOUNDMANAGER->stop("ui lvup");
		}
	}
	
}

void nomalUI::render()
{
	IMAGEMANAGER->findImage("nomalUI")->render(Vector2(15, 15));

	if ( _hp > 50)
		D2DRENDERER->SkewRectangle(_hpRC, D2D1::ColorF::LawnGreen, 0, 45);
	else 
		D2DRENDERER->SkewRectangle(_hpRC, D2D1::ColorF::Red, 0, 45);

	D2DRENDERER->DrawRotationFillRectangle(_expRC, D2D1::ColorF::MediumPurple, 0);

	wstring Num = to_wstring(_player->getPlayerHP());
	D2DRENDERER->RenderText(175, 7, Num, 30, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"∏º¿∫∞ÌµÒBold");

	for (int i = 0; i < _player->getPlayerSP(); ++i)
	{
		floatRect rc;
		rc.update(Vector2(327 + 16 * i, 18), Vector2(10, 17),pivot::LEFTTOP);
		D2DRENDERER->DrawRotationFillRectangle(rc, D2D1::ColorF::DeepSkyBlue, 0);
	}

	if (_lvUP)
	IMAGEMANAGER->findImage("levelUP")->aniRender(Vector2(CAMERA->getRelativeVector2(_player->getPosition()).x + 10, CAMERA->getRelativeVector2(_player->getPosition()).y - 80), _lvAnim, 1.f);
	
}
