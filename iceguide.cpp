#include "stdafx.h"
#include "iceguide.h"

iceguide::iceguide()
{
}

iceguide::~iceguide()
{
}

HRESULT iceguide::init(float centerX, float centerY)
{
	_name = "iceguide";

	IMAGEMANAGER->addImage("ªœ¡∑æÛ¿Ω", L"images/boss/cold2.png");
	IMAGEMANAGER->addFrameImage("æÛ¿Ωªœ¡∑", L"images/boss/coldframe.png", 40, 1);

	_angle, _angle2, _angle3, _angle4, _angle5 = PI;
	_center.x = centerX;
	_center.y = centerY;
	_centerMeter = 50;

	_meterCount, _meterCount2, _meterCount3, _meterCount4, _meterCount5 = 0;

	//================================================================================================================================================================//

	for (int i = 0; i < 12; i++)
	{
		tagIceguide attack4;
		ZeroMemory(&attack4, sizeof(attack4));
		attack4._speed = 15.5f;
		attack4._size = 170.0f;
		attack4._damage = 10.0f;
		

		attack4._frameX = 0, attack4._frameCount, attack4._currentFrameX = 0;

		attack4._fireStart = false;

		_vIceguide.push_back(attack4);
	}

	for (int i = 0; i < 12; i++)
	{
		tagIceguide attack5;
		ZeroMemory(&attack5, sizeof(attack5));
		attack5._speed = 15.5f;
		attack5._size = 170.0f;
		attack5._damage = 10.0f;

		attack5._frameX = 0, attack5._frameCount, attack5._currentFrameX = 0;

		attack5._fireStart = false;

		_vIceguide2.push_back(attack5);
	}

	for (int i = 0; i < 10; i++)
	{
		tagIceguide attack6;
		ZeroMemory(&attack6, sizeof(attack6));
		attack6._speed = 15.5f;
		attack6._size = 170.0f;
		attack6._damage = 10.0f;

		attack6._frameX = 0, attack6._frameCount, attack6._currentFrameX = 0;

		attack6._fireStart = false;

		_vIceguide3.push_back(attack6);
	}

	for (int i = 0; i < 10; i++)
	{
		tagIceguide attack7;
		ZeroMemory(&attack7, sizeof(attack7));
		attack7._speed = 15.5f;
		attack7._size = 170.0f;
		attack7._damage = 10.0f;

		attack7._frameX = 0, attack7._frameCount, attack7._currentFrameX = 0;

		attack7._fireStart = false;

		_vIceguide4.push_back(attack7);
	}

	for (int i = 0; i < 12; i++)
	{
		tagIceguide attack8;
		ZeroMemory(&attack8, sizeof(attack8));
		attack8._speed = 15.5f;
		attack8._size = 170.0f;
		attack8._damage = 10.0f;

		attack8._frameX = 0, attack8._frameCount, attack8._currentFrameX = 0;

		attack8._fireStart = false;

		_vIceguide5.push_back(attack8);
	}

	

	return S_OK;
}

void iceguide::release()
{
}

void iceguide::update()
{
	move();

	angleUpdate();

	frameUpdate();


	_angle -= 0.201f;

	_angle2 -= 0.201f;

	_angle3 -= 0.201f;

	_angle4 -= 0.201f;

	_angle5 -= 0.201f;

}

void iceguide::render()
{

	for (_viIceguide = _vIceguide.begin(); _viIceguide != _vIceguide.end(); ++_viIceguide)
	{
		if (!_viIceguide->_fireStart) continue;
		{
			//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viIceguide->_rc));

			IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->frameRender(CAMERA->getRelativeVector2(Vector2(_viIceguide->_x , _viIceguide->_y )),
				_viIceguide->_frameX, _iceFrameY);
		}		
	}

	for (_viIceguide2 = _vIceguide2.begin(); _viIceguide2 != _vIceguide2.end(); ++_viIceguide2)
	{
		if (!_viIceguide2->_fireStart) continue;
		{
			//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viIceguide2->_rc));

			IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->frameRender(CAMERA->getRelativeVector2(Vector2(_viIceguide2->_x , _viIceguide2->_y )),
				_viIceguide2->_frameX, _iceFrameY);
		}
	}

	for (_viIceguide3 = _vIceguide3.begin(); _viIceguide3 != _vIceguide3.end(); ++_viIceguide3)
	{
		if (!_viIceguide3->_fireStart) continue;
		{
			//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viIceguide3->_rc));

			IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->frameRender(CAMERA->getRelativeVector2(Vector2(_viIceguide3->_x , _viIceguide3->_y)),
				_viIceguide3->_frameX, _iceFrameY);
		}
	}

	for (_viIceguide4 = _vIceguide4.begin(); _viIceguide4 != _vIceguide4.end(); ++_viIceguide4)
	{
		if (!_viIceguide4->_fireStart) continue;
		{
			//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viIceguide4->_rc));

			IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->frameRender(CAMERA->getRelativeVector2(Vector2(_viIceguide4->_x, _viIceguide4->_y)),
				_viIceguide4->_frameX, _iceFrameY);
		}
	}

	for (_viIceguide5 = _vIceguide5.begin(); _viIceguide5 != _vIceguide5.end(); ++_viIceguide5)
	{
		if (!_viIceguide5->_fireStart) continue;
		{
			//D2DRENDERER->DrawRectangle(CAMERA->getRelativeRect(_viIceguide5->_rc));

			IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->frameRender(CAMERA->getRelativeVector2(Vector2(_viIceguide5->_x, _viIceguide5->_y)),
				_viIceguide5->_frameX, _iceFrameY);
		}
	}
}

void iceguide::fire()
{
	for (_viIceguide = _vIceguide.begin(); _viIceguide != _vIceguide.end(); ++_viIceguide)
	{		
		if (_viIceguide->_fireStart) continue;
		{
			_meterCount++;

			_viIceguide->_fireStart = true;

			_viIceguide->_x = sinf(_angle) * _centerMeter + _center.x + (50 * _meterCount);
			_viIceguide->_y = -cosf(_angle) * _centerMeter + _center.y;

			_viIceguide->_angle = _angle;

			_viIceguide->_rc.update(Vector2(_viIceguide->_x, _viIceguide->_y), Vector2(_viIceguide->_size, _viIceguide->_size), pivot::CENTER);

			break;
		}			
	}

	for (_viIceguide2 = _vIceguide2.begin(); _viIceguide2 != _vIceguide2.end(); ++_viIceguide2)
	{
		if (_viIceguide2->_fireStart) continue;
		{
			_meterCount2++;

			_viIceguide2->_fireStart = true;

			_viIceguide2->_x = sinf(_angle2) * _centerMeter + _center.x;
			_viIceguide2->_y = -cosf(_angle2) * _centerMeter + _center.y + (50 * _meterCount2);

			_viIceguide2->_angle = _angle2;

			_viIceguide2->_rc.update(Vector2(_viIceguide2->_x, _viIceguide2->_y), Vector2(_viIceguide2->_size, _viIceguide2->_size), pivot::CENTER);

			break;
		}
	}

	for (_viIceguide3 = _vIceguide3.begin(); _viIceguide3 != _vIceguide3.end(); ++_viIceguide3)
	{
		if (_viIceguide3->_fireStart) continue;
		{
			_meterCount3++;

			_viIceguide3->_fireStart = true;

			_viIceguide3->_x = sinf(_angle3) * _centerMeter + _center.x + (50 * _meterCount3);
			_viIceguide3->_y = -cosf(_angle3) * _centerMeter + _center.y + (50 * _meterCount3);

			_viIceguide3->_angle = _angle3;

			_viIceguide3->_rc.update(Vector2(_viIceguide3->_x, _viIceguide3->_y), Vector2(_viIceguide3->_size, _viIceguide3->_size), pivot::CENTER);

			break;
		}
	}

	for (_viIceguide4 = _vIceguide4.begin(); _viIceguide4 != _vIceguide4.end(); ++_viIceguide4)
	{
		if (_viIceguide4->_fireStart) continue;
		{
			_meterCount4++;

			_viIceguide4->_fireStart = true;

			_viIceguide4->_x = sinf(_angle4) * _centerMeter + _center.x - (50 * _meterCount4);
			_viIceguide4->_y = -cosf(_angle4) * _centerMeter + _center.y + (50 * _meterCount4);

			_viIceguide4->_angle = _angle4;

			_viIceguide4->_rc.update(Vector2(_viIceguide4->_x, _viIceguide4->_y), Vector2(_viIceguide4->_size, _viIceguide4->_size), pivot::CENTER);

			break;
		}
	}

	for (_viIceguide5 = _vIceguide5.begin(); _viIceguide5 != _vIceguide5.end(); ++_viIceguide5)
	{
		if (_viIceguide5->_fireStart) continue;
		{
			_meterCount5++;

			_viIceguide5->_fireStart = true;

			_viIceguide5->_x = sinf(_angle5) * _centerMeter + _center.x - (50 * _meterCount5);
			_viIceguide5->_y = -cosf(_angle5) * _centerMeter + _center.y;

			_viIceguide5->_angle = _angle5;

			_viIceguide5->_rc.update(Vector2(_viIceguide5->_x, _viIceguide5->_y), Vector2(_viIceguide5->_size, _viIceguide5->_size), pivot::CENTER);

			break;
		}
	}
}

void iceguide::move()
{
	for (_viIceguide = _vIceguide.begin(); _viIceguide != _vIceguide.end(); ++_viIceguide)
	{
		if (_viIceguide->_fireStart) continue;
		{
			_viIceguide->_x += sinf(_viIceguide->_angle) * _viIceguide->_speed;
			_viIceguide->_y += -cosf(_viIceguide->_angle) * _viIceguide->_speed;

			_viIceguide->_rc.update(Vector2(_viIceguide->_x, _viIceguide->_y), Vector2(_viIceguide->_size, _viIceguide->_size), pivot::CENTER);

		}
	}

	for (_viIceguide2 = _vIceguide2.begin(); _viIceguide2 != _vIceguide2.end(); ++_viIceguide2)
	{
		if (_viIceguide2->_fireStart) continue;
		{
			_viIceguide2->_x += sinf(_viIceguide2->_angle) * _viIceguide2->_speed;
			_viIceguide2->_y += -cosf(_viIceguide2->_angle) * _viIceguide2->_speed;

			_viIceguide2->_rc.update(Vector2(_viIceguide2->_x, _viIceguide2->_y), Vector2(_viIceguide2->_size, _viIceguide2->_size), pivot::CENTER);

		}
	}

	for (_viIceguide3 = _vIceguide3.begin(); _viIceguide3 != _vIceguide3.end(); ++_viIceguide3)
	{
		if (_viIceguide3->_fireStart) continue;
		{
			_viIceguide3->_x += sinf(_viIceguide3->_angle) * _viIceguide3->_speed;
			_viIceguide3->_y += -cosf(_viIceguide3->_angle) * _viIceguide3->_speed;

			_viIceguide3->_rc.update(Vector2(_viIceguide3->_x, _viIceguide3->_y), Vector2(_viIceguide3->_size, _viIceguide3->_size), pivot::CENTER);

		}
	}

	for (_viIceguide4 = _vIceguide4.begin(); _viIceguide4 != _vIceguide4.end(); ++_viIceguide4)
	{
		if (_viIceguide4->_fireStart) continue;
		{
			_viIceguide4->_x += sinf(_viIceguide4->_angle) * _viIceguide4->_speed;
			_viIceguide4->_y += -cosf(_viIceguide4->_angle) * _viIceguide4->_speed;

			_viIceguide4->_rc.update(Vector2(_viIceguide4->_x, _viIceguide4->_y), Vector2(_viIceguide4->_size, _viIceguide4->_size), pivot::CENTER);

		}
	}

	for (_viIceguide5 = _vIceguide5.begin(); _viIceguide5 != _vIceguide5.end(); ++_viIceguide5)
	{
		if (_viIceguide5->_fireStart) continue;
		{
			_viIceguide5->_x += sinf(_viIceguide5->_angle) * _viIceguide5->_speed;
			_viIceguide5->_y += -cosf(_viIceguide5->_angle) * _viIceguide5->_speed;

			_viIceguide5->_rc.update(Vector2(_viIceguide5->_x, _viIceguide5->_y), Vector2(_viIceguide5->_size, _viIceguide5->_size), pivot::CENTER);

		}
	}
}

void iceguide::angleUpdate()
{
	_centerEnd.x = sinf(_angle) * _centerMeter + _center.x;
	_centerEnd.y = -cosf(_angle) * _centerMeter + _center.y;

	_centerEnd2.x = sinf(_angle2) * _centerMeter + _center.x;
	_centerEnd2.y = -cosf(_angle2) * _centerMeter + _center.y;

	_centerEnd3.x = sinf(_angle3) * _centerMeter + _center.x;
	_centerEnd3.y = -cosf(_angle3) * _centerMeter + _center.y;

	_centerEnd4.x = sinf(_angle4) * _centerMeter + _center.x;
	_centerEnd4.y = -cosf(_angle4) * _centerMeter + _center.y;

	_centerEnd5.x = sinf(_angle5) * _centerMeter + _center.x;
	_centerEnd5.y = -cosf(_angle5) * _centerMeter + _center.y;
	
}

void iceguide::frameUpdate()
{
	for (_viIceguide = _vIceguide.begin(); _viIceguide != _vIceguide.end(); ++_viIceguide)
	{
		_viIceguide->_frameCount++;

		if (_viIceguide->_fireStart)
		{
			_iceFrameY = 0;

			if (_viIceguide->_frameCount % 5 == 0)
			{

				if (_viIceguide->_currentFrameX >= IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->getMaxFrameX())
				{
					_viIceguide->_fireStart = false;
					_viIceguide->_currentFrameX = 0;
				}

				_viIceguide->_frameX = _viIceguide->_currentFrameX;
				_viIceguide->_currentFrameX++;
				_viIceguide->_frameCount = 0;
			}
		}
	}

	for (_viIceguide2 = _vIceguide2.begin(); _viIceguide2 != _vIceguide2.end(); ++_viIceguide2)
	{
		_viIceguide2->_frameCount++;

		if (_viIceguide2->_fireStart)
		{
			_iceFrameY = 0;

			if (_viIceguide2->_frameCount % 5 == 0)
			{

				if (_viIceguide2->_currentFrameX >= IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->getMaxFrameX())
				{
					_viIceguide2->_fireStart = false;
					_viIceguide2->_currentFrameX = 0;
				}

				_viIceguide2->_frameX = _viIceguide2->_currentFrameX;
				_viIceguide2->_currentFrameX++;
				_viIceguide2->_frameCount = 0;
			}
		}
	}

	for (_viIceguide3 = _vIceguide3.begin(); _viIceguide3 != _vIceguide3.end(); ++_viIceguide3)
	{
		_viIceguide3->_frameCount++;

		if (_viIceguide3->_fireStart)
		{
			_iceFrameY = 0;

			if (_viIceguide3->_frameCount % 5 == 0)
			{

				if (_viIceguide3->_currentFrameX >= IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->getMaxFrameX())
				{
					_viIceguide3->_fireStart = false;
					_viIceguide3->_currentFrameX = 0;
				}

				_viIceguide3->_frameX = _viIceguide3->_currentFrameX;
				_viIceguide3->_currentFrameX++;
				_viIceguide3->_frameCount = 0;
			}
		}
	}

	for (_viIceguide4 = _vIceguide4.begin(); _viIceguide4 != _vIceguide4.end(); ++_viIceguide4)
	{
		_viIceguide4->_frameCount++;

		if (_viIceguide4->_fireStart)
		{
			_iceFrameY = 0;

			if (_viIceguide4->_frameCount % 5 == 0)
			{

				if (_viIceguide4->_currentFrameX >= IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->getMaxFrameX())
				{
					_viIceguide4->_fireStart = false;
					_viIceguide4->_currentFrameX = 0;
				}

				_viIceguide4->_frameX = _viIceguide4->_currentFrameX;
				_viIceguide4->_currentFrameX++;
				_viIceguide4->_frameCount = 0;
			}
		}
	}

	for (_viIceguide5 = _vIceguide5.begin(); _viIceguide5 != _vIceguide5.end(); ++_viIceguide5)
	{
		_viIceguide5->_frameCount++;

		if (_viIceguide5->_fireStart)
		{
			_iceFrameY = 0;

			if (_viIceguide5->_frameCount % 5 == 0)
			{

				if (_viIceguide5->_currentFrameX >= IMAGEMANAGER->findImage("æÛ¿Ωªœ¡∑")->getMaxFrameX())
				{
					_viIceguide5->_fireStart = false;
					_viIceguide5->_currentFrameX = 0;
				}

				_viIceguide5->_frameX = _viIceguide5->_currentFrameX;
				_viIceguide5->_currentFrameX++;
				_viIceguide5->_frameCount = 0;
			}
		}
	}
}

void iceguide::removeFire1(int Num1)
{
	_vIceguide.erase(_vIceguide.begin() + Num1);
}

void iceguide::removeFire2(int Num2)
{
	_vIceguide2.erase(_vIceguide2.begin() + Num2);
}

void iceguide::removeFire3(int Num3)
{
	_vIceguide3.erase(_vIceguide3.begin() + Num3);
}

void iceguide::removeFire4(int Num4)
{
	_vIceguide4.erase(_vIceguide4.begin() + Num4);
}

void iceguide::removeFire5(int Num5)
{
	_vIceguide5.erase(_vIceguide5.begin() + Num5);
}
