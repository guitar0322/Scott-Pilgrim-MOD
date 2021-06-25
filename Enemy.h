#pragma once
#include "GameObject.h"
#include "EnemyAI.h"

class EnemyAI;

struct TAGENEMY
{
	/* 적에게 필요한 것들(체력, 속도 등) */
	bool dir;		// 방향

	int hp;			// 체력
	int damage;		// 데미지
	float speed;	//
};

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();

	BoxCollider* collider;
	Renderer* renderer;
	ZOrder* zOrder;
	Ground* ground;
	TAGENEMY* commonStats;

};
