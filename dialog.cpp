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

	// ¦����� ���α׷���
	if (type % 2 == 0)
	{
		pro->setType(type);
	}
	// Ȧ����� ����
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

	//// �̹� ������ ���� render���� �ʱ� ����
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
		_vText.push_back(L"����! ù ���� �Ұ��� �?");
		_vText.push_back(L"3");
		_vText.push_back(L"(����)");
		_vText.push_back(L"6");
		_vText.push_back(L"��! ����. ������!");
		_vText.push_back(L"0");
		_vText.push_back(L"W A S D Ű�� �̵��� �� �־�.\n�̹� �˰� ���� ���� ������.");
		_vText.push_back(L"0");
		_vText.push_back(L"������ ���콺 Ŭ���� ������ ��!");
		_vText.push_back(L"7");
		_vText.push_back(L"...");
		_vText.push_back(L"0");
		_vText.push_back(L"ó�������� �ݹ� ������ �ž�.");
		_vText.push_back(L"2");
		_vText.push_back(L"���Ϳ� ���� �ε��� ���鼭\n�����ϴ� ���� ���� �ٵ�...");
		_vText.push_back(L"0");
		_vText.push_back(L"�ʵ�� '�����'�� ������ ������\n������ �Ұ�����.");
		_vText.push_back(L"0");
		_vText.push_back(L"���� ���ʿ��� ���� �� ������ \n�켱 �������� �� ����.");
		_vText.push_back(L"4");
		_vText.push_back(L"�´�. ������ ��������\n����� ���� �� ��!");
		_vText.push_back(L"6");
		_vText.push_back(L"�׷� ����� ���!");
	}
	else if (_fileName == "2")
	{
		p = 6;
		l = 1;
		_vText.push_back(L"6");
		_vText.push_back(L"�س±���, ����!");
		_vText.push_back(L"6");
		_vText.push_back(L"�����ߴ� �ͺ��� ������ ������?");
		_vText.push_back(L"7");
		_vText.push_back(L"(����)");
		_vText.push_back(L"0");
		_vText.push_back(L"������� ������� ���� �ʵ�� \n�̵��� �� ���� �ž�.");
		_vText.push_back(L"0");
		_vText.push_back(L"ȹ���� �������� TABŰ�� ������\nȮ���� �� �ִٴ� �� ���� ��!");
	}
	else if (_fileName == "3")
	{
		p = 0;
		l = 1;
		_vText.push_back(L"0");
		_vText.push_back(L"�������� ���� ���� \n���͸� ���� �� �־�.");
		_vText.push_back(L"0");
		_vText.push_back(L"�������� ����, ������!");
		_vText.push_back(L"9");
		_vText.push_back(L"...?");
		_vText.push_back(L"2");
		_vText.push_back(L"�̾�...");
	}
	else if (_fileName == "4")
	{
		p = 8;
		l = 1;
		_vText.push_back(L"8");
		_vText.push_back(L"��, ��� ����!");
		_vText.push_back(L"4");
		_vText.push_back(L"������ ���� ����� ���ݾ�!");
		_vText.push_back(L"5");
		_vText.push_back(L"...!");
		_vText.push_back(L"0");
		_vText.push_back(L"�Ѵ��� ���̿� ���� �����ٴ�...");
		_vText.push_back(L"2");
		_vText.push_back(L"��... �����̾� �ְھ�?");
	}
	else if (_fileName == "5")
	{
		p = 0;
		l = 5;
		_vText.push_back(L"5");
		_vText.push_back(L"...!");
		_vText.push_back(L"8");
		_vText.push_back(L"��, �̷�... ���� �ұ��� ������...");
	}
	else if (_fileName == "6")
	{
		p = 8;
		l = 5;
		_vText.push_back(L"5");
		_vText.push_back(L"...");
		_vText.push_back(L"8");
		_vText.push_back(L"�´�! ������, ����!");
	}

	lea = new portrait(l);
	pro = new portrait(p);
	lea->init();
	pro->init();

	OBJECTMANAGER->addObject(objectType::UI, lea);
	OBJECTMANAGER->addObject(objectType::UI, pro);
}
