#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	enterNum = 0;
	exitNum = 0;
	
	//_itemSpeed = 210.0f;
	//_gravity = 110.0f;

	//_angle = PI / 2;

}

void Item::Update()
{
	//_moveX += cosf(_angle) * _itemSpeed * TIMEMANAGER->getElapsedTime();
	//_moveY += -sinf(_angle) * _itemSpeed * TIMEMANAGER->getElapsedTime();
	
	//transform->MoveX(_itemSpeed * TIMEMANAGER->getElapsedTime());			//speed��ŭ �����δ�
	//transform->MoveY(_gravity *  TIMEMANAGER->getElapsedTime());			//gravity��ŭ ��������
	
	transform->MoveX(_moveX * TIMEMANAGER->getElapsedTime());
	transform->MoveY(_moveY * TIMEMANAGER->getElapsedTime());
	//transform->MoveX(_itemSpeed * TIMEMANAGER->getElapsedTime());
	//transform->MoveY(_itemSpeed * TIMEMANAGER->getElapsedTime());

	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 - 37 <= transform->GetX())
	{
		//_itemSpeed *= -1;		//���� �ʰ��� ���� �ٲ���
		//_gravity = 80;			//���� �ʰ��� �߷°�

		_moveX *= -1;
		_gravity = 0;
	}

	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= itemZ )
	{	
		//item�̶�� component�� ��� item�� �������� ����
		//zorder�� item�� �عٴ� �������� ���� �־�� ��
		//item�� ���̴� �� �ٸ���
		//�׷��� image�� ũ�⸦ �������� ����

		//_itemSpeed = 0;
		//_gravity = 0;

		//_moveX, _moveY = 0;
		_moveX = 0;
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

void Item::Throw(bool dir)			//throw�� bool�� dir ��ȯ
{
	throwDir = dir;					

	_gravity = 400;
	_itemSpeed = 400;
	_angle = PI / 4.2;

	_moveX += cosf(_angle) * _itemSpeed;
	_moveY += -sinf(_angle) * _itemSpeed + _gravity;

	if (dir == false)				//right�϶�
	{
		//transform->Move(_itemSpeed * TIMEMANAGER->getElapsedTime(), _gravity * TIMEMANAGER->getElapsedTime());
		//_itemSpeed = 210;	
		//transform->MoveY(PI/4);
		transform->Move(_moveX * TIMEMANAGER->getElapsedTime(), _moveY * TIMEMANAGER->getElapsedTime());
	}
	else							//left�϶�
	{
		//_itemSpeed = -210;
		transform->Move(_moveX * TIMEMANAGER->getElapsedTime(), _moveY * TIMEMANAGER->getElapsedTime());
	}
}

