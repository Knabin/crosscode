#pragma once
#include "gameObject.h"

class bossHPBar : public gameObject
{
private:
	int _maxHP;
	int _HP;

public:
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void setMaxHP(int hp) { _maxHP = hp; }
	void setHP(int hp) { _HP = hp; }
};

