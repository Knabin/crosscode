#include "stdafx.h"
#include "dialog.h"
#include "dialogText.h"

dialog::dialog(string fileName)
	: _textIndex(0)
{
}

dialog::~dialog()
{
	// �޸� ������ object manager���� ������
	for (int i = 0; i < _vObjects.size(); ++i)
	{
		_vObjects[i]->setIsAlive(false);
	}
	_vObjects.clear();
}

bool dialog::next()
{
	if (_textIndex > _vText.size()) return true;		// ������ ����� ���߱� ���� true ��ȯ
	

	// �̹� ������ ���� ������� ����
	for (int i = 0; i < _textIndex - 1; ++i)
	{
		if (!_vObjects[i]->getIsActive()) continue;
		_vObjects[i]->setIsActive(false);
	}

	return false;
}

void dialog::loadText()
{
}
