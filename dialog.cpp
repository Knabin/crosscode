#include "stdafx.h"
#include "dialog.h"
#include "dialogText.h"
#include "portrait.h"

dialog::dialog(string fileName)
	: _textIndex(0)
{
	IMAGEMANAGER->addImage("lea", L"images/portrait/lea.png");
	IMAGEMANAGER->addImage("pro", L"images/portrait/pro.png");
}

dialog::~dialog()
{
	lea->setIsAlive(false);
	pro->setIsAlive(false);
	// 메모리 해제는 object manager에서 진행함
	for (int i = 0; i < _vObjects.size(); ++i)
	{
		_vObjects[i]->setIsAlive(false);
	}
	_vObjects.clear();
}

bool dialog::next()
{
	if (_textIndex >= _vText.size()) return true;		// 마지막 대사라면 멈추기 위해 true 반환

	int type = stoi(_vText[_textIndex]);

	//wstring m;
	//m.assign(_vText[_textIndex + 1].begin(), _vText[_textIndex + 1].end());
	dialogText* t = new dialogText(_vText[_textIndex + 1], type);
	t->init();
	_vObjects.push_back(t);
	OBJECTMANAGER->addObject(objectType::UI, t);

	int prevIndex = (_textIndex == 0) ? -1 : _textIndex / 2 - 1;
	if (prevIndex != -1)
	{
		_vObjects[prevIndex]->setRect(RectMakePivot(_vObjects[prevIndex]->getRect().getCenter() - Vector2(0, 150),
			_vObjects[prevIndex]->getRect().getSize(), pivot::CENTER));
	}

	//// 이미 지나간 대사들 render하지 않기 위함
	for (int i = 0; i < prevIndex; ++i)
	{
		if (!_vObjects[i]->getIsActive()) continue;
		_vObjects[i]->setIsActive(false);
	}

	_textIndex += 2;

	return false;
}

void dialog::loadText(string fileName)
{
	if (fileName == "1")
	{
		_vText.push_back(L"1");
		_vText.push_back(L"레아! 첫 접속의 소감은 어때?");
		_vText.push_back(L"2");
		_vText.push_back(L"(끄덕)");
		_vText.push_back(L"1");
		_vText.push_back(L"멋진걸!");
		_vText.push_back(L"1");
		_vText.push_back(L"이미 알고 있겠지만,\nW A S D 키로 이동할 수 있어.");
		_vText.push_back(L"1");
		_vText.push_back(L"공격은 마우스 클릭을 누르면 돼!");
		_vText.push_back(L"2");
		_vText.push_back(L"...");
		_vText.push_back(L"1");
		_vText.push_back(L"처음이지만 금방 적응할 거야.");
		_vText.push_back(L"1");
		_vText.push_back(L"몬스터와 직접 부딪혀 보면서\n적응하는 편이 빠를 텐데...");
		_vText.push_back(L"1");
		_vText.push_back(L"필드는 '열쇠'를 구하지 않으면\n접근이 불가능해.");
		_vText.push_back(L"1");
		_vText.push_back(L"마을 북쪽에서 얻을 수 있으니 \n우선 그쪽으로 가 보렴.");
		_vText.push_back(L"1");
		_vText.push_back(L"맞다. 수상한 동굴에는\n절대로 들어가면 안 돼!");
		_vText.push_back(L"1");
		_vText.push_back(L"그럼 행운을 빈다!");
	}
	else if (fileName == "2")
	{

	}
	lea = new portrait(0);
	pro = new portrait(1);

	OBJECTMANAGER->addObject(objectType::UI, lea);
	OBJECTMANAGER->addObject(objectType::UI, pro);
}
