#pragma once
#include "GameObject.h"
class PlayerState;

class Player :
	public Component
{
private:
	float _speed;		//플레이어 속도
	float _gravity;		//중력
	//float _friction;	//마찰

	PlayerState* _state;

	AnimationClip idleRight;
	AnimationClip idleLeft;
	AnimationClip walkRight;
	AnimationClip walkLeft;
	AnimationClip runRight;
	AnimationClip runLeft;
	AnimationClip jumpRight;
	AnimationClip jumpLeft;
	AnimationClip jumpZorderRight;
	AnimationClip jumpZorderLeft;
	AnimationClip attack1Right;
	AnimationClip attack2Right;
	AnimationClip attack3Right;
	AnimationClip attack4Right;
	AnimationClip attack1Left;
	AnimationClip attack2Left;
	AnimationClip attack3Left;
	AnimationClip attack4Left;
	AnimationClip kickAttackRight;
	AnimationClip kickAttackLeft;
	AnimationClip shieldRight;
	AnimationClip shieldLeft;



public:
	BoxCollider* collider;
	Ground* ground;
	Animator* animator;
	bool dir;			//오른쪽 왼쪽 구분
	bool jumpZ;			//Z축 점프 구분
	bool groundCheck;	//그라운드 체크 구분
	bool dash;			//뛰는 거 구분
	bool dashStop;		//마찰 구분
	bool shield;		//막기 구분
	bool dirZ;			//Z축 (true -> 위/ false->아래)
	
	bool attackChange;
	float runDelay;			//뛸 때 딜레이 시간 줄 때
	float jumpDelay;		//z축 위아래 점프 딜레이 시간 줄때
	float groundCheckDelay;	//그라운드체크 딜레이 시간
	float _friction;		//마찰


	void InputHandle();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ChangeClip(string clipName, bool isInitFrame);
	void ClipInit();

	int GetSpeed() { return _speed; }
	int GetGravity() { return _gravity; }
	int GetFriction() { return _friction; }


};

