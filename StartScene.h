#pragma once
#include "Scene.h"
class StartScene :
    public Scene
{
public:
    StartScene();
    ~StartScene();
    GameObject rockman;
    ImageObject* _background;
    Box testObj;
    Box item;
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

