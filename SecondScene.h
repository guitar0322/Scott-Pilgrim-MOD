#pragma once
#include "Scene.h"
#include "RockMan.h"
class SecondScene :
    public Scene
{
public:
    SecondScene();
    ~SecondScene();
    RockMan rockman;
    virtual HRESULT Init();
    virtual HRESULT Init(int mapWidth, int mapHeight, ImageObject background);
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

