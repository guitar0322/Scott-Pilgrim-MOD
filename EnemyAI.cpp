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
	/* ADD Ŭ�� �߰��ϱ� */
	/* 
	Ŭ�� ������ ���� ���ʹ� �̸��� ��Ʈ������ �ް��Ѵ�. 
	�� ������ LEFT, RIGHT �ٿ��� ���ʹ̿� �߰��ϵ��� 
	*/

	/* Info�� �ֱ� */
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
	// �������� �˾Ƽ� �׷��ֹǷ� �׷��� �ʿ䰡 ����.
}

void EnemyAI::ChangeClip(string clipName, bool isInitFrame)
{
}
