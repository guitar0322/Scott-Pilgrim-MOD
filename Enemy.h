#pragma once
#include "GameObject.h"
#include "EnemyAI.h"

class EnemyAI;

struct TAGENEMY
{
	/* ������ �ʿ��� �͵�(ü��, �ӵ� ��) */
	bool dir;		// ����

	int hp;			// ü��
	int damage;		// ������
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
