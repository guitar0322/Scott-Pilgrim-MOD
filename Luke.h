#pragma once
#include "Enemy.h"
#include "GameObject.h"

class EnemyState;

class Luke : public virtual GameObject, public Enemy 
{
private:
	EnemyState* _state;
	GameObject* _player;
	bool _dir;
	float _speed;

public:
	BoxCollider* collider;
	Ground* ground;
	Animator* animator;

	AnimationClip idleRight;
	AnimationClip idleLeft;
	AnimationClip runRight;
	AnimationClip runLeft;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void InitClip();
	//void ChangeClip(string clipName, bool isInitFrame);

	//bool GetDir() const { return _dir; }
	//void SetDir(bool dir) { _dir = dir; }

	//void SetPlayer(GameObject* player) { _player = player; }
	//Transform* GetPlayerTransform() const { return _player->transform; }

	//float GetSpeed() const { return _speed; }
};
