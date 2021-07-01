#include "stdafx.h"
#include "Jesse.h"
#include "JesseIdleState.h"

Jesse::Jesse()
{
	// IDLE
	animator->AddClip("jesse_idle_right", CLIPMANAGER->FindClip("jesse_idle_right"));
	animator->AddClip("jesse_idle_left", CLIPMANAGER->FindClip("jesse_idle_left"));
	// WALK
	animator->AddClip("jesse_walk_right", CLIPMANAGER->FindClip("jesse_walk_right"));
	animator->AddClip("jesse_walk_left", CLIPMANAGER->FindClip("jesse_walk_left"));
	// RUN
	animator->AddClip("jesse_run_right", CLIPMANAGER->FindClip("jesse_run_right"));
	animator->AddClip("jesse_run_left", CLIPMANAGER->FindClip("jesse_run_left"));
	// BLOCK
	animator->AddClip("jesse_block_right", CLIPMANAGER->FindClip("jesse_block_right"));
	animator->AddClip("jesse_block_left", CLIPMANAGER->FindClip("jesse_block_left"));
	// HIT
	animator->AddClip("jesse_hit_right", CLIPMANAGER->FindClip("jesse_hit_right"));
	animator->AddClip("jesse_hit_left", CLIPMANAGER->FindClip("jesse_hit_left"));
	// KICK
	animator->AddClip("jesse_kick_right", CLIPMANAGER->FindClip("jesse_kick_right"));
	animator->GetClip("jesse_kick_right")->isLoop = false;
	animator->AddClip("jesse_kick_left", CLIPMANAGER->FindClip("jesse_kick_left"));
	animator->GetClip("jesse_kick_left")->isLoop = false;
	// ATTACK
	animator->AddClip("jesse_attack1_right", CLIPMANAGER->FindClip("jesse_attack1_right"));
	animator->GetClip("jesse_attack1_right")->isLoop = false;
	animator->AddClip("jesse_attack1_left", CLIPMANAGER->FindClip("jesse_attack1_left"));
	animator->GetClip("jesse_attack1_left")->isLoop = false;
	// DIE
	animator->AddClip("jesse_die_right", CLIPMANAGER->FindClip("jesse_die_right"));
	animator->AddClip("jesse_die_left", CLIPMANAGER->FindClip("jesse_die_left"));

	/* JESSE INIT */
	Init();

	// AI STATE 동적 할당
	enemyAI->SetState(new JesseIdleState());
}

Jesse::~Jesse()
{
}

void Jesse::Init()
{
	/* 210630 JESSE INFO SETTING */
	zOrder->SetZ(transform->GetY() + 132 / 2);

	bool randomDir = RND->getInt(2);
	enemyinfo->SetDir(randomDir);

	enemyinfo->Sethp(50);

	int randomAttackDamage = RND->getInt(5);
	enemyinfo->SetDamage(randomAttackDamage);

	enemyinfo->SetSpeed(48.0f);
}
