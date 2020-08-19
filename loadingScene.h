#pragma once
#include "scene.h"

// 처리할 거: sceneManager에서 로드하는 거 끝나면 이동하게끔
// 로딩씬에서 다음 씬 정보를 알고 있어야 할 것 같음

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

