#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	_itemSpeed = 0.0f;		// �÷��̾ ������ ��� �����̴� �������� �ӵ�
	_gravity = 0.0f;		// �߷�
	_angle = 0.0f;			// ����

	_friction = 30.0f;		// ������
	_dashSpeed = 10.0f;		// ���� �������� ���, ������ �ܿ� ��
	
	itemZ = 0;				// �÷��̾��� Z ���� �������� ���� ����
	
	_speedX = 0;			// ���ǵ�� �ޱ� ���� �̿��ϱ� ���� ����
	_speedY = 0;			// ��

	_onGround = false;		//���� ���� �߳�?
}

void Item::Update()
{
	transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
	transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());

	_dashSpeed -= _friction * TIMEMANAGER->getElapsedTime();

	_gravity += 0.0008f;

	//���� ���� ��
	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= itemZ && itemZ != 0)
	{
		_speedY = 0;
		_onGround = true;			//item�� ���� ���� �ߴٸ�
		
		if (_onGround)
		{
			if (!_dir)						//right�϶�
			{
				transform->MoveX(_dashSpeed * TIMEMANAGER->getElapsedTime());
			}
			if (_dir)						//left�ϋ�
			{
				transform->MoveX(-_dashSpeed * TIMEMANAGER->getElapsedTime());
			}
			if (_dashSpeed < 0)
			{
				_onGround = false;
			}
		}

		if (!_onGround)
		{
			_onGround = false;
			transform->MoveX(0);
		}
	}

	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 <= transform->GetX())
	{
		//_dashSpeed *= -1;
		_speedX *= -1;					//���� �ʰ��� x ��ǥ ���� �ٲ���		
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
	
	if (dir == false)				// right�϶�
	{
		_itemSpeed = 110;
		_angle = -(PI / 4);	
	}
	if (dir == true)				// left�϶�
	{
		_itemSpeed = 110;
		_angle = -(PI / 1.3);				
	}
	_speedX += cosf(_angle) * _itemSpeed;
	_speedY += -sinf(_angle) * _itemSpeed + _gravity;
}
