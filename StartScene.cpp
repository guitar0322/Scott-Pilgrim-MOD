#include "stdafx.h"
#include "StartScene.h"
#include "Item.h"
#include "Player.h"
StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::Init()
{
    _mapWidth = 21206;
    _mapHeight = 680;
    mainCam = new Cam();
    mainCam->camera->SetMapSize(_mapWidth, _mapHeight);
    mainCam->transform->SetPosition(WINSIZEX / 2, 568 / 2);
    mainCam->camera->SetRenderHeight(568);
    //위에는 건들지 마시오

    //=============미리 만들어져 있는 예시 오브젝트============
    //AddComponent 및 GetComponent()->Init을 하는것이 번거롭기 때문에 필요한 컴포넌트를
    //미리 붙여 Init을 해놓는 GameObject클래스의 자식 클래스를 생성해놓았다.

    //1.ImageObject
    //Renderer컴포넌트가 미리 추가되어있는 오브젝트
    //imageObj->renderer 로 접근이 가능
    imageObj = new ImageObject();
    //2.Box
    //Renderer, BoxCollider가 미리 추가되어있는 오브젝트
    //->renderer,  ->collider 로 접근이 가능
    box = new Box();

    //3.Character
    //Renderer, BoxCollider, Animator, ZOrder, Ground 컴포넌트가 추가되어있는 오브젝트
    //->renderer, ->collider, ->animator, ->zOrder, ->ground로 접근 가능하다
    character = new Character();
    character->name = "character";
	character->AddComponent(new Player);
	character->GetComponent<Player>()->Init();
	character->ground->Init(100, 5, 0, 50);
    BackgroundInit();
    return S_OK;
}

void StartScene::Release()
{

}

void StartScene::Update()
{
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
        character->transform->MoveX(15);
    }
    mainCam->transform->SetPosition(character->transform->GetX(), mainCam->transform->GetY());
    character->Update();
    BGMANAGER->Update();
    ZORDER->Update();
    mainCam->Update();
}

void StartScene::Render()
{
    BGMANAGER->Render();
    ZORDER->Render();
    sprintf_s(debug[0], "Player X : %f ", character->transform->GetX());
    sprintf_s(debug[1], "FPS : %d ", TIMEMANAGER->getFPS());
    TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, 20, debug[0], strlen(debug[0]));
    TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, 40, debug[1], strlen(debug[1]));
    TextOut(_backBuffer->getMemDC(), 20, 60, debug[2], strlen(debug[2]));
    mainCam->camera->Render(_hdc);
}

void StartScene::BackgroundInit()
{
    for (int i = 0; i < BG_NUM; i++) {
        char fileName[64];
        sprintf_s(fileName, "map/background%d.bmp", i + 1);
		background[i] = new ImageObject();
		background[i]->renderer->Init(fileName, 922, 680);
		background[i]->transform->SetPosition(922 * i + 922 /2, 680 /2);
		background[i]->name = "background";
        BGMANAGER->AddBackground(background[i]);
    }
	BGMANAGER->SetMargin(30);
	BGMANAGER->SetBackgroundWidth(922);
    BGMANAGER->SetPlayer(character);
}
