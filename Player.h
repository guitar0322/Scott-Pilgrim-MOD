#pragma once
#include "Component.h"
class PlayerState;

class Player :
	public Component
{
private:
	float _speed;		//�÷��̾� �ӵ�
	float _gravity;		//�߷�
//	float _itemZ;		//item��z���� �־��ֱ� ���� ����
	
	int _enterNum;		//�÷��̾�� gameObject�� ��ĥ��++
	int _exitNum;		//�÷��̾�� gameObject�� �������� ��������++

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
	AnimationClip kickSkillRight;
	AnimationClip kickSkillLeft;
	AnimationClip walkJumpKickRight;
	AnimationClip walkJumpKickLeft;
	AnimationClip runJumpKickRight;
	AnimationClip runJumpKickLeft;
	AnimationClip shieldRight;
	AnimationClip shieldLeft;


	//�μ��̹���
	AnimationClip twoHandPickRight;
	AnimationClip twoHandPickLeft;
	AnimationClip twoHandIdleRight;
	AnimationClip twoHandIdleLeft;
	AnimationClip twoHandWalkRight;
	AnimationClip twoHandWalkLeft;
	AnimationClip twoHandRunRight;
	AnimationClip twoHandRunLeft;
	AnimationClip twoHandJumpRight;
	AnimationClip twoHandJumpLeft;
	AnimationClip twoHandFallRight;
	AnimationClip twoHandFallLeft;
	AnimationClip twoHandGroundRight;
	AnimationClip twoHandGroundLeft;
	AnimationClip twoHandZorderRight;
	AnimationClip twoHandZorderLeft;
	AnimationClip twoHandWalkAttackRight;
	AnimationClip twoHandWalkAttackLeft;
	AnimationClip twoHandRunAttackRight;
	AnimationClip twoHandRunAttackLeft;



public:
	BoxCollider* collider;
	Ground* ground;
	Animator* animator;
	ZOrder* zOrder;
	Item* item;

	bool dir;			//������ ���� ����
	bool jumpZ;			//Z�� ���� ����
	bool groundCheck;	//�׶��� üũ ����
	bool groundZCheck;	//Z�� �׶��� üũ ����

	bool isRun;			//�ٴ� �� ����
	bool runKeyPress;	//Ű �����ߴ���

	bool block;			//���� ����
	bool dirZ;			//Z�� (true -> ��/ false->�Ʒ�)
	bool onGround;
	bool isCatch;		//�������� ȹ�� ���� 
	bool isPick;		//�������� ���÷ȴ��� ����

	float runDelay;			//�� �� ������ �ð� �� ��
	float jumpDelay;		//z�� ���Ʒ� ���� ������ �ð� �ٶ�
	float pickDelay;		//�ݴ� �ð� ������
	float friction;			//����


	RECT groundCheckRc;

	void InputHandle();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ChangeClip(string clipName, bool isInitFrame);
	void ClipInit();

	int GetSpeed() const { return _speed; }
	int GetGravity() const { return _gravity; }
	int GetFriction() const { return friction; }
	virtual void OnTriggerEnter(GameObject* gameObject);
	virtual void OnTriggerExit(GameObject* gameObject);

	virtual void PickItem();		//������ ȹ�� �Լ�
	virtual void PutItem();			//������ ���� �Լ�


};

