#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	renderer = new Renderer();
	//collider = new BoxCollider();
	animator = new Animator();
	zOrder = new ZOrder();
	shadow = new Shadow();
	ground = new Ground();
	enemyinfo = new EnemyInfo();
	enemyAI = new EnemyAI();

	AddComponent(zOrder);
	zOrder->Init();

	AddComponent(shadow);
	shadow->Init();

	AddComponent(renderer);
	renderer->Init();

	//AddComponent(collider);
	//collider->Init();
	//collider->isTrigger = true;

	AddComponent(animator);
	animator->Init();


	AddComponent(ground);
	ground->Init();

	AddComponent(enemyinfo);
	enemyinfo->Init();

	AddComponent(enemyAI);
	enemyAI->Init();	
}

Enemy::~Enemy()
{
	SAFE_DELETE(renderer);
	SAFE_DELETE(collider);
	SAFE_DELETE(animator);
	SAFE_DELETE(zOrder);
	SAFE_DELETE(ground);
	SAFE_DELETE(enemyinfo);
	SAFE_DELETE(enemyAI);
}

