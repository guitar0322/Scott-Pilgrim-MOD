#pragma once
#include "Component.h"
#include "EnemyInfo.h"

/* ���������� ���� ���漱�� */
class EnemyState;

class EnemyAI : public Component
{
private:
	/* Enemy�� player�� ã�� ���� ���� */
	GameObject* _player;

	/* ������ ����(��������)�� */
	EnemyState* state;	

public:
	EnemyAI();
	~EnemyAI();

	Animator* animator;
	EnemyInfo* enemyinfo;
	ZOrder* zOrder;

	/* 210630 Patrol ���� ���� & �Լ� ���� */
	float deltaX;
	float deltaY;
	pair<float, float> patrolPoint;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Hit(float damage);
	void Dead();
	/* ���º� Clip �����ϱ� ���� �Լ� */
	void ChangeClip(string clipName, bool isInitFrame);

	/* _player�� ã�� ���� GETTER/SETTER */
	void SetPlayer(GameObject* player) { _player = player; }
	void SetState(EnemyState* newState);
	Transform* GetPlayerTransform() const { return _player->transform; }

	/* 210629 ���¸� �����ϱ� ���� SETTER */
//	void SetState(EnemyState* newState);

	/* 210630 private Player �������� ���� �Լ� �浹(��Ʈ) */
	GameObject* GetPlayer() const { return _player; }
};