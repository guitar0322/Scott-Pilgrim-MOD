#pragma once
#include "GameObject.h"
class AutoMove :
    public Component
{
public:
    GameObject* pointerObj;
    virtual void Init();
    virtual void Update();
    virtual void Render();
};

