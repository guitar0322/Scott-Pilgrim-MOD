#pragma once
#include "Enemy2.h"
class Dobermanstate;
class Doberman : public Enemy2
{
private:
	Dobermanstate* _DobermanState;
	GameObject* Player;

public:
	Doberman();
	~Doberman();
	Renderer* renderer;
	BoxCollider* collision;
	Animator* animator;
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void changeClip(string name, bool isInitFrame);
	virtual bool getDir() const { return _dir; }
	virtual void setDir(bool dir) { _dir = dir; }
	virtual void setEnemy(GameObject* enemy) { _enemy = enemy; }
	virtual float getSpeed() const { return _speed; }
	Transform* getPlayer()const { return Player->transform; }
	void SetPlayer(GameObject* player) { Player = player; }
};

