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

	_leftThrowItem = false;							//������ left�� �ȴ���
	_rightThrowItem = false;						//������ right�� �ȴ���

	_ItemRangeOutLeftCameraX = false;				//item�� cameraX�� left  ��ǥ�� ����� �ʾҴ�
	_ItemRangeOutRightCameraX = false;				//item�� cameraX�� right ��ǥ�� ����� �ʾҴ�
}

void Item::Update()
{
	//_zorder->SetY(transform->GetY() + 30);
	if (_leftThrowItem)								//left�� item�� ��������
	{
		ItemLeftMove();								//left�� �̵��ϴ� item move��
		if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX())
		{
			ItemRangeOutRightMove();				//item�� ���� �ʰ��� right�� �̵�
		}
	}
	if (_rightThrowItem)							//right�� item�� ��������
	{
		ItemRightMove();							//right�� �̵��ϴ� item Move ��
		if (MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2	- 37 <= transform->GetX() )
		{
			ItemRangeOutLeftMove();					//item�� ���� �ʰ��� left�� �̵�
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

