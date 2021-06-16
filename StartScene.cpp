#include "stdafx.h"
#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::Init()
{
    _background = new ImageObject();
    _background->renderer->Init("map.bmp", 10224, 1494);
    _background->transform->SetPosition(10224 / 2, 1494 / 2);
    _mapWidth = _background->renderer->width;
    _mapHeight = _background->renderer->height;
    mainCam = new Cam();
    mainCam->camera->SetMapSize(_mapWidth, _mapHeight);
    mainCam->transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);

    rockman.Init();

    smallObj.renderer->Init("small_object.bmp", 98, 224);
    smallObj.collider->SetSize(98, 224);
    smallObj.transform->SetPosition(WINSIZEX/2 - 200, WINSIZEY/2 + 200);

    _bigObj.GetComponent<Renderer>()->Init("big_object.bmp", 104, 320);
    _bigObj.GetComponent<BoxCollider>()->SetSize(104, 320);
    _bigObj.transform->SetPosition(WINSIZEX / 2 + 200, WINSIZEY / 2 + 200);

    _airObj.GetComponent<Renderer>()->Init("air_object.bmp", 128, 72);
    _airObj.GetComponent<BoxCollider>()->SetSize(128, 72);
    _airObj.transform->SetPosition(WINSIZEX / 2 + 400, WINSIZEY / 2 + 200);

    _ground = new GameObject();
    _ground->AddComponent(new BoxCollider());
    _ground->GetComponent<BoxCollider>()->Init();
    _ground->GetComponent<BoxCollider>()->SetSize(800, 100);
    _ground->transform->SetPosition(WINSIZEX/2, WINSIZEY/2 + 240);

    clearTrigger = new ClearTrigger();
    clearTrigger->Init(&rockman);
    clearZone.AddComponent(clearTrigger);
    clearZone.transform->SetPosition(WINSIZEX / 2 + 100, WINSIZEY / 2 + 140);
    return S_OK;
}

void StartScene::Release()
{
}

void StartScene::Update()
{
    _background->Update();
    rockman.Update();
    smallObj.Update();
    _bigObj.Update();
    _airObj.Update();
    _ground->Update();
    mainCam->Update();
    clearZone.Update();
}

void StartScene::Render()
{
    _background->Render();
    rockman.Render();
    smallObj.Render();
    _bigObj.Render();
    _airObj.Render();
    _ground->Render();
    clearZone.Render();
    mainCam->camera->Render(_hdc);
}
