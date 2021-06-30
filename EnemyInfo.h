#pragma once
#include "Component.h"

class EnemyInfo : public Component
{
private:
	bool _dir;		// 방향
	int _hp;		// 체력
	int _damage;	// 공격력 (필요한지 조금 더 생각해보기)
	float _speed;	// 속도

public:	
	virtual void Init();

	/*
	virtual void Update();
	virtual void Render();
	얘 없이 에너미 메니저에서 적들의 상태를 불러 올때 GETTET SETTER를 이용해 불러온다.
	*/

	bool GetDir() const { return _dir; }
	void SetDir(bool dir) { _dir = dir; }

	int GetHp() const { return _hp; }
	void Sethp(int hp) { _hp = hp; }

	int GetDamage() const { return _damage; }
	void SetDamage(int damage) { _damage = damage; }

	/* 스피드는 불확실, 보류- */
	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }
};