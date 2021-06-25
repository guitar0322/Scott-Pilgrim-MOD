#pragma once
#include "Component.h"
class Controler :
    public Component
{
private:
    float _speed;
public:
    Animator* animator;
    virtual void Init();
    virtual void Update();
    virtual void Render();
};

