#pragma once
#include "Scene.h"
#define BG_NUM 23
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
	ItemObj* itemObj;
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void BackgroundInit();
};

