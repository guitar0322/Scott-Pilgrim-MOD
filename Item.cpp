#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	_itemSpeed = 0.0f;		// 플레이어가 던졌을 경우 움직이는 아이템의 속도
	_gravity = 0.0f;		// 중력
	_angle = 0.0f;			// 각도

	_friction = 30.0f;		// 마찰력
	_dashSpeed = 10.0f;		// 땅에 떨어졌을 경우, 물건의 잔여 힘
	
	itemZ = 0;				// 플레이어의 Z 값을 가져오기 위한 변수
	
	_speedX = 0;			// 스피드와 앵글 값을 이용하기 위한 변수
	_speedY = 0;			// 상동

	_onGround = false;		//땅에 착지 했나?
}

void Item::Update()
{
	transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
	transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());

	_dashSpeed -= _friction * TIMEMANAGER->getElapsedTime();

	_gravity += 0.0008f;

	//땅에 착지 시
	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= itemZ && itemZ != 0)
	{
		_speedY = 0;
		_onGround = true;			//item이 땅에 착지 했다면
		
		if (_onGround)
		{
			if (!_dir)						//right일때
			{
				transform->MoveX(_dashSpeed * TIMEMANAGER->getElapsedTime());
			}
			if (_dir)						//left일떄
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
		_speedX *= -1;					//범위 초과시 x 좌표 방향 바꿔줌		
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
	
	if (dir == false)				// right일때
	{
		_itemSpeed = 110;
		_angle = -(PI / 4);	
	}
	if (dir == true)				// left일때
	{
		_itemSpeed = 110;
		_angle = -(PI / 1.3);				
	}
	_speedX += cosf(_angle) * _itemSpeed;
	_speedY += -sinf(_angle) * _itemSpeed + _gravity;
}
