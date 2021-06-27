#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	
	_zorder = gameObject->GetComponent<ZOrder>();

	enterNum = 0;
	exitNum = 0;

	_itemSpeed = 210;
	_gravity = 80;

	_leftThrowItem = false;							//아이템 left로 안던짐
	_rightThrowItem = false;						//아이템 right로 안던짐

	_ItemRangeOutLeftCameraX = false;				//item이 cameraX의 left  좌표로 벗어나지 않았다
	_ItemRangeOutRightCameraX = false;				//item이 cameraX의 right 좌표로 벗어나지 않았다
}

void Item::Update()
{
	//_zorder->SetY(transform->GetY() + 30);
	if (_leftThrowItem)								//left로 item을 던졌을때
	{
		ItemLeftMove();								//left로 이동하는 item move값
		if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX())
		{
			ItemRangeOutRightMove();				//item이 범위 초과시 right로 이동
		}
	}
	if (_rightThrowItem)							//right로 item을 던졌을때
	{
		ItemRightMove();							//right로 이동하는 item Move 값
		if (MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2	- 37 <= transform->GetX() )
		{
			ItemRangeOutLeftMove();					//item이 범위 초과시 left로 이동
		}
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

void Item::OnCollision(GameObject* gameObject)
{
	enterNum++;
}

void Item::OnTriggerEnter(GameObject* gameObject)
{
	enterNum++;
}

void Item::OnTriggerExit(GameObject* gameObject)
{
	exitNum++;
}

void Item::ItemLeftMove()
{
	transform->Move(-_itemSpeed * TIMEMANAGER->getElapsedTime(), _gravity * TIMEMANAGER->getElapsedTime());
}

void Item::ItemRightMove()
{
	transform->Move(_itemSpeed * TIMEMANAGER->getElapsedTime(), _gravity * TIMEMANAGER->getElapsedTime());
}

void Item::ItemRangeOutLeftMove()
{
	transform->Move(-_itemSpeed * TIMEMANAGER->getElapsedTime(), _gravity * TIMEMANAGER->getElapsedTime());
}

void Item::ItemRangeOutRightMove()
{
	transform->Move(_itemSpeed * TIMEMANAGER->getElapsedTime(), _gravity * TIMEMANAGER->getElapsedTime());
}

