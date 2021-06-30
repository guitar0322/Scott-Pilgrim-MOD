#include "stdafx.h"
#include "EnemyState.h"
#include "Luke.h"
#include "LukeIdleState.h"

Luke::Luke()
{
	AnimationClip* testClip = CLIPMANAGER->FindClip("lee_idle_right");

	animator->AddClip("lee_idle_right", CLIPMANAGER->FindClip("lee_idle_right"));
	animator->AddClip("lee_idle_left", CLIPMANAGER->FindClip("lee_idle_left"));

	animator->AddClip("lee_run_right", CLIPMANAGER->FindClip("lee_run_right"));
	animator->AddClip("lee_run_left", CLIPMANAGER->FindClip("lee_run_left"));
	
	animator->AddClip("lee_attack1_right", CLIPMANAGER->FindClip("lee_attack1_right"));
	animator->AddClip("lee_attack1_left", CLIPMANAGER->FindClip("lee_attack1_left"));

	enemyAI->SetState(new LukeIdleState());
}

Luke::~Luke()
{

}

void Luke::Init()
{
	ground->enable = false;
	zOrder->SetZ(transform->GetY() + 132 / 2);
	enemyinfo->SetSpeed(30.f);
}