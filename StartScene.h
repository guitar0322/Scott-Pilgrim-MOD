#pragma once
#include "Scene.h"
#include "SceneInfoLoader.h"
#define BG_NUM 23
#define WALL_NUM 3

class WallObj;

class StartScene :
    public Scene
{
public:
    StartScene();
    ~StartScene();
    vector<GameObject*> _objectV;
    SceneInfoLoader sceneInfoLoader;
    ImageObject* background[BG_NUM];
    Box* box;
    ImageObject* imageObj;
    Character* character;
	Character* matthew;
	GameObject* player;
    WallObj* wall[WALL_NUM];
    GameObject* testGround;
	ItemObject* trashBox;
    // 210627 시영 추가 (Enemy 동적할당)
    Enemy* enemy;
	Enemy* doberman;
	Enemy* malcolm;
	Enemy* william;

    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void BackgroundInit();
    void CameraInit();
    void WallInit();
};

