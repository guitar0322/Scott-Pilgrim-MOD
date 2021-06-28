#include "stdafx.h"
#include "EnemyState.h"
#include "Luke.h"
#include "LukeIdleState.h"

Luke::Luke()
{
	animator->AddClip("luke_idle_right", CLIPMANAGER->FindClip("luke_idle_right"));
	animator->AddClip("luke_idle_left", CLIPMANAGER->FindClip("luke_idle_left"));

	animator->AddClip("luke_run_right", CLIPMANAGER->FindClip("luke_run_right"));
	animator->AddClip("luke_run_left", CLIPMANAGER->FindClip("luke_run_left"));
	
	animator->AddClip("luke_attack_right", CLIPMANAGER->FindClip("luke_attack_right"));
	animator->AddClip("luke_attack_left", CLIPMANAGER->FindClip("luke_attack_left"));

	enemyAI->SetState(new LukeIdleState());
}

Luke::~Luke()
{

}

void Luke::Init()
{

}