#include "stdafx.h"
#include "JesseHitState.h"

EnemyState* JesseHitState::Update(EnemyAI* enemy)
{
	// TODO HIT
	return nullptr;
}

void JesseHitState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("jesse_hit_right", true);
	else
		enemy->ChangeClip("jesse_hit_left", true);
}

void JesseHitState::Exit(EnemyAI* enemy)
{
}
