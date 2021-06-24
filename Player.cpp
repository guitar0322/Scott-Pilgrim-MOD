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
	_gravity = 90;
	_friction = 130;
	dir = false;
	dirZ = false;
	dash = false;
	dashStop = false;
	jumpZ = false;
	shield = false;
	groundCheck = false;
	groundZCheck = false;
	_state = new PlayerIdleState();
	_state->Enter(this);
	runDelay = 0;
	jumpDelay = 0;

}

void Player::Update()
{
	InputHandle();
	_state->Update(this);
	if (dash == true)
		runDelay += TIMEMANAGER->getElapsedTime();
	if (jumpZ == true)
		jumpDelay += TIMEMANAGER->getElapsedTime();
	if (groundCheck == true)
		groundCheckDelay += TIMEMANAGER->getElapsedTime();

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
	idleRight.Init("player/idle_right.bmp", 640, 122, 8, 0.20f);
	idleLeft.Init("player/idle_left.bmp", 640, 122, 8, 0.20f);
	walkRight.Init("player/walk_right.bmp", 456, 128, 6, 0.25f);
	walkLeft.Init("player/walk_left.bmp", 456, 128, 6, 0.25f);
	runRight.Init("player/run_right.bmp", 864, 126, 8, 0.17f);
	runLeft.Init("player/run_left.bmp", 864, 126, 8, 0.17f);
	jumpRight.Init("player/jump_right.bmp", 684, 144, 7, 0.15f);
	jumpRight.isLoop = false;
	jumpLeft.Init("player/jump_left.bmp", 684, 144, 7, 0.15f);
	jumpLeft.isLoop = false;
	fallRight.Init("player/fall_right.bmp", 490, 144, 5, 0.15f);
	fallRight.isLoop = false;
	fallLeft.Init("player/fall_left.bmp", 490, 144, 5, 0.15f);
	fallLeft.isLoop = false;
	jumpZorderRight.Init("player/jumpZorder_right.bmp", 882, 144, 9, 0.10f);
	jumpZorderRight.isLoop = false;
	jumpZorderLeft.Init("player/jumpZorder_left.bmp", 882, 144, 9, 0.10f);
	jumpZorderLeft.isLoop = false;
	groundRight.Init("player/ground_right.bmp", 98, 144, 1, 0.10f);
	groundRight.isLoop = false;
	groundLeft.Init("player/ground_left.bmp", 98, 144, 1, 0.10f);
	groundLeft.isLoop = false;

	shieldRight.Init("player/shield_right.bmp", 532, 126, 7, 0.22f);
	shieldRight.isLoop = false;
	shieldLeft.Init("player/shield_left.bmp", 532, 126, 7, 0.22f);
	shieldLeft.isLoop = false;

	kickAttackRight.Init("player/kickAttack_right.bmp", 896, 126, 7, 0.15f);
	kickAttackRight.isLoop = false;
	kickAttackLeft.Init("player/kickAttack_left.bmp", 896, 126, 7, 0.15f);
	kickAttackLeft.isLoop = false;


	attack1Right.Init("player/attack1_right.bmp", 480, 122, 4, 0.15f);
	attack2Right.Init("player/attack2_right.bmp", 366, 126, 3, 0.15f);
	attack3Right.Init("player/attack3_right.bmp", 366, 130, 3, 0.15f);
	attack4Right.Init("player/attack4_right.bmp", 864, 166, 8, 0.15f);
	attack1Right.isLoop = false;
	attack2Right.isLoop = false;
	attack3Right.isLoop = false;
	attack4Right.isLoop = false;

	attack1Left.Init("player/attack1_left.bmp", 480, 122, 4, 0.25f);
	attack2Left.Init("player/attack2_left.bmp", 366, 126, 3, 0.20f);
	attack3Left.Init("player/attack3_left.bmp", 366, 130, 3, 0.15f);
	attack4Left.Init("player/attack4_left.bmp", 864, 166, 8, 0.15f);
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
	animator->AddClip("fall_right", &fallRight);
	animator->AddClip("fall_left", &fallLeft);
	animator->AddClip("jumpZorder_right", &jumpZorderRight);
	animator->AddClip("jumpZorder_left", &jumpZorderLeft);
	animator->AddClip("ground_right", &groundRight);
	animator->AddClip("ground_left", &groundLeft);

	animator->AddClip("shield_right", &shieldRight);
	animator->AddClip("shield_left", &shieldLeft);

	animator->AddClip("kickAttack_right", &kickAttackRight);
	animator->AddClip("kickAttack_left", &kickAttackLeft);


	animator->AddClip("attack1_right", &attack1Right);
	animator->AddClip("attack2_right", &attack2Right);
	animator->AddClip("attack3_right", &attack3Right);
	animator->AddClip("attack4_right", &attack4Right);
	animator->AddClip("attack1_left", &attack1Left);
	animator->AddClip("attack2_left", &attack2Left);
	animator->AddClip("attack3_left", &attack3Left);
	animator->AddClip("attack4_left", &attack4Left);





}
