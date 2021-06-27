#include "stdafx.h"
#include "EnemyAI.h"
#include "EnemyState.h"


EnemyAI::EnemyAI()
{
}

EnemyAI::~EnemyAI()
{
}

void EnemyAI::Init()
{
	/* ADD 클립 추가하기 */
	/* 
	클립 인잇을 만들어서 에너미 이름을 스트링으로 받게한다. 
	그 다음에 LEFT, RIGHT 붙여서 에너미에 추가하도록 
	*/

	/* Info에 넣기 */
	//_dir = RND->getInt(1);
	//if (commonStats->dir == false)
	//	enemyState = ENEMY_IDLE_RIGHT;
	//else
	//	enemyState = ENEMY_IDLE_LEFT;
	//
	//animator = gameObject->GetComponent<Animator>();
	//collider = gameObject->GetComponent<BoxCollider>();
}

void EnemyAI::Update()
{
	/* 상태패턴이 계속 업데이트 되어야 하므로 여기에 넣어야 한다. */
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
	// 렌더러가 알아서 그려주므로 그려줄 필요가 없다.
}

void EnemyAI::ChangeClip(string clipName, bool isInitFrame)
{
}
