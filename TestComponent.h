#pragma once
#include "GameObject.h"
class TestComponent :
    public Component
{
public:
    virtual void Init();
    virtual void Update();
    virtual void Render();
};

