#pragma once
#include "GameObject.h"
#include "EnemyAI.h"
#include "EnemyInfo.h"

//class Player;

class Enemy : public GameObject
{
private:

public:
	Enemy();
	~Enemy();

	Renderer* renderer;
	BoxCollider* collider;
	Animator* animator;
	ZOrder* zOrder;
	Ground* ground;

	// 210625 TODO - AI, INFO 추가, CPP에서 동적할당 및 Init
	EnemyInfo* enemyinfo;
	EnemyAI* enemyAI;

};