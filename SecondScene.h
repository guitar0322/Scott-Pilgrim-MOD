#pragma once
#include "Scene.h"
class SecondScene :
    public Scene
{
public:
    SecondScene();
    ~SecondScene();
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

