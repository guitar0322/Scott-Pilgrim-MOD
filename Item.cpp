#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	itemZ = 0;
	_friction = 0.0007f;		//마찰력
	_frictionCount = 0;
	_angle = 0;
	//_angle = PI;
	_throwTime = 0;
	_gravity = 0;
	_itemSpeed = 290;
}

void Item::Update()
{
	_throwTime++;
	transform->MoveX(_moveX * TIMEMANAGER->getElapsedTime());
	transform->MoveY(_moveY * TIMEMANAGER->getElapsedTime());
		
	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 - 37 <= transform->GetX())
	{
		_moveX *= -1;					//범위 초과시 x 좌표 방향 바꿔줌		
	}

	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= itemZ && itemZ != 0 )
	{	
		_frictionCount++;

		if (!_dir)
		{
			_moveX * _friction;
		}
		if(_dir)
		{
			-(_moveX * _friction);
		}
		if (_frictionCount > 100)
		{
			_moveX = 0;
			_frictionCount = 0;
		}
		_moveY = 0;
	}
}

void Item::Render()
{
}

void Item::SetItemImage(string imageName)
{
	_animator->AddClip(imageName, CLIPMANAGER->FindClip(imageName));
	_animator->SetClip(imageName);
}

void Item::Throw(bool dir)			//throw시 bool값 dir 반환
{
	throwDir = dir;	
	
	if (dir == false)				//right일때
	{
		_angle = 0;
		//if ()
		//{
			_angle = -(PI / 4);
		//}
		//_angle = -(PI/8);			//약 -22;
		//_angle = -(PI / 4);       //약 -45;
	}
	else							//left일때
	{
		_angle = -(PI / 1.3);				
	}
	//_gravity = 30;
	_gravity += 35;
	//_gravity += 25;
	_moveX += cosf(_angle) * _itemSpeed;
	_moveY += -sinf(_angle) * _itemSpeed + _gravity;
}
