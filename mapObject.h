#pragma once
#include "gameObject.h"

// �÷��̾�� ��ȣ�ۿ����� ������, ��°�� Z-ORDER �� �����ϱ� ���� ������Ʈ ����

enum
{
	TREE,
	GRASS,
	ROOF,
	END
};

class mapObject : public gameObject
{
private:
	image* _image;
	int _type;
	int _frameX;

public:
	// type 0: tree, 1: grass
	mapObject(int type, int frameX);

	virtual HRESULT init() override;
	virtual void render() override;
};

