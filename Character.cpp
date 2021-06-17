#include "stdafx.h"
#include "Character.h"

Character::Character()
{
	renderer = new Renderer();
	collider = new BoxCollider();
	animator = new Animator();
	
	AddComponent(renderer);
	renderer->Init();
	AddComponent(collider);
	collider->Init();
	AddComponent(animator);
	animator->Init();
}

Character::~Character()
{
	SAFE_DELETE(renderer);
	SAFE_DELETE(collider);
	SAFE_DELETE(animator);
}
