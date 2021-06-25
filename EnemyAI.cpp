#include "stdafx.h"
#include "EnemyAI.h"

EnemyAI::EnemyAI()
{
}

EnemyAI::~EnemyAI()
{
}

void EnemyAI::Init()
{
	commonStats->dir = RND->getInt(1);
	
	if (commonStats->dir == false)
		enemyState = ENEMY_IDLE_RIGHT;
	else
		enemyState = ENEMY_IDLE_LEFT;

	animator = gameObject->GetComponent<Animator>();
	collider = gameObject->GetComponent<BoxCollider>();
}

void EnemyAI::Update()
{
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