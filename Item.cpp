#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	_animator->AddClip("trashbox_walk_attack_right", CLIPMANAGER->FindClip("trashbox_walk_attack_right"));
	_itemSpeed = 320.f;		// �������� �ӵ�
	_gravity = 560.f;
	//_gravity = 15.0f;		// �߷�
	_friction = 60.f;		// ������
							//�� ������ ������ �ʱ⿡ init���� �� ��

	_angle = 0.f;			// ����
	_accel = 65.f;			// ���ӷ�
	_itemZ = 0.f;			// �÷��̾��� Z ���� �������� ���� ����
	
	_speedX = 0.f;			// ���ǵ�� �ޱ� ���� �̿��ϱ� ���� ����
	_speedY = 0.f;			// ��
	
	_isGround = true;		//�� ���� �ִ°�? �������� �� ó�� �� ���� �ֱ⿡ true
}

void Item::Update()
{
	transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
   
	if (_isGround == false)					//�� ���� ���� �ʴٸ�
	{
		transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());		
		_speedY += _gravity *TIMEMANAGER->getElapsedTime();
	}

	if (_isGround == true)					//throw�ؼ� �� ���� ���� �Ѵٸ� ������ �ο�
	{
		if (_throwDir == false)				    //right�϶� ������
		{
			_speedX -= _friction * TIMEMANAGER->getElapsedTime();
			if (_speedX <= 0) _speedX = 0;
		}

		if (_throwDir == true)				//left�϶� ������
		{
			_speedX += _friction * TIMEMANAGER->getElapsedTime();
			if (_speedX >= 0) _speedX = 0;
		}
	}
	//���� ���� ��
	if(transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= _itemZ && _itemZ != 0)
	{
		_speedY = 0.0f;
		_isGround = true;
	}

	//item�� MainCam�� ���� �ʰ���
	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 <= transform->GetX())
	{
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
	_throwDir = dir;	
	_isGround = false;
	if (dir == false)				// right�϶�
	{
		//_angle = (PI/4);			// 45��
		_angle = 0;
	}
	if (dir == true)				// left�϶�
	{
		//_angle = (PI * 3 / 4);		//135��
		_angle = PI;
	}

	_speedX = cosf(_angle) * _itemSpeed;
	_speedY = -sinf(_angle) * _itemSpeed;
}

void Item::ChangeClip(string clipName, bool isInitFrame)
{
	if (isInitFrame == false)
	{
		_animator->SetClip(_animator->GetClip(clipName));
	}
	else
	{
		_animator->SetClip(_animator->GetClip(clipName), _animator->currentFrame);
	}
}
