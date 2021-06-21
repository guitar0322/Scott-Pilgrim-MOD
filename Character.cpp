#include "stdafx.h"
#include "Character.h"

Character::Character()
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

Character::~Character()
{
	SAFE_DELETE(renderer);
	SAFE_DELETE(collider);
	SAFE_DELETE(animator);
}
