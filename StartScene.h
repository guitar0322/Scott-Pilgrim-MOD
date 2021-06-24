#pragma once
#include "Scene.h"
#define BG_NUM 23
#define WALL_NUM 3
class WallObj;
class StartScene :
    public Scene
{
public:
    StartScene();
    ~StartScene();
    ImageObject* background[BG_NUM];
    Box* box;
    ImageObject* imageObj;
    Character* character;
    WallObj* wall[WALL_NUM];
    GameObject* testGround;
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void BackgroundInit();
};

