#pragma once
#include "Enemy.h"

class Luke : public Enemy
{
private:

public:
	Luke();
	~Luke();

	virtual void Init();
	virtual void Update();
	virtual void Render();
};