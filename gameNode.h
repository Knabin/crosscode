#pragma once
#include "image.h"

class gameNode
{
private:
	bool _managerInit;		//�Ŵ����� �ʱ�ȭ�Ҳ���

public:
	gameNode();
	virtual ~gameNode();

	//HRESULT�� ����ũ�μ���Ʈ ���� ����� ��ȯ�� �ε�
	//S_OK, E_FAIL, SUCCDED ������ ���â�� 
	//����� �ʱ�ȭ�� �ߵƴ��� �ƴ����� �����ش�
	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� ����
	virtual void update();			//���� ����
	virtual void render();			//�׸��� ����

	//����� DC�޸� ������

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

