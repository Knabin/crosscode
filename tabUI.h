#pragma once
#include "gameNode.h"
#include "button.h"

class tabUI : public gameNode
{
private:
	class player* _player;
	int _hp;
	int _exp;

	floatRect _hpRC;
	floatRect _expRC;

	bool _on;	//�޴� Ű�� ����
	bool _eq;	//���
	bool _iv;	//�κ�
	bool _sv;	//���̺�
	bool _st;	//����
	int _invenIndex;
	LPBYTE StateArray;
public:
	tabUI() {};
	~tabUI() {};

	bool getOn() { return _on; }

	HRESULT init();
	void release();
	void update();
	void render();
	void inEquip();
	void inInven();
	void inSave();
	void inStat();
	void outMenu();
	void InventoryList();
};

