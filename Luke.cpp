#include "stdafx.h"
#include "EnemyState.h"
#include "Luke.h"
#include "LukeIdleState.h"

Luke::Luke()
{
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
	animator->GetClip("luke_kick_right")->isLoop = false;
	animator->AddClip("luke_kick_left", CLIPMANAGER->FindClip("luke_kick_left"));
	animator->GetClip("luke_kick_left")->isLoop = false;
	// ATTACK 1
	animator->AddClip("luke_attack1_right", CLIPMANAGER->FindClip("luke_attack1_right"));
	animator->GetClip("luke_attack1_right")->isLoop = false;
	animator->AddClip("luke_attack1_left", CLIPMANAGER->FindClip("luke_attack1_left"));
	animator->GetClip("luke_attack1_left")->isLoop = false;
	// ATTACK 2
	animator->AddClip("luke_attack2_right", CLIPMANAGER->FindClip("luke_attack2_right"));
	animator->GetClip("luke_attack2_right")->isLoop = false;
	animator->AddClip("luke_attack2_left", CLIPMANAGER->FindClip("luke_attack2_left"));
	animator->GetClip("luke_attack2_left")->isLoop = false;
	// ATTACK 3
	animator->AddClip("luke_attack3_right", CLIPMANAGER->FindClip("luke_attack3_right"));
	animator->GetClip("luke_attack3_right")->isLoop = false;
	animator->AddClip("luke_attack3_left", CLIPMANAGER->FindClip("luke_attack3_left"));
	animator->GetClip("luke_attack3_left")->isLoop = false;
	// DIE
	animator->AddClip("luke_die_right", CLIPMANAGER->FindClip("luke_die_right"));
	animator->AddClip("luke_die_left", CLIPMANAGER->FindClip("luke_die_left"));
}

Luke::~Luke()
{

}

void Luke::Init()
{
	zOrder->SetZ(transform->GetY() + 132 / 2);

	bool randomDir = RND->getInt(2);
	enemyinfo->SetDir(randomDir);

	enemyinfo->Sethp(50);

	int randomAttackDamage = RND->getInt(50);
	enemyinfo->SetDamage(randomAttackDamage);

	enemyinfo->SetSpeed(48.0f);
}