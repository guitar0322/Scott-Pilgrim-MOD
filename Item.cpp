#include "stdafx.h"
#include "Item.h"
#include "Player.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	//_zOrder = gameObject->GetComponent<ZOrder>();
	player = gameObject->GetComponent<Player>();

	//_itemZ = _zorder->GetZ(); //���� itemZ���� item�� zorder gety���̴�

	enterNum = 0;
	exitNum = 0;

	_itemSpeed = 210;
	////_gravity = 80;
	//_gravity = 0;

	_leftThrowItem = false;							//������ left�� �ȴ���
	_rightThrowItem = false;						//������ right�� �ȴ���

	_ItemRangeOutLeftCameraX = false;				//item�� cameraX�� left  ��ǥ�� ����� �ʾҴ�
	_ItemRangeOutRightCameraX = false;				//item�� cameraX�� right ��ǥ�� ����� �ʾҴ�
}

void Item::Update()
{
	transform->MoveX(_itemSpeed * TIMEMANAGER->getElapsedTime());
	transform->MoveY(_gravity * TIMEMANAGER->getElapsedTime());

	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 - 37 <= transform->GetX())
	{
		_itemSpeed *= -1;			//item�� ���� �ʰ��� right�� �̵�
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

