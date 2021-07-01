#pragma once
#include "Component.h"
class Player;

class EnemyInfo : public Component
{
private:
	bool _dir;		// 방향 | FALSE == RIGHT, TRUE == LEFT
	int _hp;		// 체력
	int _damage;	// 공격력
	float _speed;	// 속도

public:	
	virtual void Init();

	bool GetDir() const { return _dir; }
	void SetDir(bool dir) { _dir = dir; }

	int GetHp() { return _hp; }
	void Sethp(int hp) { _hp = hp; }

	int GetDamage() const { return _damage; }
	void SetDamage(int damage) { _damage = damage; }

	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	/* 210629 적 플레이어 충돌 */
	void Hit(int damage);
};