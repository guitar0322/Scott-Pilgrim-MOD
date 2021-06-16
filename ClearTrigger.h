#pragma once
#include "GameObject.h"
#include "RockMan.h"
class ClearTrigger :
    public Component
{
public:
    RockMan* rockman;
    ClearTrigger();
    ~ClearTrigger();
    virtual void Init(RockMan* rockman);
    virtual void Update();
    virtual void Render();
    virtual void OnTriggerEnter(GameObject* gameObject);
};

