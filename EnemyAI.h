#pragma once
#include "Component.h"
#include "EnemyInfo.h"

/* 상태패턴을 위한 전방선언 */
class EnemyState;

class EnemyAI : public Component
{
private:
	/* Enemy가 player를 찾기 위해 선언 */
	GameObject* _player;

	/* 디자인 패턴(상태패턴)용 */
	EnemyState* state;	
	
	/* Enemy 상태 */
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

	/* 가지고 있을 필요가 없으니까 클립매니저 싱글톤으로 찾아오기만 할것*/

public:
	EnemyAI();
	~EnemyAI();

	Animator* animator;
	EnemyInfo* enemyinfo;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	/* 상태별 Clip 변경하기 위한 함수 */
	void ChangeClip(string clipName, bool isInitFrame);

	/* _player를 찾기 위한 GETTER/SETTER */
	void SetPlayer(GameObject* player) { _player = player; }
	void SetState(EnemyState* newState);
	Transform* GetPlayerTransform() const { return _player->transform; }

	/* ENEMY AI.H */
/* 210630 private Player 가져오기 위한 함수 충돌(히트) */
	GameObject* GetPlayer() const { return _player; }
};