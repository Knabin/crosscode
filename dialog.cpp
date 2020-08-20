#include "stdafx.h"
#include "dialog.h"
#include "dialogText.h"

dialog::dialog(string fileName)
	: _textIndex(0)
{
}

dialog::~dialog()
{
	// 메모리 해제는 object manager에서 진행함
	for (int i = 0; i < _vObjects.size(); ++i)
	{
		_vObjects[i]->setIsAlive(false);
	}
	_vObjects.clear();
}

bool dialog::next()
{
	if (_textIndex > _vText.size()) return true;		// 마지막 대사라면 멈추기 위해 true 반환
	

	// 이미 지나간 대사들 출력하지 않음
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
