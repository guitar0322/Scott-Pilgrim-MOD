#include "stdafx.h"
#include "Enemy.h"
#include "LukeIdleState.h"
#include "LukeRunState.h"

EnemyState* LukeIdleState::Update(Enemy* enemy)
{
    if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
        enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 200)
    {
        if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
            enemy->SetDir(false);
        else
            enemy->SetDir(true);
        return new LukeRunState();
    }
    return nullptr;
}

void LukeIdleState::Enter(Enemy* enemy)
{
    _idelTime = 0;
    if (enemy->GetDir() == false)
        enemy->ChangeClip("luke_idleRight", true);
    else
        enemy->ChangeClip("luke_idleLeft", true);
}

void LukeIdleState::Exit(Enemy* enemy)
{
}
