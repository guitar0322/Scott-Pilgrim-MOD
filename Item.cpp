#include "stdafx.h"
#include "Item.h"
#include "Player.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	//_zOrder = gameObject->GetComponent<ZOrder>();
	player = gameObject->GetComponent<Player>();

	//_itemZ = _zorder->GetZ(); //현재 itemZ값은 item의 zorder gety값이다

	enterNum = 0;
	exitNum = 0;

	_itemSpeed = 210;
	////_gravity = 80;
	//_gravity = 0;

	_leftThrowItem = false;							//아이템 left로 안던짐
	_rightThrowItem = false;						//아이템 right로 안던짐

	_ItemRangeOutLeftCameraX = false;				//item이 cameraX의 left  좌표로 벗어나지 않았다
	_ItemRangeOutRightCameraX = false;				//item이 cameraX의 right 좌표로 벗어나지 않았다
}

void Item::Update()
{
	transform->MoveX(_itemSpeed * TIMEMANAGER->getElapsedTime());
	transform->MoveY(_gravity * TIMEMANAGER->getElapsedTime());

	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 - 37 <= transform->GetX())
	{
		_itemSpeed *= -1;			//item이 범위 초과시 right로 이동
		_gravity = 80;
	}

	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= _itemZ)
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

void Item::Throw(bool dir)
{
	_throwDir = dir;
	_gravity = 0;
	if (dir == false)
	{
		_itemSpeed = 210;
	}
	else
	{
		_itemSpeed = -210;
	}
}

