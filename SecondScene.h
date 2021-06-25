#pragma once
#include "Scene.h"
#define BG_NUM 23
class SecondScene :
    public Scene
{
public:
    ImageObject* background[BG_NUM];
    float mouseDeltaX;
public:
    SecondScene();
    ~SecondScene();
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void BackgroundInit();
    void CameraInit();
};

