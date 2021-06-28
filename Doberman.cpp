#include "stdafx.h"
#include "Doberman.h"
#include "Dobermanstate.h"
#include "Dobermanidlestate.h"
Doberman::Doberman()
{
}

Doberman::~Doberman()
{
}

void Doberman::Init()
{
	renderer = gameObject->GetComponent<Renderer>();
	collision = gameObject->GetComponent<BoxCollider>();
	animator = gameObject->GetComponent<Animator>();
	animator->AddClip("idleLeft", CLIPMANAGER->AddClip("idleLeft", "Doberman/idle_left.bmp", 656, 96, 4, 0.3f));
	animator->AddClip("idleRight", CLIPMANAGER->AddClip("idleRight", "Doberman/idle_right.bmp", 656, 96, 4, 0.3f));
	animator->AddClip("moveLeft", CLIPMANAGER->AddClip("moveLeft", "Doberman/move_left.bmp", 1146, 96, 6, 0.2f));
	animator->AddClip("moveRight", CLIPMANAGER->AddClip("moveRight", "Doberman/move_right.bmp", 1146, 96, 6, 0.2f));
	//animator->AddClip("runLeft", CLIPMANAGER->AddClip("runLeft", "Doberman/DogRunLeft.bmp", 1539, 96, 9, 0.1f));
	//animator->AddClip("runRight", CLIPMANAGER->AddClip("runRight", "Doberman/DogRunRight.bmp", 1539, 96, 9, 0.1f));
	animator->AddClip("attackLeft", CLIPMANAGER->AddClip("attackLeft", "Doberman/attack_left.bmp", 1075, 96, 7, 0.2f));
	animator->AddClip("attackRight", CLIPMANAGER->AddClip("attackRight", "Doberman/attack_right.bmp", 1075, 96, 7, 0.2f));
	gameObject->tag = TAGMANAGER->GetTag("enemy");
	_speed = 100;
	_HP = 200;

	_dir = true; // 처음 보는 방향이 true면 왼쪽이다.
	_dobermanState = new Dobermanidlestate();
	_dobermanState->Enter(this);
}
void Doberman::Release()
{
}

void Doberman::Update()
{
	Dobermanstate* newDobermanstate = _dobermanState->Update(this);
	if (newDobermanstate != nullptr)
	{
		SAFE_DELETE(_dobermanState);
		_dobermanState = newDobermanstate;
		_dobermanState->Enter(this);
	}
}

void Doberman::Render()
{
}

void Doberman::ChangeClip(string name, bool isInitFrame)
{
	if (isInitFrame == true)
	{
		animator->SetClip(animator->GetClip(name));
	}
	else
	{
		animator->SetClip(animator->GetClip(name), animator->curClip->currentFrame);
	}

}
