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
	animator = gameObject->GetComponent<Animator>(); // 매튜의 행동 애니메이션
	collision = gameObject->GetComponent<BoxCollider>(); // 매튜의 박스 충돌크기
	animator->AddClip("matthew_idle_left", CLIPMANAGER->AddClip("matthew_idle_left", "Matthew/idle_left.bmp", 686, 136, 6, 0.3f));
	animator->AddClip("matthew_idle_right", CLIPMANAGER->AddClip("matthew_idle_right", "Matthew/idle_right.bmp", 686, 136, 6, 0.3f));
	animator->AddClip("matthew_move_left", CLIPMANAGER->AddClip("matthew_move_left", "Matthew/move_left.bmp", 1160, 136, 10, 0.2f));
	animator->AddClip("matthew_move_right", CLIPMANAGER->AddClip("matthew_move_right", "Matthew/move_right.bmp", 1160, 136, 10, 0.2f));
	animator->AddClip("matthew_attack1_left", CLIPMANAGER->AddClip("matthew_attack1_left", "Matthew/attack1_Left.bmp", 1244, 136, 6, 0.2f));
	animator->AddClip("matthew_attack1_right", CLIPMANAGER->AddClip("matthew_attack1_right", "Matthew/attack1_Right.bmp", 1244, 136, 6, 0.2f));
	animator->AddClip("matthew_attack2_left", CLIPMANAGER->AddClip("matthew_attack2_left", "Matthew/attack2_Left.bmp", 1148, 136, 6, 0.2f));
	animator->AddClip("matthew_attack2_right", CLIPMANAGER->AddClip("matthew_attack2_right", "Matthew/attack2_Right.bmp", 1148, 136, 6, 0.2f));
	animator->AddClip("matthew_attack3_left", CLIPMANAGER->AddClip("matthew_attack3_left", "Matthew/attack3_Left.bmp", 1245, 136, 6, 0.2f));
	animator->AddClip("matthew_attack3_right", CLIPMANAGER->AddClip("matthew_attack3_right", "Matthew/attack3_Right.bmp", 1245, 136, 6, 0.2f));
	animator->AddClip("matthew_palmwind_left", CLIPMANAGER->AddClip("matthew_palmwind_left", "Matthew/palm_wind_left.bmp", 6665, 282, 18, 0.1f));
	animator->AddClip("matthew_palmwind_right", CLIPMANAGER->AddClip("matthew_palmwind_right", "Matthew/palm_wind_right.bmp", 6665, 282, 18, 0.1f));
	gameObject->tag = TAGMANAGER->GetTag("enemy");//적 태그 
	_hp = 500;
	_speed = 30;
	_dir = true;
	_matthewstate = new MatthewIdleState();
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
		animator->SetClip(animator->GetClip(name));
	}
	else
	{
		animator->SetClip(animator->GetClip(name), animator->curClip->currentFrame);
	}

}
