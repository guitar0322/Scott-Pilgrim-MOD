#pragma once
#include "Component.h"
class PlayerState;

class Player :
	public Component
{
private:
	float _speed;		//플레이어 속도
	float _gravity;		//중력
//	float _itemZ;		//item의z값을 넣어주기 위한 변수
	
	int _enterNum;		//플레이어와 gameObject가 겹칠때++
	int _exitNum;		//플레이어와 gameObject가 겹쳐짐이 끝낫을떄++
	bool _isCatch;		//아이템 획득 유무
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
	AnimationClip fallRight;
	AnimationClip fallLeft;
	AnimationClip jumpZorderRight;
	AnimationClip jumpZorderLeft;
	AnimationClip groundRight;
	AnimationClip groundLeft;
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
	ZOrder* zOrder;
	Item* item;

	bool dir;			//오른쪽 왼쪽 구분
	bool jumpZ;			//Z축 점프 구분
	bool groundCheck;	//그라운드 체크 구분
	bool groundZCheck;	//Z축 그라운드 체크 구분
	bool dash;			//뛰는 거 구분
	bool block;			//막기 구분
	bool dirZ;			//Z축 (true -> 위/ false->아래)
	
	bool attackChange;
	float runDelay;			//뛸 때 딜레이 시간 줄 때
	float jumpDelay;		//z축 위아래 점프 딜레이 시간 줄때
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
	
	virtual void OnTriggerEnter(GameObject* gameObject);
	virtual void OnTriggerExit(GameObject* gameObject);

	virtual void PickItem();		//아이템 획득 함수
	virtual void PutItem();			//아이템 놓는 함수


};

