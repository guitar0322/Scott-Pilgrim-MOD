#include "stdafx.h"
#include "StartScene.h"
#include "Item.h"
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
    _background->name = "background";
    _mapWidth = 10224;
    _mapHeight = 1494;
    mainCam = new Cam();
    mainCam->camera->SetMapSize(_mapWidth, _mapHeight);
    mainCam->transform->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
    AnimationClip* idleRight = new AnimationClip();
    AnimationClip* runRight = new AnimationClip();
    AnimationClip* idleLeft = new AnimationClip();
    AnimationClip* runLeft = new AnimationClip();
    idleRight->Init("idle_right.bmp", 740, 90, 10, 0.15f);
    idleLeft->Init("idle_left.bmp", 740, 90, 10, 0.15f);
    runRight->Init("run_right.bmp", 1358, 94, 14, 0.08f);
    runLeft->Init("run_left.bmp", 1358, 94, 14, 0.08f);

    testObj.renderer->SetZOrder(true);
    testObj.collider->isTrigger = true;

    item.renderer->SetZOrder(true);
    item.transform->SetPosition(WINSIZEX / 2 + 200, WINSIZEY / 2);
    item.GetComponent<BoxCollider>()->isTrigger = true;
    item.AddComponent(new Item());

    rockman.name = "rockman";
    rockman.tag = TAGMANAGER->GetTag("player");
    rockman.AddComponent(new Renderer());
    rockman.GetComponent<Renderer>()->Init();
    rockman.GetComponent<Renderer>()->SetZOrder(true);
    rockman.AddComponent(new BoxCollider());
    rockman.GetComponent<BoxCollider>()->Init();
    rockman.GetComponent<BoxCollider>()->SetSize(74, 90);
    rockman.AddComponent(new Animator());
    rockman.GetComponent<Animator>()->Init();
    rockman.GetComponent<Animator>()->AddClip("idle_right", idleRight);
    rockman.GetComponent<Animator>()->AddClip("idle_left", idleLeft);
    rockman.GetComponent<Animator>()->AddClip("run_right", runRight);
    rockman.GetComponent<Animator>()->AddClip("run_left", runLeft);
    rockman.GetComponent<Animator>()->SetClip(rockman.GetComponent<Animator>()->GetClip("idle_right"));
    rockman.AddComponent(new Controler());
    rockman.GetComponent<Controler>()->Init();
    return S_OK;
}

void StartScene::Release()
{

}

void StartScene::Update()
{
    _background->Update();
    item.Update();
    rockman.Update();
    testObj.Update();
    mainCam->Update();
    ZORDER->update();
}

void StartScene::Render()
{
    _background->Render();
    //item.Render();
    //rockman.Render();
    ZORDER->render();
    TextOut(_backBuffer->getMemDC(), 20, 20, debug[0], strlen(debug[0]));
    TextOut(_backBuffer->getMemDC(), 20, 40, debug[1], strlen(debug[1]));
    TextOut(_backBuffer->getMemDC(), 20, 60, debug[2], strlen(debug[2]));
    mainCam->camera->Render(_hdc);
}
