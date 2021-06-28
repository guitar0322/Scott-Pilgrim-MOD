#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	_itemSpeed = 140;
	_gravity = 30;
}

void Item::Update()
{
	transform->MoveX(_itemSpeed *TIMEMANAGER->getElapsedTime());			//speed만큼 이동한다
	transform->MoveY(_gravity *  TIMEMANAGER->getElapsedTime());			//gravity만큼 이동한다

	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 - 37 <= transform->GetX())
	{
		_itemSpeed *= -1;				//범위 초과시 방향 바꿔줌
		_gravity = 100;				//범위 초과시 중력값 0;
	}

	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= itemZ )
	{	
		_itemSpeed = 0;
		_gravity = 0;
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
		_itemSpeed = 140;
		
	}
	else							//left일때
	{
		_itemSpeed = -140;
	}
}

