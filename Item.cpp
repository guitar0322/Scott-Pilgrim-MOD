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
	transform->MoveX(_itemSpeed *TIMEMANAGER->getElapsedTime());			//speed��ŭ �̵��Ѵ�
	transform->MoveY(_gravity *  TIMEMANAGER->getElapsedTime());			//gravity��ŭ �̵��Ѵ�

	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 - 37 <= transform->GetX())
	{
		_itemSpeed *= -1;				//���� �ʰ��� ���� �ٲ���
		_gravity = 100;				//���� �ʰ��� �߷°� 0;
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

void Item::Throw(bool dir)			//throw�� bool�� dir ��ȯ
{
	throwDir = dir;					

	if (dir == false)				//right�϶�
	{
		_itemSpeed = 140;
		
	}
	else							//left�϶�
	{
		_itemSpeed = -140;
	}
}

