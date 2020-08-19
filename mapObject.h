#pragma once
#include "gameObject.h"

// 플레이어와 상호작용하지 않지만, 통째로 Z-ORDER 및 렌더하기 위한 오브젝트 선언

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

