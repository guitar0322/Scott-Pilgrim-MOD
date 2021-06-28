#include "stdafx.h"
#include "Matthew.h"
#include "Matthewstate.h"
#include "Matthewidlestate.h"

Matthew::Matthew()
{
}

Matthew::~Matthew()
{
}

void Matthew::Init()
{
	renderer = gameObject->GetComponent<Renderer>(); //매튜의 랜더
	animation = gameObject->GetComponent<Animator>(); // 매튜의 행동 애니메이션
	collision = gameObject->GetComponent<BoxCollider>(); // 매튜의 박스 충돌크기
	animation->AddClip("MatthewidleLeft", CLIPMANAGER->AddClip("MatthewidleLeft", "Matthew/idle_left.bmp", 686, 136, 6, 0.3f));
	animation->AddClip("MatthewidleRight", CLIPMANAGER->AddClip("MatthewidleRight", "Matthew/idle_right.bmp", 686, 136, 6, 0.3f));
	animation->AddClip("MatthewmoveLeft", CLIPMANAGER->AddClip("MatthewmoveLeft", "Matthew/move_left.bmp", 1160, 136, 10, 0.2f));
	animation->AddClip("MatthewmoveRight", CLIPMANAGER->AddClip("MatthewmoveRight", "Matthew/move_right.bmp", 1160, 136, 10, 0.2f));
	animation->AddClip("Matthewattack1Left", CLIPMANAGER->AddClip("Matthewattack1Left", "Matthew/attack1_Left.bmp", 1244, 136, 6, 0.2f));
	animation->AddClip("Matthewattack1Right", CLIPMANAGER->AddClip("Matthewattack1Right", "Matthew/attack1_Right.bmp", 1244, 136, 6, 0.2f));
	animation->AddClip("Matthewattack2Left", CLIPMANAGER->AddClip("Matthewattack2Left", "Matthew/attack2_Left.bmp", 1148, 136, 6, 0.2f));
	animation->AddClip("Matthewattack2Right", CLIPMANAGER->AddClip("Matthewattack2Right", "Matthew/attack2_Right.bmp", 1148, 136, 6, 0.2f));
	animation->AddClip("Matthewattack3Left", CLIPMANAGER->AddClip("Matthewattack3Left", "Matthew/attack3_Left.bmp", 1245, 136, 6, 0.2f));
	animation->AddClip("Matthewattack3Right", CLIPMANAGER->AddClip("Matthewattack3Right", "Matthew/attack3_Right.bmp", 1245, 136, 6, 0.2f));
	gameObject->tag = TAGMANAGER->GetTag("enemy");//적 태그 
	_hp = 500;
	_speed = 30;
	_dir = true;
	_matthewstate = new Matthewidlestate();
	_matthewstate->Enter(this);
}

void Matthew::Release()
{
}

void Matthew::Update()
{
	Matthewstate* newMatthewstate = _matthewstate->Update(this);
	if (newMatthewstate != nullptr)
	{
		SAFE_DELETE(_matthewstate);
		_matthewstate = newMatthewstate;
		_matthewstate->Enter(this);
	}

}

void Matthew::Render()
{
}

void Matthew::ChangeCilp(string name, bool isInitFrame)
{
	if (isInitFrame == true)
	{
		animation->SetClip(animation->GetClip(name));
	}
	else
	{
		animation->SetClip(animation->GetClip(name), animation->curClip->currentFrame);
	}

}
