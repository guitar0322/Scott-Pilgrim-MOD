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
	bool _isCatch;		//������ ȹ�� ����
	//float _friction;	//����

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

	bool dir;			//������ ���� ����
	bool jumpZ;			//Z�� ���� ����
	bool groundCheck;	//�׶��� üũ ����
	bool groundZCheck;	//Z�� �׶��� üũ ����
	bool dash;			//�ٴ� �� ����
	bool block;			//���� ����
	bool dirZ;			//Z�� (true -> ��/ false->�Ʒ�)
	
	bool attackChange;
	float runDelay;			//�� �� ������ �ð� �� ��
	float jumpDelay;		//z�� ���Ʒ� ���� ������ �ð� �ٶ�
	float _friction;		//����


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

	virtual void PickItem();		//������ ȹ�� �Լ�
	virtual void PutItem();			//������ ���� �Լ�


};

