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
	animator->AddClip("matthew_idle_left", CLIPMANAGER->AddClip("matthew_idle_left", "matthew/idle_left.bmp", 686, 136, 6, 0.3f));
	animator->AddClip("matthew_idle_right", CLIPMANAGER->AddClip("matthew_idle_right", "matthew/idle_right.bmp", 686, 136, 6, 0.3f));
	animator->AddClip("matthew_move_left", CLIPMANAGER->AddClip("matthew_move_left", "matthew/move_left.bmp", 1160, 136, 10, 0.2f));
	animator->AddClip("matthew_move_right", CLIPMANAGER->AddClip("matthew_move_right", "matthew/move_right.bmp", 1160, 136, 10, 0.2f));
	animator->AddClip("matthew_attack1_left", CLIPMANAGER->AddClip("matthew_attack1_left", "matthew/attack1_Left.bmp", 1244, 136, 6, 0.2f));
	animator->AddClip("matthew_attack1_right", CLIPMANAGER->AddClip("matthew_attack1_right", "matthew/attack1_Right.bmp", 1244, 136, 6, 0.2f));
	animator->AddClip("matthew_attack2_left", CLIPMANAGER->AddClip("matthew_attack2_left", "matthew/attack2_Left.bmp", 1148, 136, 6, 0.2f));
	animator->AddClip("matthew_attack2_right", CLIPMANAGER->AddClip("matthew_attack2_right", "matthew/attack2_Right.bmp", 1148, 136, 6, 0.2f));
	animator->AddClip("matthew_attack3_left", CLIPMANAGER->AddClip("matthew_attack3_left", "matthew/attack3_Left.bmp", 1245, 136, 6, 0.2f));
	animator->AddClip("matthew_attack3_right", CLIPMANAGER->AddClip("matthew_attack3_right", "matthew/attack3_Right.bmp", 1245, 136, 6, 0.2f));
	animator->AddClip("matthew_palmwind_left", CLIPMANAGER->AddClip("matthew_palmwind_left", "matthew/palm_wind_left.bmp", 6665, 282, 18, 0.1f));
	animator->AddClip("matthew_palmwind_right", CLIPMANAGER->AddClip("matthew_palmwind_right", "matthew/palm_wind_right.bmp", 6665, 282, 18, 0.1f));
	animator->AddClip("matthew_hit_left", CLIPMANAGER->AddClip("matthew_hit_left","matthew/hit_left.bmp",488,117,4,0.3f));
	animator->AddClip("matthew_hit_right", CLIPMANAGER->AddClip("matthew_hit_right","matthew/hit_right.bmp",488,117,4,0.3f));
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
