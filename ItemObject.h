#pragma once
#include "Component.h"
class ItemObject :
	public GameObject
{
public:

	Renderer* renderer;
	Animator* animator;
	Item* item;
	BoxCollider* collider;

	virtual void Init();
};

