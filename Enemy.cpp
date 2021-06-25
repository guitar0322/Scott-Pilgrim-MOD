#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	renderer = new Renderer();
	collider = new BoxCollider();
	animator = new Animator();
	zOrder = new ZOrder();
	ground = new Ground();

	AddComponent(renderer);
	renderer->Init();

	AddComponent(collider);
	collider->Init();

	AddComponent(animator);
	animator->Init();

	AddComponent(zOrder);
	zOrder->Init();

	AddComponent(ground);
	ground->Init();

}

Enemy::~Enemy()
{
	SAFE_DELETE(renderer);
	SAFE_DELETE(collider);
	SAFE_DELETE(animator);
}

void Enemy::Init()
{
}

void Enemy::ChangeClip(string clipName, bool isInitFrame)
{
	if (isInitFrame == true) {
		animator->SetClip(animator->GetClip(clipName));
	}
	else {
		animator->SetClip(animator->GetClip(clipName), animator->curClip->currentFrame);
	}
}