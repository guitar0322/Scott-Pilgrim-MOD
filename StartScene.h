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
    float _jumpPower;
    float _gravity;
    bool _isJump;
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

