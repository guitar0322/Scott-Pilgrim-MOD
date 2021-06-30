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
	/* 210630 LUKE CLIP MANAGER */
	// IDLE
	animator->AddClip("luke_idle_right", CLIPMANAGER->FindClip("luke_idle_right"));
	animator->AddClip("luke_idle_left", CLIPMANAGER->FindClip("luke_idle_left"));
	// WALK
	animator->AddClip("luke_walk_right", CLIPMANAGER->FindClip("luke_walk_right"));
	animator->AddClip("luke_walk_left", CLIPMANAGER->FindClip("luke_walk_left"));
	// RUN
	animator->AddClip("luke_run_right", CLIPMANAGER->FindClip("luke_run_right"));
	animator->AddClip("luke_run_left", CLIPMANAGER->FindClip("luke_run_left"));	
	// BLOCK
	animator->AddClip("luke_block_right", CLIPMANAGER->FindClip("luke_block_right"));
	animator->AddClip("luke_block_left", CLIPMANAGER->FindClip("luke_block_left"));
	// HIT
	animator->AddClip("luke_hit_right", CLIPMANAGER->FindClip("luke_hit_right"));
	animator->AddClip("luke_hit_left", CLIPMANAGER->FindClip("luke_hit_left"));
	// KICK
	animator->AddClip("luke_kick_right", CLIPMANAGER->FindClip("luke_kick_right"));
	animator->AddClip("luke_kick_left", CLIPMANAGER->FindClip("luke_kcik_left"));
	// ATTACK 1
	animator->AddClip("luke_attack1_right", CLIPMANAGER->FindClip("luke_attack1_right"));
	animator->AddClip("luke_attack1_left", CLIPMANAGER->FindClip("luke_attack1_left"));
	// ATTACK 2
	animator->AddClip("luke_attack2_right", CLIPMANAGER->FindClip("luke_attack2_right"));
	animator->AddClip("luke_attack2_left", CLIPMANAGER->FindClip("luke_attack2_left"));
	// ATTACK 3
	animator->AddClip("luke_attack3_right", CLIPMANAGER->FindClip("luke_attack3_right"));
	animator->AddClip("luke_attack3_left", CLIPMANAGER->FindClip("luke_attack3_left"));
	// DIE
	animator->AddClip("luke_die_right", CLIPMANAGER->FindClip("luke_die_right"));
	animator->AddClip("luke_die_left", CLIPMANAGER->FindClip("luke_die_left"));

	// AI 상태 동적 할당
	enemyAI->SetState(new LukeIdleState());
}

Luke::~Luke()
{

}

void Luke::Init()
{
	zOrder->SetZ(transform->GetY() + 132 / 2);
	enemyinfo->SetSpeed(30.f);
	enemyinfo->Sethp(50);
}