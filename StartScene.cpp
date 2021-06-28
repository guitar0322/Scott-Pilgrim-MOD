#include "stdafx.h"
#include "StartScene.h"
#include "Item.h"
#include "Player.h"
#include "WallObj.h"
#include "Wall.h"
#include "Doberman.h"
#include "Matthew.h"
StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::Init()
{
    Scene::Init();
    _mapWidth = 21206;
    _mapHeight = 680;
    MainCam->SetMapSize(_mapWidth, _mapHeight);
    MainCam->transform->SetPosition(WINSIZEX / 2, 568 / 2);
    MainCam->SetRenderHeight(568);
    MainCam->SetMapSize(21206, 680);
    SetBackBufferSize(_mapWidth, _mapHeight);
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

	CLIPMANAGER->AddClip("trashBox", "item/trashBox.bmp", 100, 76, 1, 1);
	CLIPMANAGER->AddClip("chair", "item/chair.bmp", 41, 48, 1, 1);

    character = new Character();
    character->name = "character";
    character->zOrder->SetY(character->transform->GetY() + 52);
	character->AddComponent(new Player);
	character->GetComponent<Player>()->Init();
	character->ground->Init(100, 5, 0, 52);
	character->zOrder->Init();
	character->zOrder->SetY(568 / 2 + 52);
	character->collider->isTrigger = true;
    character->AddComponent(new DebugText());
    character->GetComponent<DebugText>()->Init();

    wall[0] = new WallObj();
    wall[0]->Init(0, 300, 1000, 300);

    wall[1] = new WallObj();
    wall[1]->Init(0, WINSIZEY, 1000, WINSIZEY);

    wall[2] = new WallObj();
    wall[2]->Init(800, 200, 1000, 300);

    testGround = new GameObject();
    testGround->AddComponent(new Ground());
    testGround->GetComponent<Ground>()->Init();
    testGround->transform->SetPosition(500, 600);
    testGround->GetComponent<Ground>()->SetX(500);
    testGround->GetComponent<Ground>()->SetY(500);

	trashBox = new ItemObject();
	trashBox->Init();
	trashBox->item->SetItemImage("trashBox");
	trashBox->transform->SetPosition(640, 300);

	doberman = new Character();
	doberman->Init();
	doberman->transform->SetPosition(1200, 400);
	doberman->collider->isTrigger = true;
	doberman->AddComponent(new Doberman());
	doberman->GetComponent<Doberman>()->Init();
	doberman->GetComponent<Doberman>()->SetPlayer(character);
    doberman->ground->enable = false;
    
	matthew = new Character();
	matthew->Init();
	matthew->transform->SetPosition(2000, 400);
	matthew->collider->isTrigger = true;
	matthew->AddComponent(new Matthew());
	matthew->GetComponent<Matthew>()->Init();
	matthew->GetComponent<Matthew>()->SetPlayer(character);
	matthew->ground->enable = false;

    BackgroundInit();
    return S_OK;
}

void StartScene::Release()
{

}

void StartScene::Update()
{
    //if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
    //    character->transform->MoveX(15);
    //}
    mainCam->transform->SetPosition(character->transform->GetX(), mainCam->transform->GetY());
    testGround->Update();
	trashBox->Update();
    character->Update();
    BGMANAGER->Update();
    EFFECTMANAGER->Update();
    ZORDER->Update();
    mainCam->Update();
	doberman->Update();
	matthew->Update();
}

void StartScene::Render()
{
    BGMANAGER->Render();
    ZORDER->Render();
    for (int i = 0; i < WALL_NUM; i++) {
		wall[i]->Render();
    }
    testGround->Render();
	trashBox->Render();
	doberman->Render();
	matthew->Render();
    EFFECTMANAGER->Render();
    sprintf_s(debug[0], "Player X : %f ", character->transform->GetX());
    sprintf_s(debug[1], "FPS : %d ", TIMEMANAGER->getFPS());
    TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, 20, debug[0], strlen(debug[0]));
    TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, 40, debug[1], strlen(debug[1]));
    TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, 60, debug[2], strlen(debug[2]));
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

void StartScene::CameraInit()
{
}
