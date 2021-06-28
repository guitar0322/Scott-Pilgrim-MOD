#pragma once
#include "Component.h"
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
	Renderer* renderer;
	Animator* animation;
	BoxCollider* collision;
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
	void ChangeCilp(string name, bool isInitFrame);
	bool Getdir() const { return _dir; }
	void Setdir(bool dir) { _dir = dir; }
	float GetSpeed() const { return _speed; }
	Transform* GetPlayer() const { return _player->transform; }
	void SetPlayer(GameObject* player) { _player = player; }
};

