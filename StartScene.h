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
    GameObject rockman;
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

