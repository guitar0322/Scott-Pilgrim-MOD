#pragma once
#include "GameObject.h"
class PlayerState;

class Player :
	public Component
{
private:
	int _speed;
	int _gravity;

	PlayerState* _state;
	Animator* animator;

	AnimationClip idleRight;
	AnimationClip idleLeft;
	AnimationClip walkRight;
	AnimationClip walkLeft;
	AnimationClip runRight;
	AnimationClip runLeft;
	AnimationClip jumpRight;
	AnimationClip jumpLeft;
	AnimationClip attack1Right;
	AnimationClip attack2Right;
	AnimationClip attack3Right;
	AnimationClip attack4Right;
	AnimationClip attack1Left;
	AnimationClip attack2Left;
	AnimationClip attack3Left;
	AnimationClip attack4Left;



public:
	BoxCollider* collider;
	Ground* ground;
	bool dir; //오른쪽 왼쪽 구분
	bool dirZ; //오른쪽 왼쪽 구분
	bool dash; //뛰는 거 구분
	bool attackChange;
	float runDelay;

	void InputHandle();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ChangeClip(string clipName, bool isInitFrame);
	void ClipInit();

	int GetSpeed() { return _speed; }
	int GetGravity() { return _gravity; }


};

