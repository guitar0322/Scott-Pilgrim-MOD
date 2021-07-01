#pragma once
#include "Component.h"
#include "EnemyInfo.h"

/* ���������� ���� ���漱�� */
class EnemyState;

class EnemyAI : public Component
{
private:
	/* Enemy�� player�� ã�� ���� ���� */
	GameObject* _player;

	/* ������ ����(��������)�� */
	EnemyState* state;	
	
	/* Enemy ���� */
	// IDLE STATE
	AnimationClip idelRight;
	AnimationClip idelLeft;

	// WALK STATE
	AnimationClip walkRight;
	AnimationClip walkLeft;

	// RUN STATE
	AnimationClip runRight;
	AnimationClip runLeft;

	// ATTACK STATE
	AnimationClip attackRight;
	AnimationClip attackLeft;

	// BLOCK STATE
	AnimationClip blockRight;
	AnimationClip blockLeft;

	// HIT STATE
	AnimationClip hitRight;
	AnimationClip hitLeft;

	// KICK STATE
	AnimationClip kickRight;
	AnimationClip kickLeft;

	// TODO COMBO ATTACK
	AnimationClip attack1Right;
	AnimationClip attack1Left;
	AnimationClip attack2Right;
	AnimationClip attack2Left;
	AnimationClip attack3Right;
	AnimationClip attack3Left;

	// DIE STATE
	AnimationClip dieRight;
	AnimationClip dieLeft;

	/* ������ ���� �ʿ䰡 �����ϱ� Ŭ���Ŵ��� �̱������� ã�ƿ��⸸ �Ұ�*/

public:
	EnemyAI();
	~EnemyAI();

	Animator* animator;
	EnemyInfo* enemyinfo;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	/* ���º� Clip �����ϱ� ���� �Լ� */
	void ChangeClip(string clipName, bool isInitFrame);

	/* _player�� ã�� ���� GETTER/SETTER */
	void SetPlayer(GameObject* player) { _player = player; }
	void SetState(EnemyState* newState);
	Transform* GetPlayerTransform() const { return _player->transform; }

	/* ENEMY AI.H */
/* 210630 private Player �������� ���� �Լ� �浹(��Ʈ) */
	GameObject* GetPlayer() const { return _player; }
};