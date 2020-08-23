#include "stdafx.h"
#include "dialog.h"
#include "dialogText.h"
#include "portrait.h"

dialog::dialog(string fileName)
	: _textIndex(0), _fileName(fileName)
{
	IMAGEMANAGER->addImage("lea", L"images/portrait/lea.png");
	IMAGEMANAGER->addImage("pro", L"images/portrait/pro.png");
}

dialog::~dialog()
{
	lea->setIsAlive(false);
	pro->setIsAlive(false);
	_vText.clear();
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

	// 짝수라면 프로그래머
	if (type % 2 == 0)
	{
		pro->setType(type);
	}
	// 홀수라면 레아
	else
	{
		lea->setType(type);
	}

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

void dialog::loadText()
{
	int l = 1;
	int p = 0;
	if (_fileName == "1")
	{
		p = 0;
		l = 1;
		_vText.push_back(L"0");
		_vText.push_back(L"레아! 첫 접속 소감은 어때?");
		_vText.push_back(L"3");
		_vText.push_back(L"(끄덕)");
		_vText.push_back(L"6");
		_vText.push_back(L"음! 좋아. 멋진걸!");
		_vText.push_back(L"0");
		_vText.push_back(L"W A S D 키로 이동할 수 있어.\n이미 알고 있을 수도 있지만.");
		_vText.push_back(L"0");
		_vText.push_back(L"공격은 마우스 클릭을 누르면 돼!");
		_vText.push_back(L"7");
		_vText.push_back(L"...");
		_vText.push_back(L"0");
		_vText.push_back(L"처음이지만 금방 적응할 거야.");
		_vText.push_back(L"2");
		_vText.push_back(L"몬스터와 직접 부딪혀 보면서\n적응하는 편이 빠를 텐데...");
		_vText.push_back(L"0");
		_vText.push_back(L"필드는 '통행권'을 구하지 않으면\n접근이 불가능해.");
		_vText.push_back(L"0");
		_vText.push_back(L"마을 북쪽에서 얻을 수 있으니 \n우선 그쪽으로 가 보렴.");
		_vText.push_back(L"4");
		_vText.push_back(L"맞다. 수상한 동굴에는\n절대로 들어가면 안 돼!");
		_vText.push_back(L"6");
		_vText.push_back(L"그럼 행운을 빈다!");
	}
	else if (_fileName == "2")
	{
		p = 6;
		l = 1;
		_vText.push_back(L"6");
		_vText.push_back(L"해냈구나, 레아!");
		_vText.push_back(L"6");
		_vText.push_back(L"생각했던 것보다 적응이 빠른데?");
		_vText.push_back(L"7");
		_vText.push_back(L"(끄덕)");
		_vText.push_back(L"0");
		_vText.push_back(L"통행권을 얻었으니 이제 필드로 \n이동할 수 있을 거야.");
		_vText.push_back(L"0");
		_vText.push_back(L"획득한 아이템은 TAB키를 누르면\n확인할 수 있다는 걸 잊지 마!");
	}
	else if (_fileName == "3")
	{
		p = 0;
		l = 1;
		_vText.push_back(L"0");
		_vText.push_back(L"저쪽으로 가면 드디어 \n몬스터를 만날 수 있어.");
		_vText.push_back(L"0");
		_vText.push_back(L"긴장하지 말고, 파이팅!");
		_vText.push_back(L"9");
		_vText.push_back(L"...?");
		_vText.push_back(L"2");
		_vText.push_back(L"미안...");
	}
	else if (_fileName == "4")
	{
		p = 8;
		l = 1;
		_vText.push_back(L"8");
		_vText.push_back(L"자, 잠깐만 레아!");
		_vText.push_back(L"4");
		_vText.push_back(L"동굴은 들어가지 말라고 했잖아!");
		_vText.push_back(L"5");
		_vText.push_back(L"...!");
		_vText.push_back(L"0");
		_vText.push_back(L"한눈판 사이에 들어와 버리다니...");
		_vText.push_back(L"2");
		_vText.push_back(L"뭐... 별일이야 있겠어?");
	}
	else if (_fileName == "5")
	{
		p = 0;
		l = 5;
		_vText.push_back(L"5");
		_vText.push_back(L"...!");
		_vText.push_back(L"8");
		_vText.push_back(L"아, 이런... 뭔가 불길한 예감이...");
	}
	else if (_fileName == "6")
	{
		p = 8;
		l = 5;
		_vText.push_back(L"5");
		_vText.push_back(L"...");
		_vText.push_back(L"8");
		_vText.push_back(L"온다! 조심해, 레아!");
	}

	lea = new portrait(l);
	pro = new portrait(p);
	lea->init();
	pro->init();

	OBJECTMANAGER->addObject(objectType::UI, lea);
	OBJECTMANAGER->addObject(objectType::UI, pro);
}
