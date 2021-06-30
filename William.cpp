#include "stdafx.h"
#include "William.h"
#include "WilliamIdleState.h"

William::William()
{
	CLIPMANAGER->FindClip("william_attack_left")->isLoop = false;
	CLIPMANAGER->FindClip("william_attack_right")->isLoop = false;

	animator->AddClip("william_idle_left", CLIPMANAGER->FindClip("william_idle_left"));
	animator->AddClip("william_idle_right", CLIPMANAGER->FindClip("william_idle_right"));
	animator->AddClip("william_move_left", CLIPMANAGER->FindClip("william_move_left"));
	animator->AddClip("william_move_right", CLIPMANAGER->FindClip("william_move_right"));
	animator->AddClip("william_attack_left", CLIPMANAGER->FindClip("william_attack_left"));
	animator->AddClip("william_attack_right", CLIPMANAGER->FindClip("william_attack_right"));
	animator->AddClip("william_hit_left", CLIPMANAGER->FindClip("william_hit_left"));
	animator->AddClip("william_hit_right", CLIPMANAGER->FindClip("william_hit_right"));

	enemyAI->SetState(new WilliamIdleState());

}

William::~William()
{
}
