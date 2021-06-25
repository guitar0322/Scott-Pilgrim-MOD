#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "EnemyState.h"

class EnemyState;
class Enemy;

enum ENEMYSTATE
{
	ENEMY_IDLE_RIGHT,
	ENEMY_IDLE_LEFT,
	ENEMY_RUN_RIGHT,
	ENEMY_RUN_LEFT,
	ENEMY_ATTACK_RGIHT,
	ENEMY_ATTACK_LEFT
};

class EnemyAI : public Component
{
private:
	GameObject* _player;

public:
	EnemyAI();
	~EnemyAI();

	Animator* animator;
	ENEMYSTATE enemyState;	// EnemyAI 동작(IDIE, RUN 등)구분용 
	EnemyState* state;		// 디자인패턴(상태패턴용)

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ChangeClip(string clipName, bool isInitFrame);

	void SetPlayer(GameObject* player) { _player = player; }
	Transform* GetPlayerTransform() const { return _player->transform; }

	bool GetDir() const { return dir; }
	void SetDir(bool dir) { dir = dir; }

	// TODO - HP, ATTACK 값 GET, SET 추가할 것

	float GetSpeed() const { return speed; }
};

