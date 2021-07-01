#pragma once
#include "Component.h"
class Player;

class EnemyInfo : public Component
{
private:
	bool _dir;		// ���� | FALSE == RIGHT, TRUE == LEFT
	int _hp;		// ü��
	int _damage;	// ���ݷ�
	float _speed;	// �ӵ�

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

	/* 210629 �� �÷��̾� �浹 */
	void Hit(int damage);
};