#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	_animator->AddClip("trashbox_walk_attack_right", CLIPMANAGER->FindClip("trashbox_walk_attack_right"));
	_itemSpeed = 320.f;		// 아이템의 속도
	_gravity = 560.f;
	//_gravity = 15.0f;		// 중력
	_friction = 60.f;		// 마찰력
							//위 값들은 변하지 않기에 init에서 값 줌

	_angle = 0.f;			// 각도
	_accel = 65.f;			// 가속력
	_itemZ = 0.f;			// 플레이어의 Z 값을 가져오기 위한 변수
	
	_speedX = 0.f;			// 스피드와 앵글 값을 이용하기 위한 변수
	_speedY = 0.f;			// 상동
	
	_isGround = true;		//땅 위에 있는가? 아이템은 맨 처음 땅 위에 있기에 true
}

void Item::Update()
{
	transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
   
	if (_isGround == false)					//땅 위에 있지 않다면
	{
		transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());		
		_speedY += _gravity *TIMEMANAGER->getElapsedTime();
	}

	if (_isGround == true)					//throw해서 땅 위에 착지 한다면 마찰력 부여
	{
		if (_throwDir == false)				    //right일때 마찰력
		{
			_speedX -= _friction * TIMEMANAGER->getElapsedTime();
			if (_speedX <= 0) _speedX = 0;
		}

		if (_throwDir == true)				//left일때 마찰력
		{
			_speedX += _friction * TIMEMANAGER->getElapsedTime();
			if (_speedX >= 0) _speedX = 0;
		}
	}
	//땅에 착지 시
	if(transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= _itemZ && _itemZ != 0)
	{
		_speedY = 0.0f;
		_isGround = true;
	}

	//item이 MainCam의 범위 초과시
	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 <= transform->GetX())
	{
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
	_throwDir = dir;	
	_isGround = false;
	if (dir == false)				// right일때
	{
		//_angle = (PI/4);			// 45도
		_angle = 0;
	}
	if (dir == true)				// left일때
	{
		//_angle = (PI * 3 / 4);		//135도
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
