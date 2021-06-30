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
	/* ADD Ŭ�� �߰��ϱ� */
	/* 
	Ŭ�� ������ ���� ���ʹ� �̸��� ��Ʈ������ �ް��Ѵ�. 
	�� ������ LEFT, RIGHT �ٿ��� ���ʹ̿� �߰��ϵ��� 
	*/
	animator = gameObject->GetComponent<Animator>();
	enemyinfo = gameObject->GetComponent<EnemyInfo>();
}

void EnemyAI::Update()
{
	/* ���������� ��� ������Ʈ �Ǿ�� �ϹǷ� ���⿡ �־�� �Ѵ�. */
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
