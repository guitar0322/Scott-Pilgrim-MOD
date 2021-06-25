#pragma once
#include "GameObject.h"
class Enemy2 :
	public Component
{
protected:
	GameObject* _enemy;
	bool _dir;
	float _speed;

public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void changeClip(string name, bool isInitFrame);
	virtual bool getDir() const { return _dir; }
	virtual void setDir(bool dir) { _dir = dir; }
	virtual void setEnemy(GameObject* enemy) { _enemy = enemy; }
	virtual float getSpeed() const { return _speed; }
};

