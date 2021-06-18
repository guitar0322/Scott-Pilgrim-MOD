#include "stdafx.h"
#include "Controler.h"

void Controler::Init()
{
	_speed = 100;
	animator = gameObject->GetComponent<Animator>();
}


void Controler::Update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		animator->SetClip(animator->GetClip("run_right"));
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		transform->MoveX(_speed * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
		animator->SetClip(animator->GetClip("idle_right"));
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		animator->SetClip(animator->GetClip("run_left"));
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		transform->MoveX(-_speed * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
		animator->SetClip(animator->GetClip("idle_left"));
	}


	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		transform->MoveY(-_speed * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		transform->MoveY(_speed * TIMEMANAGER->getElapsedTime());
	}
}

void Controler::Render()
{
}
