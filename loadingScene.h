#pragma once
#include "scene.h"

// ó���� ��: sceneManager���� �ε��ϴ� �� ������ �̵��ϰԲ�
// �ε������� ���� �� ������ �˰� �־�� �� �� ����

class loadingScene : public scene
{
private:


public:
	loadingScene();
	virtual ~loadingScene() override;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

