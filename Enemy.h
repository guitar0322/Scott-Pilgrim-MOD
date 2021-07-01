#pragma once
#include "GameObject.h"
#include "EnemyAI.h"
#include "EnemyInfo.h"

class Player;

class Enemy : public GameObject
{
private:

public:
	Enemy();
	~Enemy();

	Renderer* renderer;
	Animator* animator;
	ZOrder* zOrder;
	Shadow* shadow;

	// 210625 - AI, INFO �߰�, CPP���� �����Ҵ� �� Init
	EnemyInfo* enemyinfo;
	EnemyAI* enemyAI;
};