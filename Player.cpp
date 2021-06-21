#include "stdafx.h"
#include "Player.h"
#include "PlayerIdleState.h"

void Player::InputHandle()
{
	PlayerState* newState = _state->InputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->Enter(this);

	}

}

void Player::Init()
{
	animator = gameObject->GetComponent<Animator>();
	collider = gameObject->GetComponent<BoxCollider>();
	ground = gameObject->GetComponent<Ground>();
	ClipInit();
	_speed = 80;
	_gravity = 100;
	dir = false;
	dash = false;
	dirZ = false;
	_state = new PlayerIdleState();
	_state->Enter(this);
	runDelay = 0;
}

void Player::Update()
{
	InputHandle();
	_state->Update(this);
	if (dash == true)
		runDelay += TIMEMANAGER->getElapsedTime();
}

void Player::Render()
{
}

void Player::ChangeClip(string clipName, bool isInitFrame)
{
	if (isInitFrame == false)
	{
		animator->SetClip(animator->GetClip(clipName));
	}
	else
	{
		animator->SetClip(animator->GetClip(clipName), animator->currentFrame);
	}




}

void Player::ClipInit()
{
	idleRight.Init("idle_right.bmp", 312, 74, 8, 0.30f);
	idleLeft.Init("idle_Left.bmp", 312, 74, 8, 0.30f);
	walkRight.Init("walk_right.bmp", 228, 64, 6, 0.15f);
	walkLeft.Init("walk_left.bmp", 228, 64, 6, 0.15f);
	runRight.Init("run_right.bmp", 432, 63, 8, 0.17f);
	runLeft.Init("run_left.bmp", 432, 63, 8, 0.17f);
	jumpRight.Init("jump_right.bmp", 637, 72, 13, 0.22f);
	jumpRight.isLoop = false;
	jumpLeft.Init("jump_left.bmp", 637, 72, 13, 0.22f);
	jumpLeft.isLoop = false;

	attack1Right.Init("attack1_right.bmp", 240, 61, 4, 0.15f);
	attack2Right.Init("attack2_right.bmp", 183, 63, 3, 0.15f);
	attack3Right.Init("attack3_right.bmp", 183, 65, 3, 0.15f);
	attack4Right.Init("attack4_right.bmp", 432, 86, 8, 0.15f);
	attack1Right.isLoop = false;
	attack2Right.isLoop = false;
	attack3Right.isLoop = false;
	attack4Right.isLoop = false;

	attack1Left.Init("attack1_left.bmp", 240, 61, 4, 0.25f);
	attack2Left.Init("attack2_left.bmp", 183, 63, 3, 0.20f);
	attack3Left.Init("attack3_left.bmp", 183, 65, 3, 0.15f);
	attack4Left.Init("attack4_left.bmp", 432, 86, 8, 0.15f);
	attack1Left.isLoop = false;
	attack2Left.isLoop = false;
	attack3Left.isLoop = false;
	attack4Left.isLoop = false;


	animator->AddClip("idle_right", &idleRight);
	animator->AddClip("idle_left", &idleLeft);
	animator->AddClip("walk_right", &walkRight);
	animator->AddClip("walk_left", &walkLeft);
	animator->AddClip("run_right", &runRight);
	animator->AddClip("run_left", &runLeft);
	animator->AddClip("jump_right", &jumpRight);
	animator->AddClip("jump_left", &jumpLeft);

	animator->AddClip("attack1_right", &attack1Right);
	animator->AddClip("attack2_right", &attack2Right);
	animator->AddClip("attack3_right", &attack3Right);
	animator->AddClip("attack4_right", &attack4Right);
	animator->AddClip("attack1_left", &attack1Left);
	animator->AddClip("attack2_left", &attack2Left);
	animator->AddClip("attack3_left", &attack3Left);
	animator->AddClip("attack4_left", &attack4Left);





}
