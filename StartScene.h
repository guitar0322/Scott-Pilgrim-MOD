#pragma once
#include "Scene.h"
#include "RockMan.h"
#include "ClearTrigger.h"
class StartScene :
    public Scene
{
public:
    StartScene();
    ~StartScene();
    RockMan rockman;
    Box smallObj;
    Box _bigObj;
    Box _airObj;
    Zone clearZone;
    ClearTrigger* clearTrigger;
    GameObject* _ground;
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

