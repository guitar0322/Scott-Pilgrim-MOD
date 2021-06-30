#pragma once
#include "Component.h"

class EnemyInfo : public Component
{
private:
	bool _dir;		// ����
	int _hp;		// ü��
	int _damage;	// ���ݷ� (�ʿ����� ���� �� �����غ���)
	float _speed;	// �ӵ�

public:	
	virtual void Init();

	/*
	virtual void Update();
	virtual void Render();
	�� ���� ���ʹ� �޴������� ������ ���¸� �ҷ� �ö� GETTET SETTER�� �̿��� �ҷ��´�.
	*/

	bool GetDir() const { return _dir; }
	void SetDir(bool dir) { _dir = dir; }

	int GetHp() const { return _hp; }
	void Sethp(int hp) { _hp = hp; }

	int GetDamage() const { return _damage; }
	void SetDamage(int damage) { _damage = damage; }

	/* ���ǵ�� ��Ȯ��, ����- */
	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }
};