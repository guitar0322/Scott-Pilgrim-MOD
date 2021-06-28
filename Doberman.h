#pragma once
#include "GameObject.h"
class Dobermanstate;
class Doberman : public Component
{
private:
	Dobermanstate* _dobermanState;
	GameObject* _player;
	GameObject* _enemy;
	bool _dir;
	float _speed;
	float _HP;

public:
	Doberman();
	~Doberman();
	Renderer* renderer;
	BoxCollider* collision;
	Animator* animator;
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
	void ChangeClip(string name, bool isInitFrame);
	bool GetDir() const { return _dir; }
	void SetDir(bool dir) { _dir = dir; }
	void SetEnemy(GameObject* enemy) { _enemy = enemy; }
	float GetSpeed() const { return _speed; }
	Transform* GetPlayer()const { return _player->transform; }
	void SetPlayer(GameObject* player) { _player = player; }
};

