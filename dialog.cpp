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
	// �޸� ������ object manager���� ������
	for (int i = 0; i < _vObjects.size(); ++i)
	{
		_vObjects[i]->setIsAlive(false);
	}
	_vObjects.clear();
}

bool dialog::next()
{
	if (_textIndex >= _vText.size()) return true;		// ������ ����� ���߱� ���� true ��ȯ

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

	//// �̹� ������ ���� render���� �ʱ� ����
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
		_vText.push_back(L"����! ù ������ �Ұ��� �?");
		_vText.push_back(L"2");
		_vText.push_back(L"(����)");
		_vText.push_back(L"1");
		_vText.push_back(L"������!");
		_vText.push_back(L"1");
		_vText.push_back(L"�̹� �˰� �ְ�����,\nW A S D Ű�� �̵��� �� �־�.");
		_vText.push_back(L"1");
		_vText.push_back(L"������ ���콺 Ŭ���� ������ ��!");
		_vText.push_back(L"2");
		_vText.push_back(L"...");
		_vText.push_back(L"1");
		_vText.push_back(L"ó�������� �ݹ� ������ �ž�.");
		_vText.push_back(L"1");
		_vText.push_back(L"���Ϳ� ���� �ε��� ���鼭\n�����ϴ� ���� ���� �ٵ�...");
		_vText.push_back(L"1");
		_vText.push_back(L"�ʵ�� '����'�� ������ ������\n������ �Ұ�����.");
		_vText.push_back(L"1");
		_vText.push_back(L"���� ���ʿ��� ���� �� ������ \n�켱 �������� �� ����.");
		_vText.push_back(L"1");
		_vText.push_back(L"�´�. ������ ��������\n����� ���� �� ��!");
		_vText.push_back(L"1");
		_vText.push_back(L"�׷� ����� ���!");
	}
	else if (fileName == "2")
	{

	}
	lea = new portrait(0);
	pro = new portrait(1);

	OBJECTMANAGER->addObject(objectType::UI, lea);
	OBJECTMANAGER->addObject(objectType::UI, pro);
}