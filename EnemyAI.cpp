#include "stdafx.h"
#include "EnemyAI.h"
#include "EnemyState.h"
#include "LukeIdleState.h"

EnemyAI::EnemyAI()
{
}

EnemyAI::~EnemyAI()
{
}

void EnemyAI::Init()
{
	/* 헤더에서 걸어준 것들 초기화 */
	zOrder = gameObject->GetComponent<ZOrder>();
	animator = gameObject->GetComponent<Animator>();
	enemyinfo = gameObject->GetComponent<EnemyInfo>();
}

void EnemyAI::Update()
{
	/* 상태패턴이 계속 업데이트 되어야 하므로 존재한다. */
	EnemyState* newState = state->Update(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(state);
		state = newState;
		state->Enter(this);
	}
}

void EnemyAI::Render()
{

}

void EnemyAI::Hit(float damage)
{
	DAMAGEMANAGER->CreateDamage(damage, transform->GetX(), transform->GetY() - 70);
	enemyinfo->Hit(damage);
	if (enemyinfo->GetHp() <= 0)
		Dead();
}

void EnemyAI::Dead()
{
	gameObject->SetActive(false);
	ENEMYMANAGER->DeadEvent(gameObject);
}

void EnemyAI::ChangeClip(string clipName, bool isInitFrame)
{
	AnimationClip* newClip = animator->GetClip(clipName);
	if (isInitFrame == true)
		animator->SetClip(animator->GetClip(clipName));
	else
		animator->SetClip(animator->GetClip(clipName), animator->curClip->currentFrame);

}

void EnemyAI::SetState(EnemyState * newState)
{
	state = newState;
	state->Enter(this);
	return;
}
