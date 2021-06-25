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
	ENEMYSTATE enemyState;	// EnemyAI ����(IDIE, RUN ��)���п� 
	EnemyState* state;		// ����������(�������Ͽ�)

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ChangeClip(string clipName, bool isInitFrame);

	void SetPlayer(GameObject* player) { _player = player; }
	Transform* GetPlayerTransform() const { return _player->transform; }

	bool GetDir() const { return dir; }
	void SetDir(bool dir) { dir = dir; }

	// TODO - HP, ATTACK �� GET, SET �߰��� ��

	float GetSpeed() const { return speed; }
};

