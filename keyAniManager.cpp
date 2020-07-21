#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"

keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{
}

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{
	//싸그리 해제해주자
	deleteAll();
}

void keyAniManager::update()
{
	iterTotalAnimation vIter;
	iterAnimation mIter;

	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay()) continue;
				(*vArrIter)->frameUpdate(timeManager::getInstance()->getElapsedTime() * 1.0f);
			}
		}
	}
}

void keyAniManager::render()
{
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);
		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setDefPlayFrame(reverse, loop);
		vAnimationBuffer[i]->setFPS(fps);
	}

	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);
		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION(cbFunction));
		vAnimationBuffer[i]->setFPS(fps);
	}

	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);
		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
		vAnimationBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);

}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);

		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setPlayFrame(arr, arrLen, loop);
		vAnimationBuffer[i]->setFPS(fps);
	}

	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;


	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);

		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION(cbFunction));
		vAnimationBuffer[i]->setFPS(fps);
	}

	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;


	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);

		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
		vAnimationBuffer[i]->setFPS(fps);
	}

	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;


	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);

		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setPlayFrame(start, end, reverse, loop);
		vAnimationBuffer[i]->setFPS(fps);
	}

	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);

		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION(cbFunction));
		vAnimationBuffer[i]->setFPS(fps);
	}

	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj, int buffer)
{
	image* img = imageManager::getInstance()->findImage(imageKeyName);
	arrAnimations vAnimationBuffer;
	arrAnimation mArrAnimation;


	for (int i = 0; i < buffer; ++i)
	{
		vAnimationBuffer.push_back(new animation);

		vAnimationBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAnimationBuffer[i]->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
		vAnimationBuffer[i]->setFPS(fps);
	}

	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAnimationBuffer));

	_vTotalAnimation.push_back(mArrAnimation);
}

void keyAniManager::start(string animationKeyName)
{
	iterTotalAnimation vIter;
	iterAnimation mIter;

	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == animationKeyName)) break;

			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->isPlay()) continue;
				(*vArrIter)->start();
				return;
			}
		}
	}
}

void keyAniManager::stop(string animationKeyName)
{
	iterTotalAnimation vIter;
	iterAnimation mIter;

	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == animationKeyName)) break;

			iterAnimations vArrIter;

			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay()) continue;
				(*vArrIter)->stop();
				return;
			}
		}
	}
}

void keyAniManager::pause(string animationKeyName)
{
	//iterAnimation iter = _mTotalAnimation.find(animationKeyName);

	//iter->second->pause();
}

void keyAniManager::resume(string animationKeyName)
{
	//iterAnimation iter = _mTotalAnimation.find(animationKeyName);

	//iter->second->resume();
}

animation * keyAniManager::findAnimation(string animationKeyName)
{
	iterTotalAnimation vIter;
	iterAnimation mIter;

	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == animationKeyName)) continue;
			// 맵 이터 <애니메이션 이름, 동일한 애니메이션을 여러개 가지고 있는 벡터>

			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->isPlay()) continue;
				return (*vArrIter);
			}
		}
	}

	return nullptr;
}

void keyAniManager::deleteAll()
{
	iterTotalAnimation vIter;
	iterAnimation mIter;

	// 토탈
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		mIter = vIter->begin();
		// 맵
		for (; mIter != vIter->end(); )
		{
			if (mIter->second.size() != NULL)
			{
				iterAnimations vArrIter = mIter->second.begin();

				for (; vArrIter != mIter->second.end();)
				{
					(*vArrIter)->release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else ++mIter;
		}
	}
}
