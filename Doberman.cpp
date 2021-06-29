#include "stdafx.h"
#include "EnemyState.h"
#include "Doberman.h"
#include "Dobermanidlestate.h"
Doberman::Doberman()
{
	CLIPMANAGER->FindClip("doberman_attack_left")->isLoop = false;
	CLIPMANAGER->FindClip("doberman_attack_right")->isLoop = false;

	animator->AddClip("doberman_idle_left", CLIPMANAGER->FindClip("doberman_idle_left"));
	animator->AddClip("doberman_idle_right", CLIPMANAGER->FindClip("doberman_idle_right"));
	animator->AddClip("doberman_move_left", CLIPMANAGER->FindClip("doberman_move_left"));
	animator->AddClip("doberman_move_right", CLIPMANAGER->FindClip("doberman_move_right"));
	animator->AddClip("doberman_attack_left", CLIPMANAGER->FindClip("doberman_attack_left"));
	animator->AddClip("doberman_attack_right",CLIPMANAGER->FindClip("doberman_attack_right"));


	enemyAI->SetState(new DobermanIdleState());
}

Doberman::~Doberman()
{
}

void Doberman::Init()
{
}