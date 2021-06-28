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
	
	//transform->MoveX(_itemSpeed * TIMEMANAGER->getElapsedTime());			//speed만큼 움직인다
	//transform->MoveY(_gravity *  TIMEMANAGER->getElapsedTime());			//gravity만큼 떨어진다
	
	transform->MoveX(_moveX * TIMEMANAGER->getElapsedTime());
	transform->MoveY(_moveY * TIMEMANAGER->getElapsedTime());
	//transform->MoveX(_itemSpeed * TIMEMANAGER->getElapsedTime());
	//transform->MoveY(_itemSpeed * TIMEMANAGER->getElapsedTime());

	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 + 37 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 - 37 <= transform->GetX())
	{
		//_itemSpeed *= -1;		//범위 초과시 방향 바꿔줌
		//_gravity = 80;			//범위 초과시 중력값

		_moveX *= -1;
		_gravity = 0;
	}

	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= itemZ )
	{	
		//item이라는 component는 모든 item이 공용으로 쓴다
		//zorder를 item의 밑바닥 기준으로 값을 넣어야 함
		//item의 높이는 다 다르다
		//그래서 image의 크기를 기준으로 잡음

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

void Item::Throw(bool dir)			//throw시 bool값 dir 반환
{
	throwDir = dir;					

	_gravity = 400;
	_itemSpeed = 400;
	_angle = PI / 4.2;

	_moveX += cosf(_angle) * _itemSpeed;
	_moveY += -sinf(_angle) * _itemSpeed + _gravity;

	if (dir == false)				//right일때
	{
		//transform->Move(_itemSpeed * TIMEMANAGER->getElapsedTime(), _gravity * TIMEMANAGER->getElapsedTime());
		//_itemSpeed = 210;	
		//transform->MoveY(PI/4);
		transform->Move(_moveX * TIMEMANAGER->getElapsedTime(), _moveY * TIMEMANAGER->getElapsedTime());
	}
	else							//left일때
	{
		//_itemSpeed = -210;
		transform->Move(_moveX * TIMEMANAGER->getElapsedTime(), _moveY * TIMEMANAGER->getElapsedTime());
	}
}

