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

void Doberman::init()
{
	renderer = gameObject->GetComponent<Renderer>();
	collision = gameObject->GetComponent<BoxCollider>();
	animator = gameObject->GetComponent<Animator>();
	animator->AddClip("idleLeft", CLIPMANAGER->AddClip("idleLeft", "Doberman/DogIdleLeft.bmp", 656, 96, 4, 0.3f));
	animator->AddClip("idleRight", CLIPMANAGER->AddClip("idleRight", "Doberman/DogIdleRight.bmp", 656, 96, 4, 0.3f));
	animator->AddClip("moveLeft", CLIPMANAGER->AddClip("moveLeft", "Dorberman/DogmoveLeft.bmp", 1146, 96, 6, 0.2f));
	animator->AddClip("moveRight", CLIPMANAGER->AddClip("moveRight", "Dorberman/DogmoveRight.bmp", 1146, 96, 6, 0.2f));
	animator->AddClip("runLeft", CLIPMANAGER->AddClip("runLeft", "Doberman/DogRunLeft.bmp", 1539, 96, 9, 0.1f));
	animator->AddClip("runRight", CLIPMANAGER->AddClip("runRight", "Doberman/DogRunRight.bmp", 1539, 96, 9, 0.1f));
	animator->AddClip("attackLeft", CLIPMANAGER->AddClip("attackLeft", "Doberman/DogAttackLeft.bmp", 1075, 96, 7, 0.2f));
	animator->AddClip("attackRight", CLIPMANAGER->AddClip("attackRight", "Doberman/DogAttackRight.bmp", 1075, 96, 7, 0.2f));
	gameObject->tag = TAGMANAGER->GetTag("enemy");
	_speed = 40;
	_dir = false;
	_DobermanState = new Dobermanidlestate();
	_DobermanState->Enter(this);
}
void Doberman::release()
{
}

void Doberman::update()
{
	Dobermanstate* newDobermanstate = _DobermanState->Update(this);
	if (newDobermanstate != nullptr)
	{
		SAFE_DELETE(_DobermanState);
		_DobermanState = newDobermanstate;
		_DobermanState->Enter(this);
	}
}

void Doberman::render()
{
}

void Doberman::changeClip(string name, bool isInitFrame)
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
