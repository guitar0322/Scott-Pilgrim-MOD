#include "stdafx.h"
#include "Luke.h"
#include "EnemyState.h"
#include "LukeIdleState.h"

void Luke::Init()
{
	renderer = (Renderer*)(AddComponent(new Renderer()));
	renderer->Init();

	collider = (BoxCollider*)(AddComponent(new BoxCollider()));
	collider->Init();
	collider->SetSize(74, 90);

	animator = (Animator*)(AddComponent(new Animator()));
	animator->Init();

	//tag = TAGMANAGER->GetTag("player");

	InitClip();

	_state = new LukeIdleState();
	_state->Enter(this);
	_speed = 50;
}

void Luke::Update()
{
	Enemy::Update();
	EnemyState* newState = _state->Update(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->Enter(this);
	}
}

void Luke::Render()
{
	Enemy::Render();
}

void Luke::InitClip()
{
	idleRight.Init("luke/idle_right.bmp", 320, 132, 4, 0.20f);
	idleLeft.Init("luke/idle_left.bmp", 320, 132, 4, 0.20f);

	animator->AddClip("luke_idleRight", &idleRight);
	animator->AddClip("luke_idleLeft", &idleLeft);
}