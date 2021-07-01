#include "stdafx.h"
#include "EnemyState.h"
#include "Malcolm.h"
#include "MalcolmIdleState.h"
Malcolm::Malcolm()
{
	CLIPMANAGER->FindClip("malcolm_attack_left")->isLoop = false;
	CLIPMANAGER->FindClip("malcolm_attack_right")->isLoop = false;

	animator->AddClip("malcolm_idle_left", CLIPMANAGER->FindClip("malcolm_idle_left"));
	animator->AddClip("malcolm_idle_right", CLIPMANAGER->FindClip("malcolm_idle_right"));
	animator->AddClip("malcolm_move_left", CLIPMANAGER->FindClip("malcolm_move_left"));
	animator->AddClip("malcolm_move_right", CLIPMANAGER->FindClip("malcolm_move_right"));
	animator->AddClip("malcolm_run_left", CLIPMANAGER->FindClip("malcolm_run_left"));
	animator->AddClip("malcolm_run_right", CLIPMANAGER->FindClip("malcolm_run_right"));
	animator->AddClip("malcolm_attack_left", CLIPMANAGER->FindClip("malcolm_attack_left"));
	animator->AddClip("malcolm_attack_right", CLIPMANAGER->FindClip("malcolm_attack_right"));
	animator->AddClip("malcolm_kick_left",CLIPMANAGER->FindClip("malcolm_kick_left"));
	animator->AddClip("malcolm_kick_right",CLIPMANAGER->FindClip("malcolm_kick_right"));
	animator->AddClip("malcolm_block_left",CLIPMANAGER->FindClip("malcolm_block_left"));
	animator->AddClip("malcolm_block_right",CLIPMANAGER->FindClip("malcolm_block_right"));
	animator->AddClip("malcolm_hit_left", CLIPMANAGER->FindClip("malcolm_hit_left"));
	animator->AddClip("malcolm_hit_right", CLIPMANAGER->FindClip("malcolm_hit_right"));
	

	enemyAI->SetState(new MalcolmIdleState);
}

Malcolm::~Malcolm()
{
}

void Malcolm::Init()
{
	zOrder->SetZ(transform->GetX() + 132 / 2);
	enemyinfo->SetSpeed(30.0f);
	enemyinfo->Sethp(100.f);
}
