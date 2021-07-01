#pragma once
#include "Component.h"
#define SUCCUBUSMAX 4
class Matthewstate;
class Matthew : public Component
{
private:
	Matthewstate* _matthewstate;
	GameObject* _player;
	float _hp;
	float _speed;
	bool _dir;

public:
	Matthew();
	~Matthew();
	GameObject* _succubus[SUCCUBUSMAX];
	Animator* animator;
	BoxCollider* collision;
	int _attackTime;
	float _phaseTime;
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
	void ChangeCilp(string name, bool isInitFrame);
	bool Getdir() const { return _dir; }
	void Setdir(bool dir) { _dir = dir; }
	float GetSpeed() const { return _speed; }
	float GetHp(){ return _hp; }
	Transform* GetPlayer() const { return _player->transform; }
	void SetPlayer(GameObject* player) { _player = player; }
};

